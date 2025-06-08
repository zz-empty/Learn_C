#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"

#define SIZE 10
/* #define SIZE 300000000 */
#define MAX 100

// qsort排序链表索引
int compare_index(const void *p1, const void *p2) {
    pNode_t pL = *(pNode_t*)p1;
    pNode_t pR = *(pNode_t*)p2;
    return  pL->data - pR->data; 
}

pList_t random_list(int len, int max);

int main() {
    // 生成一个随机链表
    pList_t pL = random_list(SIZE, MAX);
    printList(pL);

    // 建立链表索引
    pNode_t indexs[SIZE];
    pNode_t cur = pL->pHead;    // 遍历链表
    for (int i = 0; i < SIZE; ++i, cur = cur->pNext) {
        indexs[i] = cur; 
    }

    // 排序链表索引
    qsort(indexs, SIZE, sizeof(pNode_t), compare_index);

    // 打印索引
    for (int i = 0; i < SIZE; ++i) {
        printf("%3d", indexs[i]->data);
    }
    printf("\n");

    printList(pL);
    destoryList(pL);
}
