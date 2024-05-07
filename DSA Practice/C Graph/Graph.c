#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

//EXPORTED TYPES

typedef struct GraphObj
{
    int size;
    int order;
    int recent;
    int *colorRA;
    int *parentRA;
    int *distanceRA;
    List *neighborRA;

} GraphObj;

//-------------------CONSTRUCTORS/DECONSTRUCTORS------------------//
Graph newGraph(int n)
{
    Graph new = malloc(sizeof(GraphObj));
    new->size = 0;
    new->order = n;
    new->recent = NIL;
    new->colorRA = malloc(sizeof(int) * (n+1));
    new->parentRA = malloc(sizeof(int) * (n+1));
    new->distanceRA = malloc(sizeof(int) * (n+1));
    new->neighborRA = malloc(sizeof(List) * (n+1));

    for (int i = 0; i < n + 1; i++)
    {
        new->neighborRA[i] = newList();
        new->colorRA[i] = 0;
        new->parentRA[i] = NIL;
        new->distanceRA[i] = INF;
    }
    return new;
}

//frees all allocated memory for Graph
void freeGraph(Graph *pG)
{
    for (int i = 0; (i < (*pG)->order + 1); i++)
    {
        freeList(&(*pG)->neighborRA[i]);
        (*pG)->neighborRA[i] = NULL;
    }
    free((*pG)->colorRA);
    free((*pG)->parentRA);
    free((*pG)->neighborRA);
    free((*pG)->distanceRA);
    
    (*pG)->colorRA = NULL;
    (*pG)->parentRA = NULL;
    (*pG)->neighborRA = NULL;
    (*pG)->distanceRA = NULL;

    free(*pG);
    *pG = NULL;
}

//-------------------------ACCESS FUNCTIONS------------------------//

//returns order
int getOrder(Graph G)
{
    return G->order;
}

//returns size
int getSize(Graph G)
{
    return G->size;
}

//returns source
int getSource(Graph G)
{
    return G->recent;
}

//returns parent of index u
int getParent(Graph G, int u)
{
    return G->parentRA[u];
}

//returns distance of index u
int getDist(Graph G, int u)
{
    return G->distanceRA[u];
}

//appends path of index u to L //NOTE GO BACK TO LATER//
void getPath(List L, Graph G, int u)
{
    if (u == G->recent)
    {
        append(L, G->recent);
    }
    else if (G->parentRA[u] == NIL)
    {
        append(L, NIL);
    }
    else
    {
        getPath(L, G, G->parentRA[u]);
        append(L, u);
    }
}

//---------------------MANIPULATION PROCEDURES--------------------//

//resets Graph to null state
void makeNull(Graph G)
{
    for (int i = 0; i < G->order + 1; i++)
    {
        clear(G->neighborRA[i]);
        G->colorRA[i] = 0;
        G->parentRA[i] = NIL;
        G->distanceRA[i] = INF;
    }

    G->size = 0;
    G->recent = NIL;
}

//adds edge to Graph (connects u and v)
void addEdge(Graph G, int u, int v)
{
    if (orderedInsert(G->neighborRA[u], v) && orderedInsert(G->neighborRA[v], u))
    {
        G->size++;
    }
}

//adds arc to Graph(only u to v, not v to u)
void addArc(Graph G, int u, int v)
{
    if (orderedInsert(G->neighborRA[u], v))
    {

        G->size++;
    }
}

//runs the BFS algorithm on the graph
void BFS(Graph G, int s)
{
    int x;
    G->recent = s;
    for (int i = 1; i < G->order + 1; i++)
    {
        if (i != s)
        {
            G->colorRA[i] = 0;
            G->parentRA[i] = NIL;
            G->distanceRA[i] = INF;
        }
    }
    G->colorRA[s] = 0;
    G->parentRA[s] = NIL;
    G->distanceRA[s] = 0;
    List q = newList();
    append(q, s);
    moveFront(q);
    while (!isEmpty(q))
    {
        moveFront(q);
        x = get(q);
        deleteFront(q);
        if (!isEmpty(G->neighborRA[x]))
        {
            moveFront(G->neighborRA[x]);
            while (index(G->neighborRA[x]) >= 0)
            {
                if (G->colorRA[get(G->neighborRA[x])] == 0)
                {
                    G->colorRA[get(G->neighborRA[x])] = 1;
                    G->distanceRA[get(G->neighborRA[x])] = G->distanceRA[x] + 1;
                    G->parentRA[get(G->neighborRA[x])] = x;
                    append(q, get(G->neighborRA[x]));
                }
                moveNext(G->neighborRA[x]);
            }
        }
        G->colorRA[x] = 2;
    }
    freeList(&q);
	q = NULL;
}

//--------------------------OTHER OPERATIONS-----------------------//

//prints graph onto output file
void printGraph(FILE *out, Graph G)
{
    if (G == NULL)
    {
        printf("GraphError: Calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < G->order + 1; i++)
    {
        fprintf(out, "%d: ", i);
        printList(out, G->neighborRA[i]);
        fprintf(out, "\n");
    }
}