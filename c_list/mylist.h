#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


// 将两个有序链表合并成一个链表
pList_t mergeList(pList_t l1, pList_t l2);
// 使用len个随机元素初始化链表
void initList_random(pList_t pL, int len, int r);
// 逆转链表
void reverseList(pList_t pL);
// 找链表的中间节点
void find_mid_node(pList_t pL);
// 移除连续重复的元素
void remove_consecutive_duplicates(pList_t pL);
// 判断两个链表是否相交
pNode_t find_intersection_node(List_t l1, List_t l2);
// 判断链表是否有环
int isCycle(pList_t pL);

#endif
