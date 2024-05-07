//-----------------------------------------------------------------------------
//List.c
//Implements a doubly linked list ADT.
// Written by Steven Tabilisma for CSE101 Spring 2021  | stabilis@ucsc.edu
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Data Structures

typedef struct Node
{
    struct Node *prevItem;
    int data;
    struct Node *nextItem;
} Node;

typedef Node *Item;

typedef struct ListObj
{
    Item prev;
    Item current;
    Item next;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

List newList(void)
{
    List newL;
    newL = malloc(sizeof(ListObj));
    newL->prev = NULL;
    newL->current = NULL;
    newL->next = NULL;
    newL->length = 0;
    newL->index = -1;
    return newL;
}

Item newItem(int data)
{
    Item item;
    item = malloc(sizeof(Node));
    item->prevItem = NULL;
    item->data = data;
    item->nextItem = NULL;
    return item;
}

// Memory Clearing
void freeList(List *pQ)
{
    clear(*pQ);
    free(*pQ);
    *pQ = NULL;
}

void freeItem(Item *pI)
{
    if ((pI != NULL) && (*pI != NULL))
    {
        free(*pI);
        *pI = NULL;
    }
}

// Access functions -----------------------------------------------------------

int length(List Q) // Returns the Length of the list.
{
    if (Q == NULL)
    {
        printf("Length Error.\n");
        exit(EXIT_FAILURE);
    }
    return Q->length;
}

int index(List Q) // Returns index of cursor element if defined, -1 otherwise.
{
    if (Q == NULL)
    {
        printf("Index Error.\n");
        exit(EXIT_FAILURE);
    }
    return Q->index;
}

int front(List Q)
{
    if (Q == NULL)
    {
        printf("Front Error.\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(Q))
    {
        printf("List Error: calling getFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return Q->next->data;
}

int back(List Q)
{
    if (Q == NULL)
    {
        printf("Back Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(Q))
    {
        printf("Back Error. Empty case.\n");
        exit(EXIT_FAILURE);
    }
    return Q->prev->data;
}

int get(List Q)
{
    if (Q == NULL)
    {
        printf("Get Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(Q))
    {
        printf("Get Error. Empty.\n");
        exit(EXIT_FAILURE);
    }
    if (Q->index == -1)
    {
        printf("List Error: Index and cursor undefined.\n");
        exit(EXIT_FAILURE);
    }
    return Q->current->data;
}

int equals(List A, List B)
{
    int check = 0;
    if (A == NULL || B == NULL)
    {
        printf("Equals Error.\n");
        exit(EXIT_FAILURE);
    }

    Node *pA = A->next;
    Node *pB = B->next;
    if (A->length != B->length)
    {
        return check;
    }
    else
    {
        while (pA && pB)
        {
            if (pA->data != pB->data)
            {
                return 0;
            }
            pA = pA->nextItem;
            pB = pB->nextItem;
        }
        check = 1;
        return check;
    }
}

// Unused Access Functions

int isEmpty(List Q)
{
    if (Q->length <= 0)
    {
        return 1;
    }
    if (Q == NULL)
    {
        printf("Empty Error. NULL List.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

// Manipulation procedures ----------------------------------------------------
void clear(List Q)
{
    if (Q == NULL)
    {
        printf("Clear Error. NULL list\n");
        exit(EXIT_FAILURE);
    }
    while (Q->length > 1)
    {
        deleteFront(Q);
    }

    Item p = Q->next;

    Q->next = NULL;
    Q->prev = NULL;
    Q->current = NULL;
    Q->length = 0;
    Q->index = -1;

    freeItem(&p);
}
void set(List Q, int x)
{
    if (Q == NULL)
    {
        printf("Set Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(Q))
    {
        printf("Set Error. Empty list.\n");
        exit(EXIT_FAILURE);
    }
    Q->current->data = x;
}
void moveFront(List Q)
{
    if (isEmpty(Q))
    {
        printf("moveFront Error. Empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (Q == NULL)
    {
        printf("moveFront Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }
    if (Q != NULL)
    {
        Q->current = Q->next;
        Q->index = 0;
    }
}
void moveBack(List Q)
{
    if (isEmpty(Q))
    {
        printf("moveFront Error. Empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (Q == NULL)
    {
        printf("moveFront Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }
    if (Q != NULL)
    {
        Q->current = Q->prev;
        Q->index = Q->length - 1;
    }
}
void movePrev(List Q)
{
    if (Q == NULL)
    {
        printf("movePrev Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }
    if (Q->current != NULL)
    {
        if (Q->index > 0)
        {
            Q->current = Q->current->prevItem;
            Q->index--;
        }
        else
        {
            Q->current = NULL;
            Q->index = -1;
        }
    }
}
void moveNext(List Q)
{
    if (Q == NULL)
    {
        printf("moveNext Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    if (Q->current != NULL)
    {
        if (Q->index < Q->length - 1)
        {
            Q->current = Q->current->nextItem;
            Q->index++;
        }
        else
        {
            Q->current = NULL;
            Q->index = -1;
        }
    }
}
void prepend(List Q, int x)
{
    if (Q == NULL)
    {
        printf("Prepend Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    Item N = newItem(x);

    if (!isEmpty(Q))
    {
        Q->next->prevItem = N;
        N->nextItem = Q->next;
        Q->next = N;
        Q->length++;
    }
    else if (isEmpty(Q))
    {
        Q->next = Q->prev = N;
        Q->length++;
    }

    if (Q->index != -1)
    {
        Q->index++;
    }
}
void append(List Q, int x)
{
    if (Q == NULL)
    {
        printf("Append Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    Item N = newItem(x);
    if (!isEmpty(Q))
    {
        Q->prev->nextItem = N;
        N->prevItem = Q->prev;
        Q->prev = N;
        Q->length++;
    }
    else if (isEmpty(Q))
    {
        Q->next = Q->prev = N;
        Q->length++;
    }
}
void insertBefore(List Q, int x)
{
    Item N = newItem(x);
    if (Q == NULL)
    {
        printf("insertBefore Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }
    else if (Q->length <= 0)
    {
        printf("insertBefore Error. Length case.\n");
        exit(EXIT_FAILURE);
    }
    else if (index(Q) == -1)
    {
        printf("insertBefore Error. Index case. \n");
        exit(EXIT_FAILURE);
    }

    else if (isEmpty(Q))
    {
        printf("insertBefore Error. Empty list case.\n");
        exit(EXIT_FAILURE);
    }

    N->nextItem = Q->current;
    if (Q->current->prevItem != NULL)
    {
        N->prevItem = Q->current->prevItem;
        Q->current->prevItem->nextItem = N;
    }
    Q->current->prevItem = N;
    if (N->prevItem == NULL)
    {
        Q->next = N;
    }
    Q->index++;
    Q->length++;
}
void insertAfter(List Q, int x)
{
    if (Q == NULL)
    {
        printf("insertAfter Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    if (index(Q) == -1)
    {
        printf("insertAfter Error. index case.\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(Q))
    {
        printf("insertAfter Error. Empty list case.\n");
        exit(EXIT_FAILURE);
    }

    if (Q->current == Q->prev)
    {
        append(Q, x);
    }

    else
    {
        Item N = newItem(x);
        N->nextItem = Q->current->nextItem;
        N->prevItem = Q->current;
        Q->current->nextItem = N;
        N->nextItem->prevItem = N;

        Q->length++;
    }
}
void deleteFront(List Q)
{
    if (Q == NULL)
    {
        printf("deleteFront Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(Q))
    {
        printf("deleteFront Error. Empty list case.\n");
        exit(EXIT_FAILURE);
    }

    if (Q->current == Q->next)
    {
        Q->current = NULL;
        Q->index = -1;
    }

    if (length(Q) == 1)
    {
        Q->next = Q->prev = NULL;
        Q->length--;
    }
    else if (length(Q) > 1)
    {
        Item p = Q->next;
        Q->next = Q->next->nextItem;
        Q->next->prevItem = NULL;
        Q->length--;
        if (Q->index != -1)
        {
            Q->index--;
        }
        freeItem(&p);
    }
}
void deleteBack(List Q)
{
    if (Q == NULL)
    {
        printf("deleteBack Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(Q))
    {
        printf("deleteBack Error. Empty list case.\n");
        exit(EXIT_FAILURE);
    }

    if (Q->current == Q->prev)
    {
        Q->current = NULL;
        Q->index = -1;
    }

    if (length(Q) == 1)
    {
        freeItem(&(Q->next));
        Q->prev = NULL;
        Q->next = NULL;
        Q->length -= 1;
        return;
    }
    else if (length(Q) > 1)
    {
        Item p = Q->prev;
        Q->prev = Q->prev->prevItem;
        Q->prev->nextItem = NULL;
        Q->length--;
        freeItem(&p);
    }
}
void delete (List Q)
{
    if (Q == NULL)
    {
        printf("delete Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    if (Q->index == -1)
    {
        printf("delete Error. Index case.\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(Q))
    {
        printf("delete Error. Empty list case.\n");
        exit(EXIT_FAILURE);
    }

    if (Q->current == Q->prev)
    {
        deleteBack(Q);
    }

    else if (Q->current == Q->next)
    {
        deleteFront(Q);
    }

    else
    {
        Item p = Q->current;
        Q->current->prevItem->nextItem = Q->current->nextItem;
        Q->current->nextItem->prevItem = Q->current->prevItem;
        Q->current = NULL;
        Q->length -= 1;
        Q->index = -1;
        freeItem(&p);
    }
}
void deleteNode(List Q)
{
    Item t = NULL;
    t = Q->current;
    Q->current->prevItem->nextItem = Q->current->nextItem;
    Q->current->nextItem->prevItem = Q->current->prevItem;
    Q->current = NULL;
    Q->index = -1;
    Q->length -= 1;
    freeItem(&t);
}
// Other Functions ------------------------------------------------------------
void printList(FILE *out, List Q)
{
    if (Q == NULL)
    {
        printf("printList Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(Q))
    {
        printf("printList Error. Empty list case.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        Item temp = Q->next;
        while (temp != NULL)
        {
            fprintf(out, "%d ", temp->data);
            temp = temp->nextItem;
        }
    }
}
List copyList(List Q)
{
    if (Q == NULL)
    {
        printf("copyList Error. NULL case.\n");
        exit(EXIT_FAILURE);
    }

    List listCopy = newList();
    Node *p = Q->next;
    while (p)
    {
        append(listCopy, p->data);
        p = p->nextItem;
    }
    return listCopy;
}
