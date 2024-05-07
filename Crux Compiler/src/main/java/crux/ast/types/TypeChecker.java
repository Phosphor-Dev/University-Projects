package crux.ast.types;

import crux.ast.*;
import crux.ast.traversal.NullNodeVisitor;

import java.util.ArrayList;

/**
 * This class will associate types with the AST nodes from Stage 2
 */
public final class TypeChecker {
  private final ArrayList<String> errors = new ArrayList<>();

  public ArrayList<String> getErrors() {
    return errors;
  }

  public void check(DeclarationList ast) {
    var inferenceVisitor = new TypeInferenceVisitor();
    inferenceVisitor.visit(ast);
  }

  /**
   * Helper function, should be used to add error into the errors array
   */
  private void addTypeError(Node n, String message) {
    errors.add(String.format("TypeError%s[%s]", n.getPosition(), message));
  }

  /**
   * Helper function, should be used to record Types if the Type is an ErrorType then it will call
   * addTypeError
   */
  private void setNodeType(Node n, Type ty) {
    ((BaseNode) n).setType(ty);
    if (ty.getClass() == ErrorType.class) {
      addTypeError(n, ((ErrorType) ty).getMessage());
    }
  }

  /**
   * Helper to retrieve Type from the map
   */
  public Type getType(Node n) {
    return ((BaseNode) n).getType();
  }


  /**
   * This calls will visit each AST node and try to resolve its type with the help of the
   * symbolTable.
   */
  private final class TypeInferenceVisitor extends NullNodeVisitor<Void> {

    //private Symbol currentFunctionSymbol;
    private Type currentFunctionReturnType;

    @Override
    public Void visit(VarAccess vaccess) {
      setNodeType(vaccess,vaccess.getSymbol().getType());
      return null;
    }

    @Override
    public Void visit(ArrayDeclaration arrayDeclaration) {
      if (((ArrayType) arrayDeclaration.getSymbol().getType()).getBase().equivalent(new IntType())) {
        return null;
      } else if (((ArrayType) arrayDeclaration.getSymbol().getType()).getBase().equivalent(new BoolType())) {
        return null;
      } else {
        addTypeError(arrayDeclaration, "arrayDeclarationError");
      }
      return null;
    }

    @Override
    public Void visit(Assignment assignment) {
      assignment.getLocation().accept(this);
      assignment.getValue().accept(this);
      setNodeType(assignment, getType(assignment.getLocation()).assign(getType(assignment.getValue())));
      return null;
    }

    @Override
    public Void visit(Break brk) {
      return super.visit(brk);
    }

    @Override
    public Void visit(Call call) {
      TypeList typeList = TypeList.of();
      for (var arg: call.getArguments()){
        arg.accept(this);
        typeList.append(getType(arg));
      }
      setNodeType(call, call.getCallee().getType().call(typeList));
      return null;
    }

    @Override
    public Void visit(DeclarationList declarationList) {
      for (var arg: declarationList.getChildren()){
        arg.accept(this);
      }
      return null;
    }

    @Override
    public Void visit(FunctionDefinition functionDefinition) {
      if (functionDefinition.getSymbol().getName().equals("main")) {
        if (((FuncType)functionDefinition.getSymbol().getType()).getRet().getClass() != VoidType.class){
          addTypeError(functionDefinition, "FunctionDefinitionError");
        }
      } else {
        currentFunctionReturnType = ((FuncType)functionDefinition.getSymbol().getType()).getRet();
      }
      for (var arg: ((FuncType) functionDefinition.getSymbol().getType()).getArgs()){
        if (!(arg.getClass() == IntType.class || arg.getClass() == BoolType.class)){
          addTypeError(functionDefinition, "FunctionDefinitionError");
        }
      }
      for (var arg: functionDefinition.getStatements().getChildren()){
        arg.accept(this);
      }

      return null;
    }

