#include "mylist.h"


// 找链表的中间节点
void find_mid_node(pList_t pL) {
    if (pL->pHead == NULL) {
        fprintf(stderr, "链表为空，没有中间节点\n");
        return;
    }

    pNode_t fast_ptr = pL->pHead;
    pNode_t slow_ptr = pL->pHead;

    while (fast_ptr->pNext != NULL && fast_ptr->pNext->pNext != NULL) {
        fast_ptr = fast_ptr->pNext->pNext;
        slow_ptr = slow_ptr->pNext;
    } 

    printf("中间节点的值：%d\n", slow_ptr->data);
}
