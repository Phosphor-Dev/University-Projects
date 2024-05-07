package crux.ir;

import crux.ast.*;
import crux.ast.SymbolTable.Symbol;
import crux.ast.traversal.NodeVisitor;
import crux.ast.types.*;
import crux.ir.insts.*;

import java.util.*;

class InstPair {
  Instruction start;
  Instruction end;
  Variable val;

  InstPair(Instruction start, Instruction end, Variable val){
    this.start = start;
    this.end = end;
    this.val = val;
  }

  Instruction getStart(){
    return start;
  }
  Instruction getEnd(){
    return end;
  }
  Variable getVal(){
    return val;
  }
}


/**
 * Convert AST to IR and build the CFG
 */
public final class ASTLower implements NodeVisitor<InstPair> {
  private Program mCurrentProgram = null;
  private Function mCurrentFunction = null;
  ////////////////////////////////////////
  private Stack<InstPair> breakList = new Stack<>();
  //private Instruction mCurrentLoopExit = null;
  ////////////////////////////////////////
  private Map<Symbol, LocalVar> mCurrentLocalVarMap = null;

  /**
   * A constructor to initialize member variables
   */
  public ASTLower() {}

  public Program lower(DeclarationList ast) {
    visit(ast);
    return mCurrentProgram;
  }

  @Override
  public InstPair visit(DeclarationList declarationList) {  //COMPLETED
    mCurrentProgram = new Program();
    for (var e : declarationList.getChildren()) {
      e.accept(this);
    }
    return null;
  }

  /**
   * This visitor should create a Function instance for the functionDefinition node, add parameters
   * to the localVarMap, add the function to the program, and init the function start Instruction.
   */
  @Override
  public InstPair visit(FunctionDefinition functionDefinition) {  //COMPLETED
    mCurrentLocalVarMap = new HashMap<>();
    String name = functionDefinition.getSymbol().getName();
    mCurrentFunction = new Function(name, (FuncType) functionDefinition.getSymbol().getType());
    List<LocalVar> args = new ArrayList<>();
    for (var e : functionDefinition.getParameters()) {
      LocalVar localVar = mCurrentFunction.getTempVar(e.getType(), e.getName());
      mCurrentLocalVarMap.put(e, localVar);
      args.add(localVar);
    }
    mCurrentFunction.setArguments(args);
    mCurrentFunction.setStart(new NopInst());
    InstPair temp = functionDefinition.getStatements().accept(this);
    mCurrentFunction.getStart().setNext(0, temp.start);
    mCurrentProgram.addFunction(mCurrentFunction);
    mCurrentLocalVarMap = null;
    mCurrentFunction = null;
    return null;
  }

  @Override
  public InstPair visit(StatementList statementList) {
    Instruction lastInst = null;

    ArrayList<InstPair> list = new ArrayList<>();
    for (var e : statementList.getChildren()) {
      InstPair statement = e.accept(this);
      list.add(statement);
    }

    NopInst nop = new NopInst();

    if (list.size() == 0) {
      return new InstPair(nop, nop, null);
    } else {
      nop.setNext(0, list.get(0).start);

      for (int i = 0; i < list.size() - 1; i++) {
        list.get(i).end.setNext(0, list.get(i + 1).start);
      }
      lastInst = list.get(list.size() - 1).end;
      return new InstPair(nop, lastInst, null);
    }
  }

  /**
   * Declarations, could be either local or Global
   */
  @Override
  public InstPair visit(VariableDeclaration variableDeclaration) {  //COMPLETED
    if (mCurrentFunction == null) {
      IntegerConstant ic = IntegerConstant.get(mCurrentProgram, 1);
      var global = new GlobalDecl(variableDeclaration.getSymbol(), ic);
      mCurrentProgram.addGlobalVar(global);
      return null;
    } else {
      Type type = variableDeclaration.getSymbol().getType();
      String name = variableDeclaration.getSymbol().getName();
      LocalVar localVar = mCurrentFunction.getTempVar(type, name);
      mCurrentLocalVarMap.put(variableDeclaration.getSymbol(), localVar);
      NopInst nop = new NopInst();
      return new InstPair(nop, nop, localVar);
    }
  }

  /**
   * Create a declaration for array and connected it to the CFG
   */
  @Override
  public InstPair visit(ArrayDeclaration arrayDeclaration) {  //COMPLETED
    long size = ((ArrayType) arrayDeclaration.getSymbol().getType()).getExtent();
    IntegerConstant ic = IntegerConstant.get(mCurrentProgram, size);
    GlobalDecl global = new GlobalDecl(arrayDeclaration.getSymbol(), ic);
    mCurrentProgram.addGlobalVar(global);
    return null;
  }

