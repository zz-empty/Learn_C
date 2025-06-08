#include <stdlib.h>
#include <time.h>
#include "mylist.h"

pList_t random_list(int len, int max) {
    pList_t pL = (pList_t)malloc(sizeof(List_t));
    pL->pHead = pL->pTail = NULL;

    srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
        pNew->data = rand() % max;
        headInsert(pL, pNew);
    }

    return pL;
}
