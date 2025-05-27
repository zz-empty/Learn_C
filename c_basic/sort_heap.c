#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* #define SIZE 10 */
#define SIZE 300000000
#define MAX 100
#define SWAP_INT(a, b) {int tmp = a; a = b; b = tmp;}

// 生成一个随机数组
int* random_arr(int len, int max) {
    srand(time(NULL));
    int *arr = (int*)malloc(len * sizeof(int));

    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % max;
    }
    return arr;
}


// 打印int数组
void print_arr(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%3d", arr[i]);
    }
    printf("\n");
}

// qsort的compare参数
int compare(const void *p1, const void *p2) {
    int *pL = (int*)p1;
    int *pR = (int*)p2;
    return *pL - *pR;
}

void adjustMaxHeap(int *arr, int pos, int len) {
    // pos是父结点下标, 确保pos位置的结点大于所有下属结点
    // 先找出最大的孩子下标
    // 再与父结点比较。如果比父结点大，就交换。交换后如果孩子结点存在，就继续向下比较。
    int dad = pos;  // 父结点下标
    int son = 2 * pos + 1;  // 左孩子下标
    
    while (son < len) {
        if (son + 1 < len && arr[son + 1] > arr[son]) {
            son = son + 1;
        }

        if (arr[son] > arr[dad]) {      // 孩子节点 > 父节点, 交换并向下循环
            SWAP_INT(arr[son], arr[dad]);
            dad = son;
            son = 2 * dad + 1;
        } else {    // 父结点 > 孩子结点，退出
            break; 
        }
    }
}

// 堆排序
void heap_sort(int *arr, int len) {
    // 最后一个父结点编号:len / 2, 下标: len / 2 - 1

    // 从最后一个父结点开始调整大根堆，直到第一个结点
    for (int i = len / 2 - 1; i >= 0; --i) {
        adjustMaxHeap(arr, i, len);
    }
    // 交换第一个结点和最后一个结点，减少堆的规模
    SWAP_INT(arr[0], arr[len - 1]);
    // 对剩余元素从头建堆，建完后，交换堆顶和最后元素，缩小堆的规模。重复直到堆的规模为2
    for (int i = len - 1; i > 1; --i) {
        adjustMaxHeap(arr, 0, i);
        SWAP_INT(arr[0], arr[i - 1]);
    }
}

int sort_time(int *arr, int len) {
    time_t begin = time(NULL);
    /* shell_sort(arr, len); */
    /* bubble_sort(arr, len); */
    /* select_sort(arr, len); */
    /* insert_sort(arr, len); */
    /* qsort(arr, len, sizeof(int), compare); */
    heap_sort(arr, len);
    time_t end = time(NULL);
    return end - begin;
}

int main() {
    int *arr = random_arr(SIZE, MAX);
    /* print_arr(arr, SIZE); */

    /* // 堆排序 */
    /* heap_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    // 测试排序的时间
    printf("排序%d个数，total_time = %ds\n", SIZE, sort_time(arr, SIZE));

    free(arr);
    return 0;
}
