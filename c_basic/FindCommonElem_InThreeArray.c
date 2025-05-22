#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 100
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

int find_commonElem_arrays(int *arr1, int len1, int *arr2, int len2, int *result) {
    //用两个指针遍历数组，如果相同就加入结果数组
    int size = 0;
    int i = 0, j = 0;

    while (i < len1 && j < len2) {
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
    return size;
}

int main()
{
    //在三个有序的数组中找到公共元素

    //生成三个随机数组, 并初始化
    srand(time(NULL)); 
    int *arr1 = (int*)malloc(N * sizeof(int));
    int *arr2 = (int*)malloc(N * sizeof(int));
    int *arr3 = (int*)malloc(N * sizeof(int));
 
    for (int i = 0; i < N; ++i) {
        arr1[i] = rand() % M;
        arr2[i] = rand() % M;
        arr3[i] = rand() % M;
    }

    //对两个数组升序排列
    selectSort(arr1, N);
    selectSort(arr2, N);
    selectSort(arr3, N);

    //显示两个数组
    print_array_int(arr1, N);
    print_array_int(arr2, N);
    print_array_int(arr3, N);

    //定义结果数组，存储相同元素
    int result[MAX_LEN] = {0};
    int size = 0;

    //临时数组，存储临时数据
    int tmp[MAX_LEN] = {0};
    int size_tmp = 0;

    //使用两次函数找到三个有序数组的公共元素
    size_tmp = find_commonElem_arrays(arr1, N, arr2, N, tmp);
    size = find_commonElem_arrays(arr3, N, tmp, size_tmp, result);

    printf("两个数组的相同元素：");
    print_array_int(result, size);

    //释放动态申请的数组
    free(arr1);
    free(arr2);
    free(arr3);
    return 0;
}
