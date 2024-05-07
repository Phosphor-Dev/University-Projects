#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"
#include "string.h"

void printPrompt(FILE *out, Graph G, int a, int b);

int main(int argc, char *argv[])
{
    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    int size, a, b;
    char *strings, *end;
    strings = malloc(sizeof(char) * 75);
    fgets(strings, 75, in);
    size = atol(strings);
    Graph G = newGraph(size);
    fgets(strings, 75, in);
    a = strtol(strings, &end, 10);
    b = strtol(end, &end, 10);
    while (a != 0 && b != 0)
    {
        addArc(G, a, b);
        fgets(strings, 75, in);
        a = strtol(strings, &end, 10);
        b = strtol(end, &end, 10);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    List S = newList();
    for(int i = 1; i<=getOrder(G); i++) append(S, i);
    DFS(G, S);
    Graph transposed = transpose(G);
    DFS(transposed, S);
    int items = 0;
    for(int i = 1; i < getOrder(transposed) + 1; i++)
    {
        if(getParent(transposed, i) == NIL)
        {
            items++;
        }
        
    }
    output(S);
    fprintf(out, "G contains %d strongly connected components:\n", items);
    int temp, i = 1;
    List listPrint = newList();
    for(moveBack(S); index(S) >= 0; movePrev(S))
    {   
        temp = get(S);
        prepend(listPrint, temp);
        if(getParent(transposed, temp) == NIL)
        {
            fprintf(out, "Component %d: ", i);
            printList(out, listPrint);
            fprintf(out, "\n");
            clear(listPrint);
            i++;
        }
        
    }
    freeList(&S);
    freeGraph(&G);
    free(strings);
    freeList(&listPrint);
    freeGraph(&transposed);
    fclose(in);
    fclose(out);
    return 0;
}
