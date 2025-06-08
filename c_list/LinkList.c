#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// 尾插法
void tailInsert(pList_t pL, pNode_t pNew) {
    if (NULL == pL->pHead) {
        pL->pHead = pL->pTail = pNew;
        return;
    }

    pL->pTail->pNext = pNew;
    pL->pTail = pNew;
    pL->size++;
}

// 有序插入
void sortInsert(pList_t pL, pNode_t pNew) {
    // 空链表
    pL->size++;
    if (NULL == pL->pHead) {
        pL->pHead = pL->pTail = pNew;
    }
    
    // 原链表的所有指针域都不变
    else if (pNew->data < pL->pHead->data) {
        pNew->pNext = pL->pHead;
        pL->pHead = pNew;
    }
    
    // 有结点的指针域发生变化
    else {
        pNode_t pPre = pL->pHead;   // 用来修改
        pNode_t pCur = pPre->pNext;   // 用来定位
        for (; pCur; pPre = pCur, pCur = pCur->pNext)  {
            // 一旦找到位置，就跳出循序
            if (pCur->data > pNew->data) {
                pPre->pNext = pNew;
                pNew->pNext = pCur;
                break;
            } 
        } 

        // 新元素最大
        if (NULL == pCur) {
            pL->pTail->pNext = pNew;
            pL->pTail = pNew;
        }
    }
    return;
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

// 删除结点, 按位删除
void deleteNode(pList_t pL, int pos) {
    // 边界：头，尾
    // 1. 先判断删除位置是否合法
    // 2. 从位置1开始找到pos结束，删除pos位置的结点
    //      如果是第一个修改头指针
    //      如果是最后一个修改尾指针
    //      释放被删除的结点
    //      --size
    if (pos < 1 || pos > pL->size) {
        fprintf(stderr, "删除位置不合法\n");
        return;
    }

    pNode_t pD = pL->pHead;
    if (1 == pos) {  
        pL->pHead = pD->pNext;
        free(pD);
        pD = NULL;
    } else {
        pNode_t pPre = pL->pHead;
        pD = pPre->pNext;
        for (int i = 2; i != pos; ++i, pPre = pD, pD = pD->pNext);
        pPre->pNext = pD->pNext;
        if (pL->pTail == pD) {
            pL->pTail = pPre;
        }
        free(pD);
        pD = NULL;
    }
    --pL->size;
}

// 将两个有序链表合并成一个链表
pList_t mergeList(pList_t l1, pList_t l2) {
    if (l1->pHead == NULL) return l2;
    if (l2->pHead == NULL) return l1;

    pNode_t pCur = l2->pHead;
    while (pCur) {
        pNode_t p = (pNode_t)calloc(1, sizeof(Node_t));
        p->data = pCur->data;
        sortInsert(l1, p);
        pCur = pCur->pNext;
    }
    return l1;
}

void test1()
{
    List_t list;
    initList(&list);
    
    /* printf("输入要插入的数据："); */
    int srcs[] = {3, 2, 8, 9, 1, 7};
    int len = sizeof(srcs) / sizeof(srcs[0]);
    for (int i = 0; i < len; ++i) {
        /* printf("i = %d\n", i); */
        pNode_t pNew = (pNode_t)malloc(sizeof(Node_t));
        memset(pNew, 0, sizeof(Node_t));
        pNew->data = srcs[i];
        sortInsert(&list, pNew);
        /* headInsert(&list, pNew); */
        /* tailInsert(&list, pNew); */
    } 

    printf("---------sort_insert----------\n");
    printList(&list);


    printf("---------delete_pos-----------\n");
    deleteNode(&list, 2);
    printList(&list);
    deleteNode(&list, 7);
    printList(&list);
    deleteNode(&list, 5);
    printList(&list);

    destoryList(&list);
}

int main() {
    List_t l1, l2;
    initList(&l1);
    initList(&l2);
    
    int srcs[] = {3, 12, 8, 19, 1, 17};
    int len = sizeof(srcs) / sizeof(srcs[0]);
    for (int i = 0; i < len; ++i) {
        /* printf("i = %d\n", i); */
        pNode_t pNew = (pNode_t)malloc(sizeof(Node_t));
        memset(pNew, 0, sizeof(Node_t));
        pNew->data = srcs[i];
        sortInsert(&l1, pNew);
    } 
    printf("l1: ");
    printList(&l1);

    int srcs2[] = {13, 22, 18, 29, 11, 27};
    int len2 = sizeof(srcs) / sizeof(srcs[0]);
    for (int i = 0; i < len2; ++i) {
        /* printf("i = %d\n", i); */
        pNode_t pNew = (pNode_t)malloc(sizeof(Node_t));
        memset(pNew, 0, sizeof(Node_t));
        pNew->data = srcs2[i];
        sortInsert(&l2, pNew);
    } 
    printf("l2: ");
    printList(&l2);

    printf("-----------有序合并两个链表--------------\n");
    mergeList(&l1, &l2);
    printList(&l1);

    destoryList(&l1);
    destoryList(&l2);
}
