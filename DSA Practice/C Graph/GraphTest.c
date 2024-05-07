#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char *argv[])
{
    FILE *out = fopen("GraphTest.txt", "w");
    Graph G = newGraph(3);

    addArc(G, 1, 2);
    addArc(G, 2, 1);
    addArc(G, 3, 1);

    addEdge(G, 3, 2);
    addEdge(G, 3, 2);
    addEdge(G, 3, 2);
    addEdge(G, 3, 2);

    printf("Size: %d\n", getSize(G));
    printf("Order: %d\n", getOrder(G));
    printf("Recent: %d\n", getSource(G));
    printf("Dist(1): %d\n", getDist(G, 2));
    printf("Parent(2): %d\n", getParent(G, 2));

    BFS(G, 2);
    printGraph(out, G);


    List nList = newList();

    getPath(nList, G, 3);

    makeNull(G);
    printGraph(out, G);

    freeGraph(&G);

    fclose(out);
    return 0;
}