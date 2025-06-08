#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void sort_count(int *arr, int len) {
    int *count = (int*)malloc(sizeof(int) * MAX);
    memset(count, 0, sizeof(int) * MAX);
    if (!count) {
        fprintf(stderr, "内存分配失败\n");
        return;
    }

    // 初始化计数数组
    for (int i = 0; i < len; ++i) {
        count[arr[i]]++;
    }

    // 根据count数组，重置arr
    int idx = 0;
    for (int i = 0; i < MAX; ++i) {
        while (count[i]--)  arr[idx++] = i;
    } 
}
