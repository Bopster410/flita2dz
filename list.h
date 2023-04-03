#ifndef FLITA2_SET_H
#define FLITA2_SET_H
#include <stdbool.h>

typedef enum type {
    INT,
    STR
} type;

typedef struct list {
    void *value;
    struct list *nextElement;
    type valueType;
} list;


// Checks if element is in list
bool isInList(list *pList, void *element);

// Adds element [newElement] to list
list* addListElement(list *pList, void *newElement, type valueType);

// Removes element [element] from list
list* removeListElement(list *pList, void *element);

// Prints all list elements
void printList(list *pList);

#endif