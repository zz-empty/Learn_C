#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// 链栈结点
typedef struct SNode {
    int data;
    struct SNode *pNext;
}SNode_t, *pSNode_t;

// 链栈
typedef struct {
    pSNode_t pTop;
    int size;
}Stack_t, *pStack_t;

// 初始化
void initStack(pStack_t pS) {
    memset(pS, 0, sizeof(Stack_t));
}

// 压栈
void push(pStack_t pS, int data) {
    pSNode_t pNew = (pSNode_t)calloc(1, sizeof(SNode_t));
    pNew->data = data;
    
    pNew->pNext = pS->pTop;
    pS->pTop = pNew;
    pS->size++;    
}

// 查看栈顶
int top(pStack_t pS) {
    if (pS->size) {
        printf("top:%d\n", pS->pTop->data);
        return pS->pTop->data;
    }
    printf("empty!\n");
    return -1;
}

// 弹栈
void pop(pStack_t pS) {
    if (pS->pTop) {
        pSNode_t p = pS->pTop;
        pS->pTop = p->pNext;
        free(p);
        pS->size--;
    }
}

// 销毁链栈
void destory(pStack_t pS) {
    while (pS->pTop) {
        pop(pS);
    }
}

int main() {
    Stack_t s;
    initStack(&s);
    top(&s);

    push(&s, 8);
    top(&s);
    push(&s, 4);
    top(&s);
    push(&s, 6);
    top(&s);
    push(&s, 3);
    top(&s);

    pop(&s);
    top(&s);
    pop(&s);
    top(&s);
    pop(&s);
    top(&s);
    pop(&s);
    top(&s);
    pop(&s);
    top(&s);
    pop(&s);
    top(&s);

    destory(&s);
}
