//-----------------------------------------------------------------------------
// BigInteger.h
// Header file for the BigInteger ADT
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "List.h"

#ifndef BIG_INTEGER_H_INCLUDE_
#define BIG_INTEGER_H_INCLUDE_

// Exported type  -------------------------------------------------------------
class BigInteger
{

private:
   // BigInteger Fields
   int signum;  // +1 (positive), -1 (negative), 0 (zero)
   List digits; //

public:
   // Class Constructors & Destructors ----------------------------------------

   // BigInteger()
   // Constructor that creates a new BigInteger in the zero state:
   // signum=0, digits=().
   BigInteger();

   // BigInteger()
   // Constructor that creates a new BigInteger from the string s.
   // pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
   BigInteger(std::string s);

   // BigInteger()
   // Constructor that copies the BigInteger N.
   BigInteger(const BigInteger &N);

   //~BigInteger()
   // Destructor (optional)
   //~BigInteger();

   // Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this BigInteger is positive,
   // negative or 0, respectively.
   int sign();

   // compare()
   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.
   int compare(BigInteger N);

   // Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this BigInteger to the zero state.
   void makeZero();

   // negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of
   // this BigInteger positive <--> negative.
   void negate();

   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N.
   BigInteger add(const BigInteger &N);

   // sub()
   // Returns a BigInteger representing the difference of this and N.
   BigInteger sub(const BigInteger &N);

   // mult()
   // Returns a BigInteger representing the product of this and N.
   BigInteger mult(const BigInteger &N);

   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.
   std::string to_string();

   // negateList()
   // Changes the sign of each integer in List L. Used by sub().
   void negateList(List &L);

   // sumList()
   // Overwrites the state of S with A + sgn*B (considered as vectors).
   // Used by both sum() and sub().
   void sumList(List &S, List A, List B, int sgn);

   // normalizeList()
   // Performs carries from right to left (least to most significant
   // digits), then returns the sign of the resulting integer. Used
   // by add(), sub() and mult().
   int normalizeList(List &L);

   // shiftList()
   // Prepends p zero digits to L, multiplying L by base^p. Used by mult().
   void shiftList(List &L, int p);

   // scalarMultList()
   // Multiplies L (considered as a vector) by m. Used by mult().
   void scalarMultList(List &L, LIST_ELEMENT m);

   // Overriden Operators -----------------------------------------------------

   // operator<<()
   // Inserts string representation of N into stream.
   friend std::ostream &operator<<(std::ostream &stream, BigInteger N);

   // operator==()
   // Returns true if and only if A equals B.
   friend bool operator==(BigInteger &A, const BigInteger &B);

   // operator<()
   // Returns true if and only if A is less than B.
   friend bool operator<(BigInteger &A, const BigInteger &B);

   // operator<=()
   // Returns true if and only if A is less than or equal to B.
   friend bool operator<=(BigInteger &A, const BigInteger &B);

   // operator>()
   // Returns true if and only if A is greater than B.
   friend bool operator>(BigInteger &A, const BigInteger &B);

   // operator>=()
   // Returns true if and only if A is greater than or equal to B.
   friend bool operator>=(BigInteger &A, const BigInteger &B);

   // operator+()
   // Returns the sum A+B.
   friend BigInteger operator+(BigInteger A, const BigInteger &B);

   // operator+=()
   // Overwrites A with the sum A+B.
   friend BigInteger operator+=(BigInteger &A, const BigInteger &B);

   // operator-()
   // Returns the difference A-B.
   friend BigInteger operator-(BigInteger A, const BigInteger &B);

   // operator-=()
   // Overwrites A with the difference A-B.
   friend BigInteger operator-=(BigInteger &A, const BigInteger &B);

   // operator*()
   // Returns the product A*B.
   friend BigInteger operator*(BigInteger A, const BigInteger &B);

   // operator*=()
   // Overwrites A with the product A*B.
   friend BigInteger operator*=(BigInteger &A, const BigInteger &B);
};

#endif