  /**
   * LookUp the name in the map(s). For globals, we should do a load to get the value to load into a
   * LocalVar.
   */
  @Override
  public InstPair visit(VarAccess name) {  //COMPLETED MAYBE
    if (mCurrentLocalVarMap.containsKey(name.getSymbol())) {
      NopInst nop = new NopInst();
      return new InstPair(nop, nop, mCurrentLocalVarMap.get(name.getSymbol()));
    } else {
      //Create addressVar AND addressAt
      AddressVar addressVar = mCurrentFunction.getTempAddressVar(name.getSymbol().getType());
      AddressAt addressAt = new AddressAt(addressVar, name.getSymbol());
      //Create LocalVar to store value from Global
      LocalVar destVar = mCurrentFunction.getTempVar(name.getSymbol().getType());
      LoadInst loadInst = new LoadInst(destVar, addressAt.getDst());
      LocalVar dest = loadInst.getDst();
      //Store Back
      StoreInst storeInst = new StoreInst(destVar, addressVar);
      addressAt.setNext(0, loadInst);
      loadInst.setNext(0, storeInst);

      //Connect Instructions
      //addressAt.setNext(0,loadInst);
      return new InstPair(addressAt, storeInst, dest);

    }
  }

  /**
   * If the location is a VarAccess to a LocalVar, copy the value to it. If the location is a
   * VarAccess to a global, store the value. If the location is ArrayAccess, store the value.
   */
  @Override
  public InstPair visit(Assignment assignment) {
    InstPair rhs = assignment.getValue().accept(this);
    if (assignment.getLocation() instanceof VarAccess) { //Local
      if (mCurrentLocalVarMap.get(((VarAccess) assignment.getLocation()).getSymbol()) != null) {
        InstPair lhs = assignment.getLocation().accept(this);
        CopyInst copyInst = new CopyInst((LocalVar) lhs.getVal(), rhs.getVal());
        lhs.getEnd().setNext(0, rhs.getStart());
        rhs.getEnd().setNext(0, copyInst);
        return new InstPair(lhs.getStart(), copyInst, null);
      } else {
        AddressVar tempAddrVar = mCurrentFunction.getTempAddressVar(assignment.getType());
        StoreInst sd = new StoreInst((LocalVar) rhs.getVal(), tempAddrVar);
        AddressAt aa = new AddressAt(tempAddrVar, ((VarAccess) assignment.getLocation()).getSymbol());
        aa.setNext(0, rhs.getStart());
        rhs.getEnd().setNext(0, sd);
        return new InstPair(aa, sd, null);
      }
    } else {
      ArrayAccess va = (ArrayAccess) assignment.getLocation();
      InstPair index = va.getIndex().accept(this);
      AddressVar tempAddrVar = mCurrentFunction.getTempAddressVar(assignment.getType());
      StoreInst sd = new StoreInst((LocalVar) rhs.getVal(), tempAddrVar);
      AddressAt aa = new AddressAt(tempAddrVar, ((ArrayAccess) assignment.getLocation()).getBase(), (LocalVar) index.getVal());
      index.getEnd().setNext(0, aa);
      aa.setNext(0, rhs.getStart());
      rhs.getEnd().setNext(0, sd);
      return new InstPair(index.getStart(), sd, null);
    }
  }

  /**
   * Lower a Call.
   */
  @Override
  public InstPair visit(Call call) {
    List<LocalVar> list = new ArrayList<>();
    InstPair previousInst = null;
    Instruction tempStart = null;
    Instruction tempEnd = null;
    for (var e: call.getArguments()){
      previousInst = e.accept(this);
      list.add((LocalVar) previousInst.getVal());
      if (tempStart == null) {
        tempStart = previousInst.getStart();
      } else {
        tempEnd.setNext(0, previousInst.getStart());
      }
      tempEnd = previousInst.getEnd();
    }
    InstPair tempPair = new InstPair(tempStart, tempEnd, null);
    Symbol calleeAddr = call.getCallee();
    Type calleeType = calleeAddr.getType();
    LocalVar retType = mCurrentFunction.getTempVar(((FuncType) calleeType).getRet());
    CallInst callInst = new CallInst(retType, calleeAddr, list);
    if (previousInst != null){
      tempPair.getEnd().setNext(0, callInst);
      return new InstPair(tempPair.getStart(), callInst, retType);
    }
    return new InstPair(callInst, callInst, callInst.getDst());
  }


