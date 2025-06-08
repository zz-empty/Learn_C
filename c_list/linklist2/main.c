#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.h"

#define RANDOM_CONTROL 10

// 判断两个链表是否相交
pNode_t find_intersection_node(List_t l1, List_t l2);
// 使用len个随机元素初始化链表
void initList_random(pList_t pL, int len, int r);

// 找链表倒数第4个节点
void find_fourth_from_end(pList_t pL);
// 将链表拆分成奇偶链表
void split_odd_even_nodes(List_t list, pList_t odd_list, pList_t even_list);
// 判断链表是否有环
int isCycle(pList_t pL);
// 找链表的中间节点
void find_mid_node(pList_t pL);

void test1() {
    List_t l1;
    initList_random(&l1, 9, RANDOM_CONTROL);
    printList(&l1);

    /* // 找出链表的倒数第四个节点 */
    /* find_fourth_from_end(&l1); */

    /* // 找出中间节点 */
    /* find_mid_node(&l1); */

    /* // 判断是否有环 */
    /* l1.pTail->pNext = l1.pHead->pNext->pNext; */
    /* if (isCycle(&l1)) { */
    /*     puts("链表有环"); */
    /* } else { */
    /*     puts("链表没有环"); */
    /* } */

    free_all_node(&l1);
}

void test2() {
    // 判断两个链表是否相交
    List_t l1;
    initList_random(&l1, 9, RANDOM_CONTROL);
    /* printList(&l1); */

    List_t l2;
    initList_random(&l2, 9, RANDOM_CONTROL);
    printList(&l2);

    // 增加交点
    headInsert(&l1, l2.pHead->pNext->pNext);
    printList(&l1);

    pNode_t result = find_intersection_node(l1, l2);
    if (result != NULL) {
        printf("交点的值为:%d\n", result->data);
    } else {
        printf("链表不相交\n");
    }

    free_all_node(&l1);
    free_all_node(&l2);
}

int main() {
    List_t l1;
    initList_random(&l1, 11, RANDOM_CONTROL);
    printList(&l1);


    /* // 移除链表中的重复元素 */
    /* remove_consecutive_duplicates(&l1); */
    /* printList(&l1); */

    // 拆分成两个链表
    List_t odd_list;
    List_t even_list;
    initList(&odd_list);
    initList(&even_list);
    split_odd_even_nodes(l1, &odd_list, &even_list);

    printList(&odd_list);
    printList(&even_list);
    printList(&l1);

    free_all_node(&l1);
}
