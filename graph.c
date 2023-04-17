#include "graph.h"

node_t *addNode(node_t *currentNode, char *nodeId) {
    bool isFirst = currentNode == NULL, isNodeInGraph;

    if (!isFirst) {
        isNodeInGraph = isInGraph(currentNode, nodeId);
    }

    if (isFirst || !isNodeInGraph) {
        node_t *temp = malloc(sizeof(node_t));
        temp->name = nodeId;
        temp->connectedNodes = NULL;
        temp->nextNodeInGraph = currentNode;
        return temp;
    }

    return currentNode;
}

node_t *addConnection(node_t *currentNode, char *nodeId, char *nodeToConnect) {
    if (currentNode == NULL) {
        return NULL;
    }

    node_t *temp = malloc(sizeof(node_t));
    temp->name = currentNode->name;
    if (strcmp(currentNode->name, nodeId) == 0) {
        temp->connectedNodes = addListElement(currentNode->connectedNodes, nodeToConnect, STR);
        temp->nextNodeInGraph = currentNode->nextNodeInGraph;
        return temp;
    } else {
        temp->connectedNodes = currentNode->connectedNodes;
        temp->nextNodeInGraph = addConnection(currentNode->nextNodeInGraph, nodeId, nodeToConnect);
        if (temp->nextNodeInGraph == NULL) {
            return currentNode;
        } else {
            return temp;
        }
    }
}

void printGraph(node_t *currentNode) {
    printf("%s: ", currentNode->name);
    printList(currentNode->connectedNodes);
    putchar('\n');
    if (currentNode->nextNodeInGraph != NULL) {
        printGraph(currentNode->nextNodeInGraph);
    }
}

bool isInGraph(node_t *currentNode, char *nodeId) {
    if (currentNode == NULL) {
        return false;
    } else if (strcmp(currentNode->name, nodeId) == 0) {
        return true;
    } else {
        return isInGraph(currentNode->nextNodeInGraph, nodeId);
    }
}

node_t *findNode(node_t *currentNode, char *nodeId) {
    if (currentNode == NULL) {
        return NULL;
    } else if (strcmp(currentNode->name, nodeId) == 0) {
        return currentNode;
    } else {
        findNode(currentNode->nextNodeInGraph, nodeId);
    }
}

void graphToDot(node_t *graph, const char *fileName, graphType type) {
    FILE *graphSrc = fopen(fileName, "w");
    fputs("graph gr {\n", graphSrc);
    if (type == DIRECTED) {
        fputs("\tedge [dir=forward]\n", graphSrc);
    }
    node_t *temp = graph;
    while (temp != NULL) {
        fprintf(graphSrc,"\t%s", temp->name);
        list *currentConnection = temp->connectedNodes;
        if (currentConnection != NULL) {
            fputs(" -- ", graphSrc);
        }
        while (currentConnection != NULL) {
            fprintf(graphSrc,"%s", (char*)currentConnection->value);
            if (currentConnection->nextElement != NULL) {
                fputs(", ", graphSrc);
            }
            currentConnection = currentConnection->nextElement;
        }
        fputc('\n', graphSrc);
        temp = temp->nextNodeInGraph;
    }
    putc('}', graphSrc);
    fclose(graphSrc);
}

node_t *graphFromFile(char *fileName) {
    // Opening source file
    FILE *input = fopen(fileName, "r");

    // File len
    fseek(input, 0, SEEK_END);
    int len = ftell(input);
    fseek(input, 0, SEEK_SET);
    char *inputBuf = malloc(sizeof(char) * len + 1);

    // Reading from file
    fread(inputBuf, sizeof(char), len + 1, input);

    // Closing the file
    fclose(input);

    inputBuf[len] = '\0';

    // Parsing the file
    node_t *tmpNode = NULL;
    char *currentEdgeBuf = strtok(inputBuf, "\n");
    while (currentEdgeBuf != NULL) {
        char *node = malloc(sizeof(char) * 4), *nodeToConnect = malloc(sizeof(char) * 4);
        sscanf(currentEdgeBuf, "%s %s", node, nodeToConnect);
        tmpNode = addNode(tmpNode, node);
        tmpNode = addConnection(tmpNode, node, nodeToConnect);
        currentEdgeBuf = strtok(NULL, "\n");
    }

    free(inputBuf);

    return tmpNode;
}

void freeGraph(node_t *graph) {
    node_t *currentNode = graph;
    while (currentNode != NULL) {
        node_t *nextNode = currentNode->nextNodeInGraph;
        free(currentNode->name);
        freeList(currentNode->connectedNodes);
        free(currentNode);
        currentNode = nextNode;
    }
}