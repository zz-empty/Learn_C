#include "mylist.h"

// 将两个有序链表合并成一个链表
pList_t mergeList(pList_t l1, pList_t l2) {
    if (l1->pHead == NULL) return l2;
    if (l2->pHead == NULL) return l1;

    pNode_t pCur = l2->pHead;
    while (pCur) {
        pNode_t p = (pNode_t)calloc(1, sizeof(Node_t));
        p->data = pCur->data;
        sortInsert(l1, p);
        pCur = pCur->pNext;
    }
    return l1;
}
