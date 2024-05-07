#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[])
{
    FILE *in, *out;
    int u, v, size, front, back;

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    fscanf(in, "%d", &size);
    Graph G = newGraph(size);

    while (fscanf(in, "%d %d", &u, &v) != EOF)
    {
        if (u == 0 && v == 0)
        {
            break;
        }
        addEdge(G, u, v);
    }
    printf("\n");
    printGraph(out, G);

    List L = newList();
    while (fscanf(in, "%d %d", &front, &back))
    {
        if (front == 0 && back == 0)
        {
            break;
        }
        BFS(G, front);
        getPath(L, G, back);
        if (getDist(G, back) == -1)
        {
            fprintf(out, "The distance from %d to %d is infinity\n", front, back);
            fprintf(out, "No %d-%d path exists\n", front, back);
        }
        else
        {
            fprintf(out, "The distance from %d to %d is %d\n", front, back, getDist(G, back));
            fprintf(out, "A shortest %d-%d path is: ", front, back);
            printList(out, L);
            fprintf(out, "\n");
        }
        clear(L);
    }

    freeGraph(&G);
    freeList(&L);
    fclose(in);
    fclose(out);
    return 0;
}