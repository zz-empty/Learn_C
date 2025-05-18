#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 100
#define N 10
#define M 50
#define SWAP(a, b) {int tmp = a; a = b; b = tmp;}

void print_array_int(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%3d", arr[i]);
    } 
    printf("\n");
}

void selectSort(int *arr, int len) {
    for (int i = len - 1; i > 0; --i) {
        //每次找出最大值下标，与arr[i]交换
        int max = 0;
        for (int j = 1; j <= i; ++j) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }
        SWAP(arr[i], arr[max]);
    }
}

int main()
{
    //在两个有序的数组中找到公共元素
    /* int arr1[] = {3, 4, 7, 9, 10, 14, 38, 39, 45}; */
    /* int arr2[] = {1, 4, 8, 9, 17, 34, 38, 49, 45, 57, 68}; */

    //生成两个随机数组, 并初始化
    srand(time(NULL)); 
    int *arr1 = (int*)malloc(N * sizeof(int));
    int *arr2 = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i) {
        arr1[i] = rand() % M;
        arr2[i] = rand() % M;
    }

    //对两个数组升序排列
    selectSort(arr1, N);
    selectSort(arr2, N);

    //显示两个数组
    print_array_int(arr1, N);
    print_array_int(arr2, N);

    //定义结果数组，存储相同元素
    int result[MAX_LEN] = {0};
    int size = 0;


    //用两个指针遍历数组，如果相同就加入结果数组
    int i = 0, j = 0;
    while (i < N && j < N) {
        if (arr1[i] < arr2[j]) {
            //前者小，往后跳
            ++i;
        } else if (arr1[i] > arr2[j]) {
            //后者小，往后跳
            ++j;
        } else {
            //相同元素，加入结果
            result[size++] = arr1[i];
            ++i;
            ++j;
        }
    } 

    printf("两个数组的相同元素：");
    print_array_int(result, size);
    return 0;
}
