#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SIZE 10
#define M 100

// 二叉树结点
typedef struct TreeNode {
    int val;    // 节点值
    struct TreeNode *left;      // 左子树指针
    struct TreeNode *right;     // 右子树指针
} TreeNode;


// 队列结点
typedef struct QueueNode {
    TreeNode *data;
    struct QueueNode *next;
} QueueNode;

// 链式队列
typedef struct {
    QueueNode *head;     // 队头
    QueueNode *tail;     // 队尾
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
void enQueue(LinkQueue *q, QueueNode *node) {
    if (emptyQueue(q)) {
        q->head = q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
}

// 出队
TreeNode* deQueue(LinkQueue *q) {
    if (emptyQueue(q)) {
        /* fprintf(stderr, "队空，无法出队\n"); */
        return NULL;
    }

    QueueNode *cur = q->head;
    TreeNode *node = cur->data;
    q->head = q->head->next;
    free(cur);
    cur = NULL;
    return node;
}

// 队列大小
int sizeQueue(LinkQueue *q) {
    if (q->head == NULL) {
        return 0;
    }

    int size = 0;
    QueueNode *cur = q->head;
    for (; cur; cur = cur->next) {
        ++size;
    }
    return size;
}

TreeNode* getFront(LinkQueue *q) {
    if (emptyQueue(q)) {
        fprintf(stderr, "队空，没有队头\n");
        return NULL;
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
    for (QueueNode *cur = q->head; cur; cur = cur->next) {
        printf("%3d", cur->data->val); 
    }

    printf("\t队列大小：%d\n", sizeQueue(q));
}

// 二叉树层次建树，固定结点
TreeNode* build_tree_from_arr(int* arr, int size) {
    TreeNode *root = NULL;
    // 将数组格式化成一个链式队列
    // 队列中是所有还没有放置孩子结点的树节点
    LinkQueue q;
    initQueue(&q);
    for (int i = 0; i < size; ++i) {
        TreeNode *pNew = (TreeNode*)calloc(1, sizeof(TreeNode));    // 新建一个树节点
        pNew->val = arr[i];     // 树节点赋值
        QueueNode *pQueueNode = (QueueNode*)calloc(1, sizeof(QueueNode));    // 新建一个队列结点
        pQueueNode->data = pNew;    // 队列结点赋值
        enQueue(&q, pQueueNode);      // 新队列入队
        
        if (NULL == root) {  // 如果树空
            root = pNew;
            q.head = q.tail = pQueueNode;
        } else {    // 树非空
            // 新节点入队
            q.tail->next = pQueueNode;
            q.tail = pQueueNode;

            // 放置队头指向的树节点的孩子域
            TreeNode *cur = q.head->data; 
            if (NULL == cur->left) {
                cur->left = pNew; 
            } else {
                cur->right = pNew;  // 队头的孩子域已放完，出队
                deQueue(&q);
            }
        }
    } 
    
    return root;
}

// 二叉树层次建树，结点数位置
TreeNode* build_tree_from_queue(LinkQueue *q) {
    TreeNode *root = NULL;

    // 一个指针，指向等待放孩子的树节点
    // 另一个指针，遍历队列的剩余结点
    for (QueueNode *pNode = q->head; pNode; pNode = pNode->next) {
        if (NULL == root) {     // 树空
            root = pNode->data;
        } else {
            TreeNode *cur = q->head->data;  // 队头存储的，就是等待放置孩子的树节点
            if (NULL == cur->left) {
                cur->left = pNode->data;
            } else {
                cur->right = pNode->data;
                deQueue(q);
            }
        }
    }

    return root;
}

void preOrder(TreeNode *root) {
    if (root) {
        printf("%3d", root->val);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void midOrder(TreeNode *root) {
    if (root) {
        midOrder(root->left);
        printf("%3d", root->val);
        midOrder(root->right);
    }
}

void postOrder(TreeNode *root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%3d", root->val);
    }
}

void printTree(TreeNode *root) {
    preOrder(root);
    printf("\n");
}

void print_arr(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%3d", arr[i]);
    }
    printf("\n");
}

void leverOrder(TreeNode *root) {
    if (!root) return;
    
    TreeNode **queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int level_size = rear - front;  // 当前层次的大小
        for (int i = 0; i < level_size; ++i) {
            TreeNode *node = queue[front++];
            printf("%3d", node->val);
            if (node->left) queue[rear++] = node->left;     // 如果当前节点的左孩子存在，加入队列
            if (node->right) queue[rear++] = node->right;            // 如果当前节点的右孩子存在，加入队列
        }
        printf("\n");
    }
    free(queue);
}


int main() {
    srand(time(NULL));    
    int arr[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; ++i) {
        arr[i] = rand() % M;
    }
    print_arr(arr, MAX_SIZE);

    // 固定结点数的层次建树
    TreeNode *root = build_tree_from_arr(arr, MAX_SIZE);
    printTree(root);
    leverOrder(root);
    printf("\n");


    // 不固定节点数的层次建树
    LinkQueue q;
    initQueue(&q);
    for (int i = 0; i < 2 * MAX_SIZE; ++i) {
        TreeNode *pNew = (TreeNode*)calloc(1, sizeof(TreeNode));
        pNew->val = arr[i % MAX_SIZE];
        QueueNode *pQueueNode = (QueueNode*)calloc(1, sizeof(QueueNode));
        pQueueNode->data = pNew;
        enQueue(&q, pQueueNode);
    }
    printQueue(&q);
    root = NULL;
    root = build_tree_from_queue(&q);
    leverOrder(root);
    printf("\n");
}
