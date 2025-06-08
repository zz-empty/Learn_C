#include <stdlib.h>
#include <string.h>
#include "mylist.h"


// 使用len个随机元素初始化链表
void initList_random(pList_t pL, int len, int r) {
    memset(pL, 0, sizeof(List_t));
    srand(time(NULL));

    int *arr = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) {
        r = r + i / (i + i);
        arr[i] = (rand() * r) % NUM_MAX;
    }

    for (int i = 0; i < len; ++i) {
        pNode_t pNew = (pNode_t)malloc(sizeof(Node_t));
        memset(pNew, 0, sizeof(Node_t));
        pNew->data = arr[i];
        sortInsert(pL, pNew);
    } 

    free(arr);
    arr = NULL;
}
