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
    int *finishRA;
    int *parentRA;
    int *discoverRA;
    List *neighborRA;

} GraphObj;

//CONSTRUCTORS/DECONSTRUCTORS
Graph newGraph(int n)
{
    Graph new = malloc(sizeof(GraphObj));
    new->size = 0;
    new->order = n;
    new->recent = NIL;
    new->finishRA = malloc(sizeof(int)*(n+1));
    new->colorRA = malloc(sizeof(int) * (n+1));
    new->discoverRA = malloc(sizeof(int)*(n+1));
    new->parentRA = malloc(sizeof(int) * (n+1));
    new->neighborRA = malloc(sizeof(List) * (n+1));

    for (int i = 0; i < n + 1; i++)
    {
        new->colorRA[i] = 0;
        new->parentRA[i] = NIL;
        new->finishRA[i] = UNDEF;
        new->discoverRA[i] = UNDEF;
        new->neighborRA[i] = newList();
    }
    return new;
}

void freeGraph(Graph *pG)
{
    for (int i = 0; (i < (*pG)->order + 1); i++)
    {
        freeList(&(*pG)->neighborRA[i]);
        (*pG)->neighborRA[i] = NULL;
    }
    free((*pG)->colorRA);
    free((*pG)->parentRA);
    free((*pG)->finishRA);
    free((*pG)->neighborRA);
    free((*pG)->discoverRA);
    
    (*pG)->colorRA = NULL;
    (*pG)->parentRA = NULL;
    (*pG)->finishRA = NULL;
    (*pG)->neighborRA = NULL;
    (*pG)->discoverRA = NULL;

    free(*pG);
    *pG = NULL;
}

//ACCESS FUNCTIONS

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

//returns parent of index u
int getParent(Graph G, int u)
{
    return G->parentRA[u];
}

int getDiscover(Graph G, int u)
{
    return G->discoverRA[u];
}

int getFinish(Graph G, int u)
{
    return G->finishRA[u];
}

//MANIPULATION PROCEDURES

//adds edge to Graph (connects u and v)
void addEdge(Graph G, int u, int v)
{
    if (orderedInsert(G->neighborRA[u], v) && orderedInsert(G->neighborRA[v], u))
    {
        G->size++;
    }
}

void addArc(Graph G, int u, int v)
{
    if (orderedInsert(G->neighborRA[u], v))
    {

        G->size++;
    }
}

void DFS(Graph G, List S)
{
    int time;
    for (int i=1; i<=getOrder(G); i++){
        G->colorRA[i] = 0;
		G->parentRA[i] = NIL;
    }
    time = 0; 
    G->recent = NIL;
    for (moveFront(S); index(S)>=0; moveNext(S)){
        if (G->colorRA[get(S)] == 0) {
            time = Visit(G, get(S), time, S);
        }
    }
    int reduction = length(S)/2;
    for(int i=0; i<reduction; i++) deleteBack(S);
}

int Visit(Graph G, int x, int time, List L)
{
    G->colorRA[x] = 1;
    int rT = time + 1;
    G->discoverRA[x] = rT;
    if (!isEmpty(G->neighborRA[x]))
    {
        for (moveFront(G->neighborRA[x]); index(G->neighborRA[x]) >= 0; moveNext(G->neighborRA[x]))
        {
            if (G->colorRA[get(G->neighborRA[x])] == 0)
            {
                G->parentRA[get(G->neighborRA[x])] = x;
                rT = Visit(G, get(G->neighborRA[x]), rT, L);
            }
        }
    }
    rT++;
    prepend(L, x);
    G->colorRA[x] = 2;
    G->finishRA[x] = rT;
    return rT;
}


//OTHER OPERATIONS
Graph transpose(Graph G)
{
    Graph transpose = newGraph(G->order);
    for (int i = 1; i < G->order + 1; i++)
    {
        if (!isEmpty(G->neighborRA[i]))
        {
            for (moveFront(G->neighborRA[i]); index(G->neighborRA[i]) >= 0; moveNext(G->neighborRA[i])) addArc(transpose, get(G->neighborRA[i]), i);
        }
    }
    return transpose;
}

Graph copyGraph(Graph G)
{
    Graph transpose = newGraph(G->order);
    for (int i = 1; i < G->order + 1; i++)
    {
        if (!isEmpty(G->neighborRA[i]))
        {
            for (moveFront(G->neighborRA[i]); index(G->neighborRA[i]) >= 0; moveNext(G->neighborRA[i])) addArc(transpose, i, get(G->neighborRA[i]));
        }
    }
    return transpose;
}

void printGraph(FILE *out, Graph G)
{
    for (int i = 1; i < G->order + 1; i++)
    {
        fprintf(out, "%d: ", i);
        printList(out, G->neighborRA[i]);
        fprintf(out, "\n");
    }
}