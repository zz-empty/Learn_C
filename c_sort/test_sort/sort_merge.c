#include <stdio.h>
#include <stdlib.h>

// 合并有序数组
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

// 递归归并
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
