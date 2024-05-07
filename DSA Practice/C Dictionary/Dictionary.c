/*********************************************************************************
* Steven Tabilisma, stabilis
* 2021 Spring CSE101 PA7
* Dictionary.c
*********************************************************************************/
#include "Dictionary.h"
#include <stdio.h>
#include <string.h>

#define BLACK 0
#define RED 1

//-----------------NODE AND DICT DATA STRUCTURES------------------//

typedef struct NodeObj
{
    int color;
    KEY_TYPE key;
    VAL_TYPE data;
    struct NodeObj *left;
    struct NodeObj *right;
    struct NodeObj *parent;
} NodeObj;

typedef NodeObj *Node;

typedef struct DictionaryObj
{
    int size;
    int unique;
    Node NIL;
    Node root;
    Node cursor;
} DictionaryObj;

//HELPER FUNCTION DECLARATION//
void transplant(Dictionary D, Node U, Node V);

// Constructors-Destructors ---------------------------------------------------

//creates new node
Node newNode(KEY_TYPE key, VAL_TYPE data)
{
    Node N = malloc(sizeof(NodeObj));
    N->key = key;
    N->data = data;
    N->left = NULL;
    N->right = NULL;
    N->color = BLACK;
    N->parent = NULL;
    return N;
}

//creates new Dictionary
Dictionary newDictionary(int unique)
{
    Dictionary Dict = malloc(sizeof(DictionaryObj));
    int nil = -1;
    int *nilVal = &nil;
    Dict->unique = unique;
    Dict->NIL = newNode(KEY_UNDEF, nilVal);
    Dict->NIL->left = Dict->NIL;
    Dict->NIL->right = Dict->NIL;
    Dict->root = Dict->NIL;
    Dict->cursor = Dict->NIL;
    Dict->size = 0;
    return Dict;
}

void leftRotate(Dictionary D, Node N);
void rightRotate(Dictionary D, Node N);
void insertFixUp(Dictionary D, Node N);
void deleteFixUp(Dictionary D, Node N);
void postOrder(FILE *out, Dictionary D, Node N);
void preOrder(FILE *out, Dictionary D, Node N);
void inOrder(FILE *out, Dictionary D, Node N);

//frees all memory associated with Node
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

//frees all memory associated with Dictionary
void freeDictionary(Dictionary *pD)
{
    if (pD != NULL && *pD != NULL)
    {
        makeEmpty(*pD);
        freeNode(&(*pD)->NIL);
        free(*pD);
        *pD = NULL;
    }
}

// Access functions -----------------------------------------------------------

//returns the size of the Dictionary
int size(Dictionary D)
{
    if (D == NULL)
    {
        printf("size() on NULL reference\n");
        exit(EXIT_FAILURE);
    }

    return D->size;
}

