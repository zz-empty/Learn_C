#include "mylist.h"
// 判断两个链表是否相交
pNode_t find_intersection_node(List_t l1, List_t l2) {
    // 设置两个指针，一个先遍历l1再遍历l2，另一个相反
    // 只要两个指针相等就是相交
    if (l1.pHead == NULL || l2.pHead == NULL) return NULL;
    
    pNode_t p1 = l1.pHead;
    pNode_t p2 = l2.pHead;

    while (p1 != p2) {
        p1 = (p1 == NULL) ? l2.pHead : p1->pNext;
        p2 = (p2 == NULL) ? l1.pHead : p2->pNext;
    }

    return p1;
}
