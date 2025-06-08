#include <stdlib.h>
#include <string.h>
#include "mylist.h"
// 将链表拆分成奇偶链表
void split_odd_even_nodes(List_t list, pList_t odd_list, pList_t even_list) {
    if (NULL == list.pHead) {
        memset(odd_list, 0, sizeof(List_t));
        memset(even_list, 0, sizeof(List_t));
        return;
    }

    if (list.pHead == list.pTail) {
        headInsert(odd_list, list.pHead);
        memset(even_list, 0, sizeof(List_t));
        return;
    }

    pNode_t cur = list.pHead;
    for (int i = 0; cur; ++i, cur = cur->pNext) {
        // i % 2 == 0 加入奇数列表，否则加入偶数列表
        pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
        pNew->data = cur->data;
        if (0 == i % 2) {
            tailInsert(odd_list, pNew);
        } else {
            tailInsert(even_list, pNew);
        }
    }
}
