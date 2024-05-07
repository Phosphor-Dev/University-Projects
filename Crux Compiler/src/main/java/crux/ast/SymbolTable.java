package crux.ast;

import crux.ast.types.*;

import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Symbol table will map each symbol from Crux source code to its declaration or appearance in the
 * source. The symbol table is made up of scopes, Each scope is a map which maps an identifier to
 * its symbol. Scopes are inserted to the table starting from the first scope (Global Scope). The
 * Global scope is the first scope in each Crux program, and it contains all the built-in functions
 * and names. The symbol table is an ArrayList of scopes.
 */
public final class SymbolTable {

  /**
   * Symbol is used to record the name and type of names in the code. Names include function names,
   * global variables, global arrays, and local variables.
   */
  static public final class Symbol implements java.io.Serializable {
    static final long serialVersionUID = 12022L;
    private final String name;
    private final Type type;
    private final String error;

    /**
     *
     * @param name String
     * @param type the Type
     */
    private Symbol(String name, Type type) {
      this.name = name;
      this.type = type;
      this.error = null;
    }

    private Symbol(String name, String error) {
      this.name = name;
      this.type = null;
      this.error = error;
    }

    /**
     *
     * @return String the name
     */
    public String getName() {
      return name;
    }

    /**
     *
     * @return the type
     */
    public Type getType() {
      return type;
    }

    @Override
    public String toString() {
      if (error != null) {
        return String.format("Symbol(%s:%s)", name, error);
      }
      return String.format("Symbol(%s:%s)", name, type);
    }

    public String toString(boolean includeType) {
      if (error != null) {
        return toString();
      }
      return includeType ? toString() : String.format("Symbol(%s)", name);
    }
  }

  private final PrintStream err;
  private final ArrayList<Map<String, Symbol>> symbolScopes = new ArrayList<>();

  private boolean encounteredError = false;

  SymbolTable(PrintStream err) {
    this.err = err;
    HashMap<String, Symbol> globalScopes = new HashMap<>();

    TypeList readIntList = TypeList.of();
    globalScopes.put("readInt", new Symbol("readInt", new FuncType(readIntList, new IntType())));

    TypeList readCharList = TypeList.of();
    globalScopes.put("readChar", new Symbol("readChar", new FuncType(readCharList, new IntType())));

    TypeList printBoolList = TypeList.of();
    globalScopes.put("printBool", new Symbol("printBool", new FuncType(printBoolList, new VoidType())));

    TypeList printIntList = TypeList.of();
    globalScopes.put("printInt", new Symbol("printInt", new FuncType(printIntList, new VoidType())));

    TypeList printCharList = TypeList.of();
    globalScopes.put("printChar", new Symbol("printChar", new FuncType(printCharList, new VoidType())));

    TypeList printlnList = TypeList.of();
    globalScopes.put("println", new Symbol("println", new FuncType(printlnList, new VoidType())));



    symbolScopes.add(globalScopes); //Global Scope
    //TODO
  }

  boolean hasEncounteredError() {
    return encounteredError;
  }

  /**
   * Called to tell symbol table we entered a new scope.
   */

  void enter() {
    symbolScopes.add(new HashMap<>());
    //TODO
  }

  /**
   * Called to tell symbol table we are exiting a scope.
   */

  void exit() {
    symbolScopes.remove(symbolScopes.size() - 1);
    //TODO
  }

  /**
   * Insert a symbol to the table at the most recent scope. if the name already exists in the
   * current scope that's a declaration error.
   */
  Symbol add(Position pos, String name, Type type) {
    //TODO
    Map<String, Symbol> currentScope = symbolScopes.get(symbolScopes.size() - 1);
      if (currentScope.get(name) == null) { //Has an error attached
        Symbol newSymbol = new Symbol(name, type);
        currentScope.put(name, newSymbol);
        return newSymbol;
      } else {
        err.printf("DeclarationError%s[Could not declare %s.]%n", pos, name);
        encounteredError = true;
        return new Symbol(name, "DeclarationError");
      }
  }

  /**
   * lookup a name in the SymbolTable, if the name not found in the table it should encounter an
   * error and return a symbol with ResolveSymbolError error. if the symbol is found then return it.
   */
  Symbol lookup(Position pos, String name) {
    var symbol = find(name);
    if (symbol == null) {
      err.printf("ResolveSymbolError%s[Could not find %s.]%n", pos, name);
      encounteredError = true;
      return new Symbol(name, "ResolveSymbolError");
    } else {
      return symbol;
    }
  }

  /**
   * Try to find a symbol in the table starting from the most recent scope.
   */
  private Symbol find(String name) {
    for (int i = symbolScopes.size() - 1; i >= 0; i--) {
      Map<String, Symbol> currentScope = symbolScopes.get(i);
      if (currentScope.containsKey(name)) {
        return currentScope.get(name);
      }
    }
    return null;
    }
}
