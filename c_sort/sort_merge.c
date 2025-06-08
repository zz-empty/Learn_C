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

void merge(int *arr, int left, int mid, int right, int temp[]) {
    int i = left;   // 左半区起始位置
    int j = mid + 1;  // 右半区起始位置
    int k = 0;   // 临时数组索引

    // 按序合并到临时数组
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }    

    // 处理剩余元素
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // 将合并结果复制回原数组
    for (i = 0; i < k; ++i) {
        arr[left + i] = temp[i];
    }
}

void _merge_sort(int *arr, int left, int right, int temp[]) {
    if (left >= right) return;  // 递归终止条件
    int mid = left + (right - left) / 2;        // 防溢出计算终点
    _merge_sort(arr, left, mid, temp);      // 递归左半区
    _merge_sort(arr, mid + 1, right, temp); // 递归右半区
    merge(arr, left, mid, right, temp);     // 合并左右半区
}

void merge_sort(int *arr, int len) {
    int *temp = (int*)malloc(sizeof(int) * len);        // 一次性分配临时数组
    if (!temp) {
        printf("内存分配失败\n");
        return;
    }

    _merge_sort(arr, 0, len - 1, temp);
    free(temp);     // 释放临时数组
}


int sort_time(int *arr, int len) {
    time_t begin = time(NULL);
    merge_sort(arr, len);
    time_t end = time(NULL);
    return end - begin;
}

int main() {
    int *arr = random_arr(SIZE, MAX);
    /* print_arr(arr, SIZE); */

    /* // 归并排序 */
    /* merge_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    // 测试排序的时间
    printf("排序%d个数，total_time = %ds\n", SIZE, sort_time(arr, SIZE));

    free(arr);
    return 0;
}