  /**
   * Handle operations like arithmetics and comparisons. Also handle logical operations (and,
   * or, not).
   */
  @Override
  public InstPair visit(OpExpr operation) { //COMPLETED
    InstPair left = null;
    InstPair right = null;
    LocalVar tempVar = mCurrentFunction.getTempVar(operation.getType());
    if (operation.getOp() != OpExpr.Operation.LOGIC_AND && operation.getOp() != OpExpr.Operation.LOGIC_OR && operation.getOp() != OpExpr.Operation.LOGIC_NOT) {
      left = operation.getLeft().accept(this);
      right = operation.getRight().accept(this);
      left.getEnd().setNext(0, right.getStart());
      switch (operation.getOp()) {
        //COMPARATORS
        case GE:
          CompareInst geInst = new CompareInst(tempVar, CompareInst.Predicate.GE, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, geInst);
          return new InstPair(left.getStart(), geInst, tempVar);
        case GT:
          CompareInst gtInst = new CompareInst(tempVar, CompareInst.Predicate.GT, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, gtInst);
          return new InstPair(left.getStart(), gtInst, tempVar);
        case LE:
          CompareInst leInst = new CompareInst(tempVar, CompareInst.Predicate.LE, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, leInst);
          return new InstPair(left.getStart(), leInst, tempVar);
        case LT:
          CompareInst ltInst = new CompareInst(tempVar, CompareInst.Predicate.LT, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, ltInst);
          return new InstPair(left.getStart(), ltInst, tempVar);
        case EQ:
          CompareInst eqInst = new CompareInst(tempVar, CompareInst.Predicate.EQ, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, eqInst);
          return new InstPair(left.getStart(), eqInst, tempVar);
        case NE:
          CompareInst neInst = new CompareInst(tempVar, CompareInst.Predicate.NE, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, neInst);
          return new InstPair(left.getStart(), neInst, tempVar);
        //ARITHMETIC
        case ADD:
          BinaryOperator addInst = new BinaryOperator(BinaryOperator.Op.Add, tempVar, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, addInst);
          return new InstPair(left.getStart(), addInst, tempVar);
        case SUB:
          BinaryOperator subInst = new BinaryOperator(BinaryOperator.Op.Sub, tempVar, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, subInst);
          return new InstPair(left.getStart(), subInst, tempVar);
        case MULT:
          BinaryOperator multInst = new BinaryOperator(BinaryOperator.Op.Mul, tempVar, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, multInst);
          return new InstPair(left.getStart(), multInst, tempVar);
        case DIV:
          BinaryOperator divInst = new BinaryOperator(BinaryOperator.Op.Div, tempVar, (LocalVar) left.getVal(), (LocalVar) right.getVal());
          right.getEnd().setNext(0, divInst);
          return new InstPair(left.getStart(), divInst, tempVar);
        //NEGATION
        }
    }else {
      InstPair lhs = operation.getLeft().accept(this);
      JumpInst jumpInst = new JumpInst((LocalVar) lhs.getVal());
      NopInst nopInst = new NopInst();

      if (operation.getOp() == OpExpr.Operation.LOGIC_NOT) {
        UnaryNotInst notInst = new UnaryNotInst(tempVar, (LocalVar) lhs.getVal());
        lhs.getEnd().setNext(0, notInst);
        return new InstPair(lhs.getStart(), notInst, tempVar);
      } else {
        InstPair rhs = operation.getRight().accept(this);
        switch (operation.getOp()) {
          case LOGIC_OR:
            CopyInst copyInstOR0 = new CopyInst(tempVar, rhs.getVal());

            BooleanConstant valueTrue = BooleanConstant.get(mCurrentProgram, true);
            CopyInst copyInstOR1 = new CopyInst(tempVar, valueTrue);//

            lhs.getEnd().setNext(0, jumpInst);

            jumpInst.setNext(0, rhs.getStart());
            rhs.getEnd().setNext(0, copyInstOR0);
            copyInstOR0.setNext(0, nopInst);

            jumpInst.setNext(1, copyInstOR1);
            copyInstOR1.setNext(0, nopInst);

            return new InstPair(lhs.getStart(), nopInst, tempVar);

          case LOGIC_AND:
            BooleanConstant value = BooleanConstant.get(mCurrentProgram, false);
            CopyInst copyInstAND0 = new CopyInst(tempVar, value);//
            CopyInst copyInstAND1 = new CopyInst(tempVar, rhs.getVal());

            lhs.getEnd().setNext(0, jumpInst);

            jumpInst.setNext(0, copyInstAND0);
            copyInstAND0.setNext(0, nopInst);

            jumpInst.setNext(1, rhs.getStart());
            rhs.getEnd().setNext(0, copyInstAND1);
            copyInstAND1.setNext(0, nopInst);

            return new InstPair(lhs.getStart(), nopInst, tempVar);
        }
      }
    }
    return null;
  }

