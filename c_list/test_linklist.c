#include "mylist.h"

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
    initList_random(&l1, 10, 34);
    printf("l1: ");
    printList(&l1);
    initList_random(&l2, 10, 45);
    printf("l2: ");
    printList(&l2);
    

#if 0
    printf("-----------有序合并两个链表--------------\n");
    mergeList(&l1, &l2);
    printList(&l1);

    destoryList(&l1);
    destoryList(&l2);
#endif
}
