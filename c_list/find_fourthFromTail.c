#include "mylist.h"


// 找链表倒数第4个节点
void find_fourth_from_end(pList_t pL) {
    if (size_list(pL) < 4) {
        fprintf(stderr, "链表长度小于4，没有倒数第4个节点\n");
        return;
    }

    pNode_t slow_ptr = pL->pHead;   // slow_ptr指向第一个节点
    pNode_t fast_ptr = pL->pHead;
    for (int i = 0; i < 3; ++i) fast_ptr = fast_ptr->pNext; // fast_ptr指向第4个节点

    while (fast_ptr != pL->pTail) {
        fast_ptr = fast_ptr->pNext;
        slow_ptr = slow_ptr->pNext;
    } 

    printf("倒数第4个节点的值：%d\n", slow_ptr->data);
}
