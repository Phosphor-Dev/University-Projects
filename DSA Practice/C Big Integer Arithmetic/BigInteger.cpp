/*********************************************************************************
* Steven, stabilis
* 2021 Spring CSE101 PA5
* BigInteger.cpp
*********************************************************************************/
#include "BigInteger.h"
#include <string>
#include <iostream>

using namespace std;

// Class Constructors & Destructors ----------------------------------------
BigInteger();

BigInteger(std::string s);

BigInteger(const BigInteger &N);

// Access functions --------------------------------------------------------
int sign();

int compare(BigInteger N);

void makeZero();

void negate();

// BigInteger Arithmetic operations ----------------------------------------
BigInteger add(const BigInteger &N);

BigInteger sub(const BigInteger &N);

BigInteger mult(const BigInteger &N);

// Other Functions ---------------------------------------------------------
std::string to_string();

void negateList(List &L);

void sumList(List &S, List A, List B, int sgn);

int normalizeList(List &L);

void shiftList(List &L, int p);

void scalarMultList(List &L, LIST_ELEMENT m);