    @Override
    public Void visit(IfElseBranch ifElseBranch) {
      for (var e: ifElseBranch.getCondition().getChildren()){
        e.accept(this);
      }
      ifElseBranch.getCondition().accept(this);
      if (getType(ifElseBranch.getCondition()).getClass() != BoolType.class){
        addTypeError(ifElseBranch, "ifElseBranchError");
      }
      for (var arg: ifElseBranch.getThenBlock().getChildren()){
        arg.accept(this);
      }
      for (var arg: ifElseBranch.getElseBlock().getChildren()){
        arg.accept(this);
      }
      return null;
    }

    @Override
    public Void visit(ArrayAccess access) {
      var baseTy = access.getBase().getType();
      Node node = access.getIndex();
      node.accept(this);
      var offsetTy = ((BaseNode)node).getType();
      var resultTy = baseTy.index(offsetTy);
      setNodeType(access,resultTy);
      return null;
    }

    @Override
    public Void visit(LiteralBool literalBool) {
      setNodeType(literalBool, new BoolType());
      return null;
    }

    @Override
    public Void visit(LiteralInt literalInt) {
      setNodeType(literalInt, new IntType());
      return null;
    }

    @Override
    public Void visit(For forloop) {
      for(var arg:forloop.getInit().getChildren()){
        arg.accept(this);
      }
      for(var arg:forloop.getCond().getChildren()){
        arg.accept(this);
      }
      forloop.getCond().accept(this);
      for(var arg:forloop.getIncrement().getChildren()){
        arg.accept(this);
      }
      for(var arg:forloop.getBody().getChildren()){
        arg.accept(this);
      }
      return null;
    }

    @Override
    public Void visit(OpExpr op) {
      op.getLeft().accept(this);
      Type leftType;
      Type rightType = null;
      if (op.getRight() != null){
        op.getRight().accept(this);
        leftType = getType(op.getLeft());
        rightType = getType(op.getRight());
      }else{
        leftType = getType(op.getLeft());
      }

      switch (op.getOp()){
        case ADD:
          var a = leftType.add(rightType);
          setNodeType(op, a);
          break;
        case SUB:
          var s = leftType.sub(rightType);
          setNodeType(op, s);
          break;
        case MULT:
          var m = leftType.mul(rightType);
          setNodeType(op, m);
          break;
        case DIV:
          var d = leftType.div(rightType);
          setNodeType(op, d);
          break;
        case LOGIC_AND:
          var la = leftType.and(rightType);
          setNodeType(op, la);
          break;
        case LOGIC_OR:
          var lo = leftType.or(rightType);
          setNodeType(op, lo);
          break;
        case LOGIC_NOT:
          var ln = leftType.not();
          setNodeType(op, ln);
          break;
        case GE:
        case LE:
        case NE:
        case EQ:
        case GT:
        case LT:
          var many = leftType.compare(rightType);
          setNodeType(op, many);
          break;
        default:
          addTypeError(op, "OpExprError");
          break;
      }
      return null;
    }

    @Override
    public Void visit(Return ret) {
      ret.getValue().accept(this);
      if (getType(ret.getValue()).getClass() != currentFunctionReturnType.getClass()){
        addTypeError(ret, "returnError");
      }
      return null;
    }

    @Override
    public Void visit(StatementList statementList) {
      boolean lastStatementReturns = false;
      for (var arg: statementList.getChildren()) {
        if (!lastStatementReturns) {
          arg.accept(this);
          if (arg.getClass() == Return.class){
            lastStatementReturns = true;
          }
        } else {
          addTypeError(statementList, "statementListError");
          break;
        }
      }
      return null;
    }

    @Override
    public Void visit(VariableDeclaration variableDeclaration) {
        if (!(variableDeclaration.getSymbol().getType().getClass() == IntType.class
                || variableDeclaration.getSymbol().getType().getClass() == BoolType.class)){
        addTypeError(variableDeclaration, "variableDeclarationError");
      }
      return null;
    }
  }
}