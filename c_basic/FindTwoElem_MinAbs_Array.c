#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE 10
#define M 100
#define SWAP(a, b) {int tmp = a; a = b; b = tmp;}

//打印数组
void print_array_int(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%3d", arr[i]);
    } 
    printf("\n");
}

//选择排序排序数组
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

//生成一个动态分配的数组
int *create_random_array(int len) {
    //生成一个随机数组
    srand(time(NULL)); 
    int *arr = (int*)malloc(len * sizeof(int));
    //初始化数组
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % M;
    }
    return arr;
}

//释放动态分配的数组
void destory_random_array(int *arr) {
    free(arr);
    arr = NULL;
}

//得到两个整数的绝对值
int abs_int(int e1, int e2) {
    return e1 - e2 > 0 ? e1 - e2 : e2 - e1;
}

//对有序数组去重
int uniqueArray(int *arr, int len) {
    int size = 0;
    for (int i = 1; i < len; ++i) {
       if (arr[size] != arr[i]) {
           arr[++size] = arr[i];
       } 
    }
    return size;
}

int main()
{
    //得到一个随机数组
    int *arr = create_random_array(ARRAY_SIZE);
    print_array_int(arr, ARRAY_SIZE);

    //找出两个元素，它们的绝对值是最小的
    //先排序，遍历每两个元素之间的绝对值
    selectSort(arr, ARRAY_SIZE);        //排序
    int arr_size = uniqueArray(arr, ARRAY_SIZE);    //去重
    print_array_int(arr, arr_size);     //显示数组
    int min_abs = abs_int(arr[0], arr[1]);  //初始化最小值 
    int left = 0, right = 1;    //记录abs最小的两个元素下标
    for (int i = 1; i < arr_size - 1; ++i) {
        if (min_abs > abs_int(arr[i], arr[i + 1])) {
            min_abs = abs_int(arr[i], arr[i + 1]);         
            left = i;
            right = i + 1;
        }
    }

    //打印这两个元素
    printf("a:%d, b:%d\n", arr[left], arr[right]);

    //释放随机数组
    destory_random_array(arr);
    return 0;
}
