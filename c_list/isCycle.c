#include "mylist.h"

// 判断链表是否有环
int isCycle(pList_t pL) {
    if (NULL == pL->pHead) return 0;
    
    pNode_t fast_ptr = pL->pHead->pNext;
    pNode_t slow_ptr = pL->pHead;

    for (; fast_ptr && fast_ptr->pNext != NULL && fast_ptr->pNext->pNext != NULL; 
            fast_ptr = fast_ptr->pNext->pNext, slow_ptr = slow_ptr->pNext) {
        if (fast_ptr == slow_ptr)  return 1;
    }
    return 0;
}
