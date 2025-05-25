#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100    // 栈的最大容量

// 实现一个顺序栈
typedef struct {
    int data[MAX_SIZE]; // 存储元素的数组
    int top;            // 栈顶指针（指向当前栈顶元素） 
} SeqStack;

void initStack(SeqStack *S) {
    S->top = -1;
}

bool emptyStack(SeqStack *S) {
    return S->top == -1; 
}

bool fullStack(SeqStack *S) {
    return S->top == MAX_SIZE - 1; 
}

void pushStack(SeqStack *S, int value) {
    if (!fullStack(S)) {
        S->data[++S->top] = value;
    } else {
        printf("栈满，无法入栈\n");
    }
}

bool getTop(SeqStack *S, int *value) {
    if (!emptyStack(S)) {
        *value = S->data[S->top];
        return true;
    }
    printf("栈空，没有栈顶\n");
    return false;
}

void popStack(SeqStack *S, int *value) {
    if (!emptyStack(S)) {
        *value = S->data[S->top--];
    } else {
        printf("栈空，无法弹栈\n");
    }
}

void printStack(SeqStack *S) {
    printf("S: ");
    for (int i = 0; i <= S->top; ++i) {
        printf("%4d", S->data[i]);
    }
    printf("\n");
}

int main() {
    SeqStack s;
    int temp;

    // 初始化栈
    initStack(&s);

    // 测试入栈
    pushStack(&s, 5);
    pushStack(&s, 7);
    pushStack(&s, 3);
    pushStack(&s, 9);
    printStack(&s);
    
    // 测试获取栈顶
    getTop(&s, &temp);
    printf("栈顶元素：%d\n", temp);

    // 测试弹栈
    popStack(&s, &temp);
    printf("弹出元素：%d\n", temp);
    popStack(&s, &temp);

    // 测试边界条件
    printf("\n测试边界条件：\n");
    SeqStack S2;
    initStack(&S2);
    popStack(&S2, &temp);    // 触发空栈提示
    getTop(&S2, &temp); // 触发空栈提示

    // 测试栈满
    printf("\n测试栈满：\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        pushStack(&S2, i);
    }
    pushStack(&S2, 100); // 触发栈满提示
}
