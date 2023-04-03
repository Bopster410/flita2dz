#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

list *addListElement(list *pList, void *newElement, type valueType) {
    bool isFirstElement = pList == NULL, isInListEl;
    if (!isFirstElement) {
        isInListEl = isInList(pList, newElement);
    }
    if (isFirstElement || !isInListEl) {
        list *pTemp = malloc(sizeof(list));
        pTemp->value = newElement;
        pTemp->nextElement = pList;
        pTemp->valueType = valueType;
        return pTemp;
    }
    return pList;
}

list *removeListElement(list *pList, void *element) {
    list *nextElement = pList->nextElement;
    if (pList->value == element) {
        pList = pList->nextElement;
        return pList;
    } else if (nextElement->value == element && nextElement->valueType == INT) {
        pList->nextElement = nextElement->nextElement;
        free(nextElement);
        return pList;
    } else if (nextElement->valueType == STR) {
        if (strcmp(nextElement->value, element) == 0) {
            pList->nextElement = nextElement->nextElement;
            free(nextElement->value);
            free(nextElement);
            return pList;
        }
    } else if (nextElement->nextElement == NULL) {
        return pList;
    } else {
        pList->nextElement = removeListElement(pList->nextElement, element);
        return pList;
    }
}

void printList(list *pList) {
    if (pList != NULL) {
        char *formatStr;
        switch (pList->valueType) {
            case INT:
                formatStr = "%d ";
                break;
            case STR:
                formatStr = "%s ";
                break;
            default:
                formatStr = "error\n";
        }
        if (pList->nextElement == NULL) {
            printf(formatStr, pList->value);
        } else {
            printf(formatStr, pList->value);
            printList(pList->nextElement);
        }
    } else {
        printf("{}");
    }

}

bool isInList(list *pList, void *element) {
    bool isElement = false;
    if (pList->valueType == STR) {
        isElement = strcmp(pList->value, element) == 0;
    } else {
        isElement = pList->value == element;
    }

    if (isElement) {
        return true;
    } else if (pList->nextElement == NULL) {
        return false;
    } else {
        return isInList(pList->nextElement, element);
    }
}
