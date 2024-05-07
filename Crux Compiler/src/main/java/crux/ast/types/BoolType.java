package crux.ast.types;

/**
 * Types for Booleans values This should implement the equivalent methods along with and,or, and not
 * equivalent will check if the param is instance of BoolType
 */
public final class BoolType extends Type implements java.io.Serializable {
  static final long serialVersionUID = 12022L;

  @Override
  public String toString() {
    return "bool";
  }

  @Override
  public boolean equivalent(Type that) {
    return that.getClass() == BoolType.class;
  }

  @Override
  public Type and(Type that) {
    if (equivalent(that)) {
      return new BoolType();
    } else {
      return super.and(that);
    }
  }

  @Override
  public Type or(Type that) {
    if (equivalent(that)) {
      return new BoolType();
    } else {
      return super.or(that);
    }
  }

  @Override
  public Type not() {
    return new BoolType();
  }

  @Override
  public Type compare(Type other) {
    if (equivalent(other)) {
      return new BoolType();
    }
    return super.compare(other);
  }

  @Override
  public Type assign(Type that) {
    if (equivalent(that)) {
      return new BoolType();
    } else {
      return super.assign(that);
    }
  }
}