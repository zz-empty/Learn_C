#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SIZE 5  // 队列最大容量（实际可用容量为 MAX_SIZE-1）
#define N 10
#define M 100

typedef struct {
    int data[MAX_SIZE];     // 队列的数据部分
    int front;      // 队头指针（指向队头元素）
    int rear;       // 队尾（指向下一个待插入的位置）
} CicularQueue;

void initQueue(CicularQueue *q) {
    q->front = q->rear = 0;
}

// 判断队列是否为空
bool emptyQueue(CicularQueue *q) {
    return q->front == q->rear;
}

// 判断队列是否为满
bool fullQueue(CicularQueue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// 入队
bool enQueue(CicularQueue *q, int value) {
    if (fullQueue(q)) {
        fprintf(stderr, "队列已满，无法入队\n");
        return false;
    }

    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_SIZE;
    return true;
}

// 出队
bool deQueue(CicularQueue *q, int *value) {
    if (emptyQueue(q)) {
        fprintf(stderr, "队列空，无法出队\n");
        return false;
    }
    
    *value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return true;
}

// 获取队头元素
int getFront(CicularQueue *q, int *value) {
    if (emptyQueue(q)) {
        fprintf(stderr, "队列空\n");
        return -1;
    }
    *value = q->data[q->front];
    return *value; 
}

// 获取队列元素数量
int sizeQueue(CicularQueue *q) {
    return (q->rear - q->front + MAX_SIZE) % MAX_SIZE;
}

// 打印队列内容
void printQueue(CicularQueue *q) {
    if (emptyQueue(q)) {
        printf("队空，无法打印\n");
        return;
    } else {
        printf("队列内容（队头——>队尾）：");
        int idx = q->front;
        for (; idx != q->rear; idx = (idx + 1) % MAX_SIZE) {
            printf("%3d", q->data[idx]);
        }

        printf("\t元素数量：%d\n", sizeQueue(q));
    }
}


int main() {
    CicularQueue q;
    initQueue(&q);

    srand(time(NULL));

    // 入队
    for (int i = 0; i < N; ++i) {
        enQueue(&q, rand() % M);
    }

    printQueue(&q);

    // 出队
    int temp;
    deQueue(&q, &temp);
    printf("出队元素：%d\n", temp);
    deQueue(&q, &temp);
    printf("出队元素：%d\n", temp);
    deQueue(&q, &temp);
    printf("出队元素：%d\n", temp);
    printQueue(&q);

    // 测试循环特性
    enQueue(&q, rand() % M);
    enQueue(&q, rand() % M);
    enQueue(&q, rand() % M);
    printQueue(&q);

    // 测试获取队头
    getFront(&q, &temp);
    printf("队头元素：%d\n", temp);

}