  /**
   * It should compute the address into the array, do the load, and return the value in a LocalVar.
   */
  @Override
  public InstPair visit(ArrayAccess access) {
    InstPair index = access.getIndex().accept(this);
    AddressVar addressVar = mCurrentFunction.getTempAddressVar(access.getType());
    AddressAt addressAt = new AddressAt(addressVar, access.getBase(), (LocalVar) index.getVal());
    //Create LocalVar to store value from Global
    LocalVar destVar = mCurrentFunction.getTempVar(access.getType());
    LoadInst loadInst = new LoadInst(destVar, addressAt.getDst());
    LocalVar dest = loadInst.getDst();
    //Store Back
    StoreInst storeInst = new StoreInst(destVar, addressVar);

    index.getEnd().setNext(0, addressAt);
    addressAt.setNext(0, loadInst);
    loadInst.setNext(0, storeInst);

    //Connect Instructions
    //addressAt.setNext(0,loadInst);
    return new InstPair(index.getStart(), storeInst, dest);
  }

  /**
   * Copy the literal into a tempVar
   */
  @Override
  public InstPair visit(LiteralBool literalBool) {  //COMPLETED
    BooleanConstant value = BooleanConstant.get(mCurrentProgram, literalBool.getValue());
    LocalVar localVar = mCurrentFunction.getTempVar(new BoolType());
    CopyInst copyInst = new CopyInst(localVar, value);
    return new InstPair(copyInst, copyInst, localVar);
  }

  /**
   * Copy the literal into a tempVar
   */
  @Override
  public InstPair visit(LiteralInt literalInt) {  //COMPLETED
    IntegerConstant value = IntegerConstant.get(mCurrentProgram, literalInt.getValue());
    LocalVar localVar = mCurrentFunction.getTempVar(new IntType());
    CopyInst copyInst = new CopyInst(localVar, value);
    return new InstPair(copyInst, copyInst, localVar);
  }

  /**
   * Lower a Return.
   */
  @Override
  public InstPair visit(Return ret) { //COMPLETED
    InstPair retPair = ret.getValue().accept(this);
    ReturnInst retInst = new ReturnInst((LocalVar) retPair.getVal());
    retPair.getEnd().setNext(0, retInst);
    return new InstPair(retPair.getStart(), retInst, retPair.getVal());

  }

  /**
   * Implement If Then Else statements.
   */
  @Override
  public InstPair visit(IfElseBranch ifElseBranch) {
    //Visit Condition
    InstPair condition = ifElseBranch.getCondition().accept(this);

    //Create jumpInst
    JumpInst jumpInst = new JumpInst((LocalVar) condition.getVal());


    //Visit thenBlock
    InstPair thenBlock = ifElseBranch.getThenBlock().accept(this);

    //Visit elseBlock
    InstPair elseBlock = ifElseBranch.getElseBlock().accept(this);

    //Merge Blocks Into NopInst
    NopInst nopInst = new NopInst();
    condition.getEnd().setNext(0, jumpInst);
    jumpInst.setNext(0, elseBlock.getStart());
    jumpInst.setNext(1, thenBlock.getStart());
    thenBlock.getEnd().setNext(0, nopInst);
    elseBlock.getEnd().setNext(0, nopInst);

    //Return InstPair from Condition Inst to NopInst
    return new InstPair(condition.getStart(), nopInst, null);
  }

  /**
   * Implement for loops.
   */
  @Override
  public InstPair visit(For loop) {
    InstPair init = loop.getInit().accept(this);
    InstPair cond = loop.getCond().accept(this);
    InstPair increment = loop.getIncrement().accept(this);

    NopInst exit = new NopInst();
    InstPair brkPair = new InstPair(exit, exit, null);

    breakList.push(brkPair);
    InstPair list = loop.getBody().accept(this);
    JumpInst jp = new JumpInst((LocalVar) cond.getVal());

    init.getEnd().setNext(0, cond.getStart());
    cond.getEnd().setNext(0, jp);
    jp.setNext(0, exit);
    jp.setNext(1, list.getStart());
    list.getEnd().setNext(0, increment.getStart());
    increment.end.setNext(0, cond.start);

    exit.setNext(0, new NopInst());

    return new InstPair(init.getStart(), exit, null);

  }

  /**
   * Break Node
   */
  @Override
  public InstPair visit(Break brk) {
    InstPair breakInst = breakList.pop();
    return new InstPair(breakInst.getStart(), breakInst.getEnd(), null);
  }
}
