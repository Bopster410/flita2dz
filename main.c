#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        exit(1);
    }
    node_t *graph = graphFromFile(argv[1]);

    printGraph(graph);

    const char *dotFileName = "graph.dot";
    graphToDot(graph, dotFileName, DIRECTED);

    freeGraph(graph);

    char *command = malloc(sizeof(char) * 64);
    sprintf(command, "dot -Tpng %s -o output.png", dotFileName);

    system(command);

    free(command);

    return 0;
}