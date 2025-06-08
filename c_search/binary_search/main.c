#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MAX 100

int* random_arr(int len, int max);
void print_arr(int *arr, int len);
int binary_search(int *arr, int len, int target);

// qsort的参数
int compare(const void *p1, const void *p2) {
    int *l = (int*)p1;
    int *r = (int*)p2;
    return *l - *r;
}

int main() {
    // 生成一个随机数组，然后排序
    int *arr = random_arr(SIZE, MAX);
    print_arr(arr, SIZE);
    qsort(arr, SIZE, sizeof(int), compare);
    print_arr(arr, SIZE);

    // 二分查找
    srand(time(NULL));
    int num = rand() % MAX;
    printf("查找值：%d\n", num);
    binary_search(arr, SIZE, num);

    free(arr);
}
