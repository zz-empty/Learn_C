#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"
// 移除连续重复的元素
void remove_consecutive_duplicates(pList_t pL) {
    // pre->date = cur->date ---> pre->next = cur->next, free(cur)
    if (NULL == pL->pHead || pL->pHead == pL->pTail) return;

    pNode_t pre = pL->pHead;
    pNode_t cur = pre->pNext;

    while (cur) {
        if (pre->data == cur->data) {
            printf("delete node:%d\n", cur->data);
            pNode_t p = cur;
            pre->pNext = cur->pNext;    // 删除重复的元素
            cur = cur->pNext;
            free(p);                  // 释放结点空间
            p = NULL;
        } else {
            pre = pre->pNext;
            cur = cur->pNext;
        }
    }

    printf("remove success, list.size:%d\n", size_list(pL));
}
