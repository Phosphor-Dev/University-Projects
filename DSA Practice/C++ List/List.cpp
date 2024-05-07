/*********************************************************************************
* Steven, stabilis
* 2021 Spring CSE101 PA4
* List.cpp
*********************************************************************************/

#include "List.h"
#include <string>
#include <iostream>

using namespace std;

//creates new Node
List::Node::Node(int x)
{
    data = x;
    next = nullptr;
    prev = nullptr;
}

//creates new List in empty state
List::List()
{
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

//creates copy of constructor
List::List(const List &L)
{
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node *N = L.frontDummy;
    N = N->next;
    while (N != L.backDummy)
    {
        insertAfter(N->data);
        moveNext();
        N = N->next;
    }
    this->moveFront();
}

//Destructor
List::~List()
{
    moveBack();
    while (num_elements > 1) eraseBefore();
    clear();
    Node *back = backDummy;
    Node *front = frontDummy;
    backDummy->next = nullptr;
    backDummy->prev = nullptr;
    frontDummy->next = nullptr;
    frontDummy->prev = nullptr;
    delete front;
    delete back;
}

bool List::isEmpty()
{
    return (num_elements == 0);
}

int List::size()
{
    return num_elements;
}

int List::position()
{
    return pos_cursor;
}

void List::moveFront()
{
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
}

void List::moveBack()
{
    pos_cursor = size();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

int List::peekNext()
{
    return afterCursor->data;
}

int List::peekPrev()
{
    return beforeCursor->data;
}

int List::moveNext()
{
    if (position() >= size())
    {
        cerr << "moveNext() Error: Back of list." << endl;
        exit(EXIT_FAILURE);
    }
    int element = afterCursor->data;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return element;
}

int List::movePrev()
{
    if (position() == 0)
    {
        cerr << "movePrev() Error: Front of list." << endl;
        exit(EXIT_FAILURE);
    }
    int element = beforeCursor->data;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return element;
}

void List::insertAfter(int x)
{
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    afterCursor->prev = N;
    beforeCursor->next = N;
    afterCursor = N;
    num_elements++;
}

void List::insertBefore(int x)
{
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    afterCursor->prev = N;
    beforeCursor->next = N;
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
}

void List::eraseAfter()
{
    if (isEmpty())
    {
        cerr << "eraseAfter() Empty List." << endl;
        exit(EXIT_FAILURE);
    }
    if (position() == size())
    {
        cerr << "eraseAfter() End of the list." << endl;
        exit(EXIT_FAILURE);
    }
    Node *N = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;
    N->next = nullptr;
    N->prev = nullptr;
    num_elements--;
    delete N;
}

void List::eraseBefore()
{
    if (isEmpty())
    {
        cerr << "eraseBefore() Error: Empty List." << endl;
        exit(EXIT_FAILURE);
    }
    if (position() == 0)
    {
        cerr << "eraseBefore() Error: Front of the list." << endl;
        exit(EXIT_FAILURE);
    }
    Node *N = beforeCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    beforeCursor = beforeCursor->prev;
    N->next = nullptr;
    N->prev = nullptr;
    num_elements--;
    pos_cursor--;
    delete N;
}

int List::findNext(int x)
{
    while (pos_cursor != num_elements) if(moveNext() == x) return (pos_cursor);
    return (-1);
}

int List::findPrev(int x)
{
    while (pos_cursor != 0) if(movePrev() == x) return (pos_cursor);
    return (-1);
}

void List::cleanup()
{
    int check, pos;
    if (position() != 0 && position() != size())
    {
        int prev;
        pos = position();
        check = peekPrev();
        prev = findPrev(check);
        while (prev != -1 && position() != 0)
        {
            while (position() < pos) moveNext();
            check = peekPrev();
            pos = position() - 1;
            prev = findPrev(check);
        }
    }
    else if (position() == 0)
    {
        pos = 0;
        check = -1;
    }
    else if (position() == size())
    {
        pos = 0;
        check = -2;
    }
    List L = List(*this);
    clear();
    for (L.moveFront(); L.position() < L.size(); L.moveNext())
    {
        moveFront();
        if (findNext(L.peekNext()) == -1)
        {
            moveBack();
            insertBefore(L.peekNext());
        }
    }
    moveFront();
    if (check != -1 && check != -2)
    {
        findNext(check);
        moveNext();
    }
    else if (check == -1) moveFront();
    else if (check == -2) moveBack();
}

void List::clear()
{
    moveFront();
    while (!isEmpty()) eraseAfter();
}

List List::concat(const List &L)
{
    List temp;
    Node *N = this->frontDummy->next;
    Node *M = L.frontDummy->next;
    while (N->next != nullptr)
    {
        temp.insertBefore(N->data);
        N = N->next;
    }
    while (M->next != nullptr)
    {
        temp.insertBefore(M->data);
        M = M->next;
    }
    temp.moveFront();
    return temp;
}

string List::to_string()
{
    Node *N = nullptr;
    N = N->next;
    string s = "(";
    while (N != backDummy->prev)
    {
        s += std::to_string(N->data) + ", ";
        N = N->next;
    }
    s = s + std::to_string(N->data);
    s = s + ")";
    return s;
}

bool List::equals(const List &R)
{
    Node *N = this->frontDummy->next;
    Node *M = R.frontDummy->next;
    int length = R.num_elements;
    if (this->num_elements != R.num_elements) return false;
    else
    {
        while (length != 0)
        {
            int temp = N->data;
            int temp2 = M->data;
            N = N->next;
            M = M->next;
            if (temp != temp2) return false;
            length--;
        }
        return true;
    }
}

ostream &operator<<(ostream &stream, List &L)
{
    return stream << L.List::to_string();
}

bool operator==(List &A, const List &B)
{
    return A.List::equals(B);
}

List &List::operator=(const List &L)
{
    if (this != &L)
    {
        List temp = List(L);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}