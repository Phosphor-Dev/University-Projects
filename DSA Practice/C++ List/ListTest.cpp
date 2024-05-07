/*********************************************************************************
* Steven, stabilis
* 2021 Spring CSE101 PA4
* List Test.cpp
*********************************************************************************/

#include <iostream>
#include <string>
#include "List.h"
#include "List.cpp"

using namespace std;
List L;
Z.insertAfter(5);
Z.insertBefore(2);
cout << endl;
cout << "   Z = " << Z << endl;
Z.moveFront();
Z.insertBefore(4);
Z.moveBack();
Z.insertAfter(7);
cout << endl;
cout << "   Z = " << Z << endl;
Z.eraseAfter();
Z.eraseBefore();
cout << endl;
cout << "   Z = " << Z << endl;
Z.movePrev();
Z.eraseBefore();
cout << "   Z = " << Z << endl;
Z.moveNext();
Z.eraseAfter();
cout << "   Z = " << Z << endl;
cout << endl;
List A;
List B;
List AB;
A.insertBefore(7);
A.insertBefore(3);
A.insertBefore(25);
B.insertAfter(11);
B.insertAfter(8);
B.insertAfter(42);
cout << "   A = " << A << endl;
cout << "   B = " << B << endl;
AB = A.concat(Z);
cout << "   AB = " << AB << endl;
YZ.cleanup();
List X;
List Y;
X.insertBefore(12);
X.insertBefore(3);
X.insertBefore(9);
Y.insertAfter(9);
Y.insertAfter(12);
Y.insertAfter(3);
cout << "   Equal? " << (X==Y?"True":"False") << endl;