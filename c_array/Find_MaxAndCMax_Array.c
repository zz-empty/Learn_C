#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 15
#define M 30
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
    //找一个数组的最大值和次大值
    srand(time(NULL)); 
    int *arr = (int*)malloc(N * sizeof(int));
    //初始化数组
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % M;
    }
    selectSort(arr, N);
    int size = uniqueArray(arr, N);
    print_array_int(arr, size);
    printf("size = %d\n", size);

    //分别找出最大值和次大值
    int max = 0;    //max表示最大值下标
    int cmax = 0;   //cmax表示次大值下标
    for (int i = 0; i < size; ++i) {
        if (arr[i] > arr[max]) {
            max = i;
        }   
    }

    for (int i = 0; i < size; ++i) {
        if (i != max && arr[i] > arr[cmax]) {
            cmax = i;
        }
    }

    //显示最大值和次大值
    printf("max:%-3d, cmax:%-3d\n", arr[max], arr[cmax]);

    //释放动态分配的内存
    free(arr);
    arr = NULL;
}
