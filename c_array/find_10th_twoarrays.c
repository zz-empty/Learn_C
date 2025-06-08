#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MAX 100
#define SWAP_INT(a, b) {int tmp = a; a = b; b = tmp;}

// 生成一个随机数组
int* random_arr(int len, int max, int random) {
    srand(time(NULL) * random);
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

// 合并打印两个数组
void print_and(int *arr1, int *arr2) {
    // 合并打印
    int i = 0, j = 0;
    while (i < SIZE && j < SIZE) {
        if (arr1[i] <= arr2[j]) {
            printf("%3d", arr1[i]);
            ++i;
        } else {
            printf("%3d", arr2[j]);
            ++j;
        }
    }
    while (i < SIZE) {
        printf("%3d", arr1[i]);
        ++i;
    }
    while (j < SIZE) {
        printf("%3d", arr2[j]);
        ++j;
    }
    printf("\n");
}

int compare(const void *p1, const void *p2) {
    int *l = (int*)p1;
    int *r = (int*)p2;
    return *l - *r;
}

int find_10th(int *arr1, int *arr2, int k) {
    int index1 = 0;
    int index2 = 0;
    int cnt = 0;

    for (int n = k; n > 1; n -= n / 2) {
        int i = index1 + n / 2 - 1;
        int j = index2 + n / 2 - 1;
        printf("n = %d, k = %d\t arr1[%d] = %d, arr2[%d] = %d\n", n, n / 2, i, arr1[i], j, arr2[j]);
        if (arr1[i] < arr2[j]) {
            index1 += n / 2;
            cnt += n / 2;
        } else {
            index2 += n / 2;
            cnt += n / 2;
        }
    }
    printf("cnt = %d\n", cnt);

    // 前面都是干掉小的，最后一个留下最小的
    return arr1[index1] < arr2[index2] ? arr1[index1] : arr2[index2];
}

int main() {
    int *arr1 = random_arr(SIZE, MAX, 9);
    int *arr2 = random_arr(SIZE, MAX, 19);


    // 排序
    qsort(arr1, SIZE, sizeof(int), compare);
    qsort(arr2, SIZE, sizeof(int), compare);

    print_arr(arr1, SIZE);
    print_arr(arr2, SIZE);

    // 合并打印
    print_and(arr1, arr2);

    int k = 10;
    printf("第%d名：%d\n", k, find_10th(arr1, arr2, k));
}

