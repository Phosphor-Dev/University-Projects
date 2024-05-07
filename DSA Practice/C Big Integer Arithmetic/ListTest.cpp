/*********************************************************************************
* Steven, stabilis
* 2021 Spring CSE101 PA5
* ListTest.cpp
*********************************************************************************/

#include "List.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    cout << "THIS IS THE TEST SCRIPT FOR List.cpp" << endl;
    List newList;
    if (newList.isEmpty())
    {
        cout << "   List has been created!" << endl;
    }
    cout << "HERE" << endl;
    for (int i = 0; i < 10; i++)
    {
        newList.insertAfter(i);
        newList.moveNext();
        cout << i << " has been Inserted!" << endl;
    }
    for (newList.moveFront(); newList.position() < newList.size(); newList.moveNext())
    {

        cout << "   Element: " << newList.peekNext() << endl;
    }
    cout << "DELETING ONE ELEMENT" << endl;
    for (int i = 0; i < 5; i++)
        newList.movePrev();
    cout << "(Element: " << newList.peekNext() << ")" << endl;
    newList.eraseAfter();
    for (newList.moveFront(); newList.position() < newList.size(); newList.moveNext())
    {
        cout << "   Element: " << newList.peekNext() << endl;
    }
    cout << "DELETING ANOTHER ELEMENT" << endl;
    for (int i = 0; i < 6; i++)
        newList.movePrev();
    cout << "(Element: " << newList.peekPrev() << ")" << endl;
    newList.eraseBefore();
    for (newList.moveFront(); newList.position() < newList.size(); newList.moveNext())
    {
        cout << "   Element: " << newList.peekNext() << endl;
    }
    cout << "TESTING STRING AND PRINTING" << endl;
    cout << newList << endl;
    List testCleanUp;
    for (int i = 0; i < 5; i++)
    {
        testCleanUp.insertAfter(5);
    }
    for (int i = 0; i < 5; i++)
    {
        testCleanUp.insertAfter(3);
    }
    testCleanUp.moveFront();
    for (int i = 0; i < 5; i++)
    {
        testCleanUp.moveNext();
    }
    cout << testCleanUp << endl;
    List y = List(testCleanUp);
    cout << y << endl;
    List x = y;
    testCleanUp.moveFront();
    testCleanUp.cleanup();
    cout << testCleanUp << endl;
    List cleanUp2;
    cleanUp2.insertAfter(5);
    cleanUp2.moveNext();
    cout << "inserted 5!" << endl;
    cleanUp2.insertAfter(8);
    cleanUp2.moveNext();
    cout << "inserted 8!" << endl;
    cleanUp2.insertAfter(5);
    cleanUp2.moveNext();
    cout << "inserted 5!" << endl;
    cleanUp2.insertAfter(3);
    cleanUp2.moveNext();
    cout << "inserted 3!" << endl;
    cleanUp2.insertAfter(3);
    cout << cleanUp2 << endl;
    cleanUp2.cleanup();
    cout << cleanUp2 << endl;
    List concatList = cleanUp2.concat(testCleanUp);
    cout << concatList << endl;
    List finalTest;
    finalTest.insertBefore(4);
    finalTest.insertBefore(5);
    finalTest.insertBefore(3);
    finalTest.insertBefore(3);
    finalTest.insertBefore(5);
    finalTest.insertBefore(6);
    finalTest.insertBefore(7);
    cout << finalTest << endl;
    for (finalTest.moveFront(); finalTest.position() < 4; finalTest.moveNext())
    {
        cout << "position: " << finalTest.position() << endl;
    }
    cout << finalTest.peekPrev() << " and " << finalTest.peekNext() << endl;
    finalTest.cleanup();
    cout << finalTest << endl;
    cout << finalTest.peekPrev() << " and " << finalTest.peekNext() << endl;
    List A;
    A.insertBefore(5);
    A.insertBefore(10);
    A.insertBefore(15);
    A.insertBefore(176);
    A.insertBefore(200);
    A.findPrev(15);
    A.eraseBefore();
    if (A.position() != 1)
        cout << "error" << endl;
    A.insertAfter(175);
    A.eraseBefore();
    if (A.position() != 0)
        cout << "error2" << endl;
    A.insertBefore(15);
    A.insertBefore(50);
    if (A.position() != 2)
        cout << "error3" << endl;
    A.findNext(15);
    A.eraseBefore();
    if (A.position() != 3)
        cout << "error4" << endl;
    A.findPrev(15);
    if (A.position() != 0)
        cout << "error5" << endl;
    A.moveBack();
    if (A.position() != 5)
        cout << "error6" << endl;
    A.eraseBefore();
    A.eraseBefore();
    A.eraseBefore();
    A.eraseBefore();
    A.eraseBefore();
    if (A.position() != 0)
        cout << "error7" << endl;
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(1);
    A.findPrev(3);
    cout << A << endl;
    cout << A.position() << endl;
    A.cleanup();
    if (A.position() != 2)
    {
        cout << A.position() << endl;
    }
    A.clear();
    A.insertBefore(2);
    A.insertBefore(1);
    List B;
    B.insertAfter(2);
    cout << (A == B) << endl;
    return 0;
}