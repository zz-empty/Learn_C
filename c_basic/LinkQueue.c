#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define M 100

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;     // 队头
    Node *tail;     // 队尾
} LinkQueue;

// 初始化
void initQueue(LinkQueue *q) {
    q->head = q->tail = NULL;
}


// 判空
bool emptyQueue(LinkQueue *q) {
    return q->head == NULL;
}

// 入队
void enQueue(LinkQueue *q, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node)); 
    new_node->data = value;
    new_node->next = NULL;

    if (emptyQueue(q)) {
        q->head = q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

// 出队
void deQueue(LinkQueue *q, int *value) {
    if (emptyQueue(q)) {
        fprintf(stderr, "队空，无法出队\n");
        return;
    }

    *value = q->head->data;
    Node *node = q->head;
    q->head = q->head->next;
    free(node);
    node = NULL;
}

// 队列大小
int sizeQueue(LinkQueue *q) {
    if (q->head == NULL) {
        return 0;
    }

    int size = 0;
    Node *cur = q->head;
    for (; cur; cur = cur->next) {
        ++size;
    }
    return size;
}

int getFront(LinkQueue *q) {
    if (emptyQueue(q)) {
        fprintf(stderr, "队空，没有队头\n");
        return -1;
    }
    return q->head->data;
}

// 打印队列
void printQueue(LinkQueue *q) {
    if (emptyQueue(q)) {
        fprintf(stderr, "队空，没有元素\n");
        return;
    }

    printf("队列元素（队头->队尾）：");
    for (Node *cur = q->head; cur; cur = cur->next) {
        printf("%3d", cur->data); 
    }

    printf("\t队列大小：%d\n", sizeQueue(q));
}

int main() {
    LinkQueue q;
    initQueue(&q);

    srand(time(NULL));
    // 测试入队
    enQueue(&q, rand() % M);
    enQueue(&q, rand() % M);
    enQueue(&q, rand() % M);
    enQueue(&q, rand() % M);
    enQueue(&q, rand() % M);

    printQueue(&q);

    // 测试出队
    int value;
    deQueue(&q, &value);
    printf("出队元素：%d\n", value);
    deQueue(&q, &value);
    printf("出队元素：%d\n", value);
    deQueue(&q, &value);
    printf("出队元素：%d\n", value);

    printQueue(&q);

    // 测试获取队头
    printf("队头：%d\n", getFront(&q));
    printQueue(&q);

}
