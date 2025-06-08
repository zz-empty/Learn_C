#include "mylist.h"

// 逆转链表
void reverseList(pList_t pL) {
    if(pL->pHead == NULL || pL->pHead == pL->pTail) return;

    // 从第二个结点开始，依次头插 
    pNode_t p = pL->pHead->pNext;
    pL->pHead->pNext = NULL;
    pL->pTail = pL->pHead;
    while (p) {
        pNode_t pCur = p;
        p = p->pNext;
        pCur->pNext = NULL;
        headInsert(pL, pCur);
    }
}
