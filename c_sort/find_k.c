#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 30
#define MAX 100
#define SWAP_INT(a, b) {int tmp = a; a = b; b = tmp;}

int* random_arr(int len, int max);
void print_arr(int *arr, int len);
int compare(const void *p1, const void *p2);
int patition(int *arr, int left, int right);
int find_k_quick(int *arr, int left, int right, int k);
void adjustMinHeap(int *arr, int pos, int len);
int find_k_heap(int *arr, int len, int k);


int main() {
    int *arr = random_arr(SIZE, MAX);
    print_arr(arr, SIZE);

    // 寻找数组中第k大的数
    int k;
    int result;
    printf("寻找第几大的数：");
    scanf("%d", &k);
    if (k < 1 || k > SIZE) {
        printf("k的范围不合法\n");
    } else {
        result = find_k_quick(arr, 0, SIZE - 1, SIZE - k);
        printf("第%d大的数是%d\n", k, result);
        result = find_k_heap(arr, SIZE, k);
        printf("第%d大的数是%d\n", k, result);
    }

    // 排序数组
    qsort(arr, SIZE, sizeof(int), compare);
    print_arr(arr, SIZE);

    free(arr);
}

// 用堆排查找第k大的数, 找数组第n-k位
int find_k_heap(int *arr, int len, int k) {
    // 维护一个数量为k的小根堆，堆顶是最小的(第一个元素）
    for (int i = k / 2 - 1; i >= 0; --i) {
        adjustMinHeap(arr, i, len);
    }
    
    // 用剩余元素，不断与堆顶比较。如果<=堆顶无视，大于堆顶就交换并调整小根堆
    for (int i = k; i < len; ++i) {
        if (arr[i] > arr[0]) {
            SWAP_INT(arr[i], arr[0]); 
            adjustMinHeap(arr, 0, k);
        }
    }
    
    return arr[0];
}

// 从pos下标开始往下调整小根堆
void adjustMinHeap(int *arr, int pos, int len) {
    int dad = pos;
    int son = 2 * pos + 1;
    while (son < len) {
        if (son + 1 < len && arr[son + 1] < arr[son]) {
            son = son + 1;
        }
        if (arr[son] < arr[dad]) {
            SWAP_INT(arr[son], arr[dad]);
            dad = son;
            son = 2 * dad + 1;
        } else {
            break;
        }
    }
}


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

// qsort参数
int compare(const void *p1, const void *p2) {
    int *l = (int*)p1;
    int *r = (int*)p2;
    return *l - *r;
}

// 快排的划分函数
int patition(int *arr, int left, int right) {
    int i, j;
    for (i = left, j = left; i < right; ++i) {
        if (arr[i] <= arr[right]) {
            SWAP_INT(arr[i], arr[j]);
            ++j;
        }
    }
    SWAP_INT(arr[j], arr[right]);
    return j;
}

// 用快排寻找第k大的数, 最后一个参数是len-k
// 找第k大的位置，就是找编号len-k
int find_k_quick(int *arr, int left, int right, int k) {
    if (left <= right) {
        int pivot = patition(arr, left, right);        
        if (pivot == k) {
            return arr[pivot]; 
        } else if (pivot > k) {
            find_k_quick(arr, left, pivot - 1, k);
        } else {
            find_k_quick(arr, pivot + 1, right, k);   
        }
    }
}
