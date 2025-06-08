#ifndef __LIST_H__
#define __LIST_H__

#include <time.h>

// 用来控制取余的范围
#define NUM_MAX 100

// 链表节点
typedef struct Node {
    int data;
    struct Node *pNext;
}Node_t, *pNode_t;

// 链表
typedef struct List {
    pNode_t pHead;
    pNode_t pTail;
}List_t, *pList_t;


// 初始化链表
void initList(pList_t pL);
// 释放链表
void destoryList(pList_t pL);
// 获取链表大小
int size_list(pList_t pL);
// 头插法
void headInsert(pList_t pL, pNode_t pNew);
// 尾插法
void tailInsert(pList_t pL, pNode_t pNew);
// 有序插入
void sortInsert(pList_t pL, pNode_t pNew);
// 打印链表
void printList(pList_t pL);
// 删除结点, 按位删除
void deleteNode(pList_t pL, int pos);



#endif
