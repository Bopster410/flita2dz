#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        exit(1);
    }
    node_t *graph = graphFromFile(argv[1]);

    printGraph(graph);

    graphToDot(graph, "graph.dot", DIRECTED);

    system("dot -Tpng graph.dot -o output.png");
    return 0;
}