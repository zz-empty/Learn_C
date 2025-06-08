#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
void initList(pList_t pL) {
    memset(pL, 0, sizeof(List_t));
}

// 释放链表
void destoryList(pList_t pL) {
    // 释放所有节点
    while (pL->pHead) {
        pNode_t tmp = pL->pHead;
        pL->pHead = tmp->pNext;
        free(tmp);
    }
    memset(pL, 0, sizeof(List_t));
}

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

// 使用len个随机元素初始化链表
void initList_random(pList_t pL, int len) {
    memset(pL, 0, sizeof(List_t));
    srand(time(NULL));

    int *arr = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % NUM_MAX;
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

// 逆转链表
void reverseList(pList_t pL) {
    if(pL->pHead == NULL || pL->pHead == pL->pTail) return;

    // 从第二个结点开始，依次头插 
    pNode_t p = pL->pHead->pNext;
    pL->pHead->pNext = NULL;
    pL->pTail = pL->pHead;
    while (p) {
        pNode_t pCur = p;
        p = p->pNext;
        pCur->pNext = NULL;
        headInsert(pL, pCur);
    }
}

void find_fourth_from_end(pList_t pL) {
    if (size_list(pL) < 4) {
        fprintf(stderr, "链表长度小于4，没有倒数第4个节点\n");
        return;
    }

    pNode_t slow_ptr = pL->pHead;   // slow_ptr指向第一个节点
    pNode_t fast_ptr = pL->pHead;
    for (int i = 0; i < 3; ++i) fast_ptr = fast_ptr->pNext; // fast_ptr指向第4个节点

    while (fast_ptr != pL->pTail) {
        fast_ptr = fast_ptr->pNext;
        slow_ptr = slow_ptr->pNext;
    } 

    printf("倒数第4个节点的值：%d\n", slow_ptr->data);
}

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

int has_cycle(pList_t pL) {
    if (NULL == pL->pHead) return 0;
    
    pNode_t fast_ptr = pL->pHead->pNext;
    pNode_t slow_ptr = pL->pHead;

    for (; fast_ptr && fast_ptr->pNext != NULL && fast_ptr->pNext->pNext != NULL; 
            fast_ptr = fast_ptr->pNext->pNext, slow_ptr = slow_ptr->pNext) {
        if (fast_ptr == slow_ptr)  return 1;
    }
    return 0;
}

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

// 移除连续重复的元素
void remove_consecutive_duplicates(pList_t pL) {
    // pre->date = cur->date ---> pre->next = cur->next, free(cur)
    if (NULL == pL->pHead || pL->pHead == pL->pTail) return;

    pNode_t pre = pL->pHead;
    pNode_t cur = pre->pNext;

    while (cur) {
        if (pre->data == cur->data) {
            printf("delete node:%d\n", cur->data);
            pNode_t p = cur;
            pre->pNext = cur->pNext;    // 删除重复的元素
            cur = cur->pNext;
            free(p);                  // 释放结点空间
            p = NULL;
        } else {
            pre = pre->pNext;
            cur = cur->pNext;
        }
    }

    printf("remove success, list.size:%d\n", size_list(pL));
}

void split_odd_even_nodes(List_t list, pList_t odd_list, pList_t even_list) {
    if (NULL == list.pHead) {
        memset(odd_list, 0, sizeof(List_t));
        memset(even_list, 0, sizeof(List_t));
        return;
    }

    if (list.pHead == list.pTail) {
        headInsert(odd_list, list.pHead);
        memset(even_list, 0, sizeof(List_t));
        return;
    }

    pNode_t cur = list.pHead;
    for (int i = 0; cur; ++i, cur = cur->pNext) {
        // i % 2 == 0 加入奇数列表，否则加入偶数列表
        pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
        pNew->data = cur->data;
        if (0 == i % 2) {
            tailInsert(odd_list, pNew);
        } else {
            tailInsert(even_list, pNew);
        }
    }
}

void test1() {
    List_t l1;
    initList_random(&l1, 9);
    printList(&l1);

    /* // 找出链表的倒数第四个节点 */
    /* find_fourth_from_end(&l1); */

    /* // 找出中间节点 */
    /* find_mid_node(&l1); */

    /* // 判断是否有环 */
    /* l1.pTail->pNext = l1.pHead->pNext->pNext; */
    /* if (has_cycle(&l1)) { */
    /*     puts("链表有环"); */
    /* } else { */
    /*     puts("链表没有环"); */
    /* } */

    destoryList(&l1);
}

void test2() {
    // 判断两个链表是否相交
    List_t l1;
    initList_random(&l1, 9);
    /* printList(&l1); */

    List_t l2;
    initList_random(&l2, 9);
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

    destoryList(&l1);
    destoryList(&l2);
}

int main() {
    List_t l1;
    initList_random(&l1, 11);
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

    destoryList(&l1);
}
