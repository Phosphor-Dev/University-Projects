#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char *argv[])
{
    FILE *out = fopen("GraphTest.txt", "w");
    int n = 10;
    Graph G = newGraph(n);
    printf("Size %d\n", getSize(G));
    printf("Order %d\n", getOrder(G));
    printf("Parent(1) %d\n", getParent(G, 1));
    printf("Finish(1) %d\n", getFinish(G, 1));
    printf("Discover(1) %d\n", getDiscover(G, 1));
    
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 3);
    
    addArc(G, 1, 5);
    addArc(G, 2, 6);

    printf("Size %d\n", getSize(G));
    printf("Order %d\n", getOrder(G));
    printf("Parent(1) %d\n", getParent(G, 1));
    printf("Finish(1) %d\n", getFinish(G, 1));
    printf("Discover(1) %d\n", getDiscover(G, 1));

    Graph copyH = copyGraph(G);
    Graph transposeH = transpose(G);

    printGraphConsole(G);
    fclose(out);
    return (0);
}