//returns 0 if no unique inputs required
//returns 1 if unique inputs required
int getUnique(Dictionary D)
{
    if (D == NULL)
    {
        printf("getUnique() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    return (D->unique >= 1);
}

//looks up the value of the associated with key k input
VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
    if (D == NULL)
    {
        printf("lookUp() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    //main lookup function//
    Node N = D->root;
    while (N != D->NIL)
    {
        if (KEY_CMP(k, N->key) == 0)
            return N->data;
        else if (KEY_CMP(k, N->key) < 0)
            N = N->left;
        else if (KEY_CMP(k, N->key) > 0)
            N = N->right;
    }
    return VAL_UNDEF;
}

// Manipulation procedures ----------------------------------------------------

//inserts Node with Key K and Value v
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
    if (D == NULL)
    {
        printf("insert() on NULL reference\n");
        exit(EXIT_FAILURE);
    }

    if (getUnique(D))
    {
        if (lookup(D, k) != VAL_UNDEF)
        {
            printf("insert() on existing key: %s\n", k);
            exit(EXIT_FAILURE);
        }
    }

    Node y = D->NIL;
    Node x = D->root;
    Node z = newNode(k, v);

    while (x != D->NIL)
    {
        y = x;
        if (KEY_CMP(k, x->key) < 0)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == D->NIL)
    {
        D->root = z;
        z->parent = D->NIL;
    }
    else if (KEY_CMP(k, y->key) < 0)
        y->left = z;
    else
        y->right = z;

    z->left = D->NIL;
    z->right = D->NIL;
    z->color = RED;
    insertFixUp(D, z);

    D->size += 1;
}

//fixes up Dictionary according to RBT
void insertFixUp(Dictionary D, Node z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node Y = z->parent->parent->right;
            if (Y->color == RED)
            {
                z->parent->color = BLACK;
                Y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(D, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(D, z->parent->parent);
            }
        }

        else
        {
            Node Y = z->parent->parent->left;
            if (Y->color == RED)
            {
                z->parent->color = BLACK;
                Y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(D, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(D, z->parent->parent);
            }
        }
    }
    D->root->color = BLACK;
}

void rightRotate(Dictionary D, Node X)
{
    Node Y = X->left;
    X->left = Y->right;
    if (Y->right != D->NIL) Y->right->parent = X;
    Y->parent = X->parent;
    
    if (X->parent == D->NIL) D->root = Y;
    else if (X == X->parent->right) X->parent->right = Y;
    else X->parent->left = Y;


    Y->right = X;
    X->parent = Y;
}

void leftRotate(Dictionary D, Node X)
{
    Node Y = X->right;
    X->right = Y->left;
    if (Y->left != D->NIL) Y->left->parent = X;
    Y->parent = X->parent;

    if (X->parent == D->NIL) D->root = Y;
    else if (X == X->parent->left) X->parent->left = Y;
    else X->parent->right = Y;

    Y->left = X;
    X->parent = Y;
}

//helper function for delete that transplants tree
void transplant(Dictionary D, Node U, Node V)
{
    if (U->parent == D->NIL) D->root = V;
    else if (U == U->parent->left) U->parent->left = V;
    else U->parent->right = V;

    V->parent = U->parent;
}

//deletes associated Node with key k
//pre: lookup != VAL_UNDEF
void delete (Dictionary D, KEY_TYPE k)
{

    if (D == NULL)
    {
        printf("delete() on NULL reference\n");
        exit(EXIT_FAILURE);
    }

    if (lookup(D, k) == VAL_UNDEF)
    {
        printf("lookup() unable to find %s\n", k);
        exit(EXIT_FAILURE);
    }

    Node N = D->root;
    while (KEY_CMP(k, N->key) != 0)
    {
        if (KEY_CMP(k, N->key) < 0) N = N->left;
        else if (KEY_CMP(k, N->key) > 0) N = N->right;
    }

    if (N == D->cursor) D->cursor = D->NIL;

    Node Y = N;
    Node X;
    int y_original_color = Y->color;
    if (N->left == D->NIL)
    {
        X = N->right;
        transplant(D, N, N->right);
    }
    else if (N->right == D->NIL)
    {
        X = N->left;
        transplant(D, N, N->left);
    }
    else
    {
        Y = N->right;
        while (Y->left != D->NIL) Y = Y->left;
        y_original_color = Y->color;
        X = Y->right;
        if (Y->parent == N) X->parent = Y;
        else
        {
            transplant(D, Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        transplant(D, N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }

    if (y_original_color == BLACK) deleteFixUp(D, X);
    freeNode(&N);
    D->size--;
}

void deleteFixUp(Dictionary D, Node X)
{
    while (X != D->root && X->color == BLACK)
    {
        if (X == X->parent->left)
        {
            Node W = X->parent->right;
            if (W->color == RED)
            {
                W->color = BLACK;
                X->parent->color = RED;
                leftRotate(D, X->parent);
                W = X->parent->right;
            }
            if (W->left->color == BLACK && W->right->color == BLACK)
            {
                W->color = BLACK;
                X = X->parent;
            }
            else
            {
                if (W->right->color == BLACK)
                {
                    W->left->color = BLACK;
                    W->color = RED;
                    rightRotate(D, W);
                    W = X->parent->right;
                }
                W->color = X->parent->color;
                X->parent->color = BLACK;
                W->right->color = BLACK;
                leftRotate(D, X->parent);
                X = D->root;
            }
        }
        else
        {
            Node W = X->parent->left;
            if (W->color == RED)
            {
                W->color = BLACK;
                X->parent->color = RED;
                rightRotate(D, X->parent);
                W = X->parent->left;
            }
            if (W->right->color == BLACK && W->left->color == BLACK)
            {
                W->color = RED;
                X = X->parent;
            }
            else
            {
                if (W->left->color == BLACK)
                {
                    W->right->color = BLACK;
                    W->color = RED;
                    leftRotate(D, W);
                    W = X->parent->left;
                }
                W->color = X->parent->color;
                X->parent->color = BLACK;
                W->left->color = BLACK;
                rightRotate(D, X->parent);
                X = D->root;
            }
        }
    }
    X->color = BLACK;
}

//deletes all the Nodes in associated Dictionary
void makeEmpty(Dictionary D)
{
    beginForward(D);
    while (size(D) > 0)
    {
        delete (D, D->cursor->key);
        beginForward(D);
    }
    D->cursor = D->NIL;
}

//starts forward iteration and moves D->cursor to front
VAL_TYPE beginForward(Dictionary D)
{

    if (D == NULL)
    {
        printf("beginForward() on NULLreference\n");
        exit(EXIT_FAILURE);
    }

    if (D->size == 0) return VAL_UNDEF;
    D->cursor = D->root;
    while (D->cursor->left != D->NIL) D->cursor = D->cursor->left;
    return D->cursor->data;
}

//starts reverse iteration and moves D->cursor to back
VAL_TYPE beginReverse(Dictionary D)
{

    if (D == NULL)
    {
        printf("beginReverse() on NULL reference\n");
        exit(EXIT_FAILURE);
    }

    if (D->size == 0) return VAL_UNDEF;

    Node N = D->root;
    while (N->right != D->NIL) N = N->right;
    D->cursor = N;

    return N->data;
}

//returns key value if iteration started
//returns KEY_UNDEF if not started
KEY_TYPE currentKey(Dictionary D)
{
    if (D->cursor == D->NIL) return KEY_UNDEF;
    return D->cursor->key;
}

//returns val if iteration started
//returns VAL_UNDEF if not started
VAL_TYPE currentVal(Dictionary D)
{
    if (D->cursor == D->NIL) return VAL_UNDEF;
    return D->cursor->data;
}

//moves D->cursor to successor
VAL_TYPE next(Dictionary D)
{

    if (D->cursor == D->NIL) return VAL_UNDEF;
    if (D->cursor->right != D->NIL)
    {
        D->cursor = D->cursor->right;
        while (D->cursor->left != D->NIL) D->cursor = D->cursor->left;
        return D->cursor->data;
    }

    Node Y = D->cursor->parent;
    while (Y != D->NIL && D->cursor == Y->right)
    {
        D->cursor = Y;
        Y = Y->parent;
    }
    D->cursor = Y;
    if (D->cursor == D->NIL) return VAL_UNDEF;
    return Y->data;
}

//moves D->cursor to predecessor
VAL_TYPE prev(Dictionary D)
{
    if (D->cursor == D->NIL) return VAL_UNDEF;
    if (D->cursor->left != D->NIL)
    {
        D->cursor = D->cursor->left;
        while (D->cursor->right != D->NIL) D->cursor = D->cursor->right;
        return D->cursor->data;
    }
    Node Y = D->cursor->parent;
    while (Y != D->NIL && D->cursor == Y->left)
    {
        D->cursor = Y;
        Y = Y->parent;
    }
    D->cursor = Y;
    if (D->cursor == D->NIL) return VAL_UNDEF;
    return Y->data;
}

// Other operations -----------------------------------------------------------

//print Dictionary inOrder
void printDictionary(FILE *out, Dictionary D, const char *ord)
{
    if (KEY_CMP(ord, "in") == 0) inOrder(out, D, D->root);
    if (KEY_CMP(ord, "pre") == 0) preOrder(out, D, D->root);
    if (KEY_CMP(ord, "post") == 0) postOrder(out, D, D->root);
}

void inOrder(FILE *out, Dictionary D, Node N)
{
    if (N != D->NIL)
    {
        inOrder(out, D, N->left);
        fprintf(out, KEY_FORMAT "\n", N->key);
        inOrder(out, D, N->right);
    }
}

void postOrder(FILE *out, Dictionary D, Node N)
{
    if (N != D->NIL)
    {
        postOrder(out, D, N->left);
        postOrder(out, D, N->right);
        fprintf(out, KEY_FORMAT "\n", N->key);
    }
}

void preOrder(FILE *out, Dictionary D, Node N)
{
    if (N != D->NIL)
    {
        fprintf(out, KEY_FORMAT "\n", N->key);
        preOrder(out, D, N->left);
        preOrder(out, D, N->right);
    }
}
