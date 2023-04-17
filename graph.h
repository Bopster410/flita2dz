#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum graphType {
    DIRECTED,
    UNDIRECTED
} graphType;

typedef struct node node_t;

struct node
{
    node_t *nextNodeInGraph;
    list *connectedNodes;
    char *name;
};


node_t *addNode(node_t *currentNode, char *nodeId);

node_t *addConnection(node_t *currentNode, char *nodeId, char *nodeToConnect);

bool isInGraph(node_t *currentNode, char *nodeId);

void printGraph(node_t *firstNode);

node_t *findNode(node_t *currentNode, char *nodeId);

void graphToDot(node_t *graph, const char *fileName, graphType type);

node_t *graphFromFile(char *fileName);

void freeGraph(node_t *graph);

#endif