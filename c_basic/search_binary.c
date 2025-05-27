#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
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

// 二分查找，返回查找结果的下标，如果没找到返回-1
// 确保数据是升序排列的
int binary_search(int *arr, int len, int target) {
    int left = 0;
    int right = len - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (target > arr[mid]) {
            left = mid + 1;
        } else if (target < arr[mid]) {
            right = mid - 1;
        } else {
            printf("找到了，%d下标是%d\n", target, mid);
            return mid;
        }
    }
    printf("没有在数组中找到%d\n", target);
    return -1;
}

// qsort的参数
int compare(const void *p1, const void *p2) {
    int *l = (int*)p1;
    int *r = (int*)p2;
    return *l - *r;
}

int main() {
    srand(time(NULL));
    int *arr = random_arr(SIZE, MAX);
    print_arr(arr, SIZE);
    qsort(arr, SIZE, sizeof(int), compare);
    print_arr(arr, SIZE);

    // 二分查找
    int num = rand() % MAX;
    printf("查找值：%d\n", num);
    binary_search(arr, SIZE, num);

    free(arr);
}
