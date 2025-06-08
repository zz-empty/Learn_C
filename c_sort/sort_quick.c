#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10
/* #define SIZE 300000000 */
#define MAX 100
#define SWAP_INT(a, b) {int tmp = a; a = b; b = tmp;}

// 生成一个随机数组
int* random_arr(int len, int max) {
    srand(time(NULL));
    int *arr = (int*)malloc(len * sizeof(int));

    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % max;
    }
    return arr;
}

// 将数组划分成左边小于pivot，右边大于等于pivot
int patition(int *arr, int left, int right) {
    int i, j;
    for (i = left, j = left; i < right; ++i) {
        if (arr[i] < arr[right]) {
            SWAP_INT(arr[i], arr[j]);
            ++j;
        } 
    }
    SWAP_INT(arr[right], arr[j]);
    return j;
}

// 打印int数组
void print_arr(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%3d", arr[i]);
    }
    printf("\n");
}

// 快速排序，左闭右闭区间
void quick_sort(int *arr, int left, int right) {
    if (left < right) {
        int pivot = patition(arr, left, right);
        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot + 1, right);
    } 
}

// qsort的compare参数
int compare(const void *p1, const void *p2) {
    int *pL = (int*)p1;
    int *pR = (int*)p2;
    return *pL - *pR;
}

int sort_time(int *arr, int len) {
    time_t begin = time(NULL);
    /* shell_sort(arr, len); */
    /* bubble_sort(arr, len); */
    /* select_sort(arr, len); */
    /* insert_sort(arr, len); */
    /* quick_sort(arr, 0, len - 1); */
    qsort(arr, len, sizeof(int), compare);
    time_t end = time(NULL);
    return end - begin;
}

// 链表节点
typedef struct Node {
    int data;
    struct Node *pNext;
}Node_t, *pNode_t;

// 链表
typedef struct List {
    pNode_t pHead;
    pNode_t pTail;
    int size;
}List_t, *pList_t;

// 初始化链表
void initList(pList_t pL) {
    memset(pL, 0, sizeof(List_t));
}

// 释放链表
void destoryList(pList_t pL) {
    // 释放所有节点
    while (pL->pHead != NULL) {
        pNode_t tmp = pL->pHead;
        pL->pHead = tmp->pNext;
        free(tmp);
    }
    memset(pL, 0, sizeof(List_t));
}

// 头插法
void headInsert(pList_t pL, pNode_t pNew) {
    if (NULL == pL->pHead) {
        pL->pHead = pL->pTail = pNew;
        return;
    }

    pNew->pNext = pL->pHead;
    pL->pHead = pNew;
    pL->size++;
}

// 打印链表
void printList(pList_t pL) {
    pNode_t p = pL->pHead;
    printf("size:%-4d,", pL->size);
    for (; p != NULL; p = p->pNext) {
        printf("%4d", p->data);
    }
    printf("\n");
}

void test() {
    int *arr = random_arr(SIZE, MAX);
    /* print_arr(arr, SIZE); */

    /* // 快速排序 */
    /* quick_sort(arr, 0, SIZE - 1); */
    /* print_arr(arr, SIZE); */

    /* // qsort */
    /* qsort(arr, SIZE, sizeof(int), compare); */
    /* print_arr(arr, SIZE); */

    // 测试排序的时间
    printf("排序%d个数，total_time = %ds\n", SIZE, sort_time(arr, SIZE));

    free(arr);
}

int compare_index(const void *p1, const void *p2) {
    pNode_t pL = *(pNode_t*)p1;
    pNode_t pR = *(pNode_t*)p2;
    return  pL->data - pR->data; 
}

int main() {
    // 排序链表
    List_t list;
    initList(&list); 
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i) {
        pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
        pNew->data = rand() % MAX;
        headInsert(&list, pNew);
    }

    printList(&list);

    // 用qsort排序链表, 先建立索引
    pNode_t indexs[SIZE];
    pNode_t cur = list.pHead;
    for (int i = 0; i < SIZE; ++i, cur = cur->pNext) {
        indexs[i] = cur; 
    }
    qsort(indexs, SIZE, sizeof(pNode_t), compare_index);
    for (int i = 0; i < SIZE; ++i) {
        printf("%3d", indexs[i]->data);
    }
    printf("\n");

    printList(&list);

    destoryList(&list);
}
