#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.h"

// 初始化链表
void initList(pList_t pL) {
    memset(pL, 0, sizeof(List_t));
}

// 释放链表所有节点
void free_all_node(pList_t pL) {
    // 释放所有节点
    while (pL->pHead) {
        pNode_t tmp = pL->pHead;
        pL->pHead = tmp->pNext;
        free(tmp);
    }
    pL->pHead = pL->pTail = NULL;
}

// 获取链表大小
int size_list(pList_t pL) {
    int size = 0;
    pNode_t cur = pL->pHead;
    while (cur) {
        ++size;
        cur = cur->pNext;
    }
    return size;
}

// 头插法
void headInsert(pList_t pL, pNode_t pNew) {
    if (NULL == pL->pHead) {
        pL->pHead = pL->pTail = pNew;
        return;
    }

    pNew->pNext = pL->pHead;
    pL->pHead = pNew;
}

// 尾插法
void tailInsert(pList_t pL, pNode_t pNew) {
    if (NULL == pL->pHead) {
        pL->pHead = pL->pTail = pNew;
        return;
    }

    pL->pTail->pNext = pNew;
    pL->pTail = pNew;
}

// 有序插入
void sortInsert(pList_t pL, pNode_t pNew) {
    // 空链表
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
    printf("size:%-4d:", size_list(pL));
    for (; p; p = p->pNext) {
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
    if (pos < 1 || pos > size_list(pL)) {
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
}
