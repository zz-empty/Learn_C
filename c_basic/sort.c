#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* #define SIZE 1000000 */
#define SIZE 300000000
#define MAX 100

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

// 冒泡排序
void bubble_sort(int *arr, int len) {
    // 升序，就每次去掉最后的最大值
    for (int i = len - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// 选择排序
void select_sort(int *arr, int len) {
    // 升序， 每次去掉最后的最大值
    // 每次选出一个最大值的下标，与最后一位交换
    for (int i = len - 1; i > 0; --i) {
        int max = i;
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[max]) max = j;
        }
        int tmp = arr[max];
        arr[max] = arr[i];
        arr[i] = tmp;
    }
}

// 插入排序
void insert_sort(int *arr, int len) {
    // 将后面元素挨个插入当前数组，从后向前比较
    // 保存来牌的值
    // 后移所有大于来牌的元素
    // 插入找到的位置
    for (int i = 1; i < len; ++i) {
        int insertVal = arr[i];   // 保存来牌

        // 找插入位置
        int j = i - 1;
        for (; j >= 0 && arr[j] > insertVal; --j) {
            arr[j + 1] = arr[j];
        }
       
        arr[j + 1] = insertVal;
    }
}

// 希尔排序
void shell_sort(int *arr, int len) {
    // 缩小增量
    for (int gap = len >> 1; gap > 0; gap >>= 1) {
        for (int i = gap; i < len; ++i) {   // 来牌
            int insertVal = arr[i];

            // 找插入位置
            int j = i - gap;
            for (; j >= 0 && arr[j] > insertVal; j -= gap) {
                arr[j + gap] = arr[j];
            }

            arr[j + gap] = insertVal;
        } 
    }
}

int sort_time(int *arr, int len) {
    time_t begin = time(NULL);
    shell_sort(arr, len);
    /* bubble_sort(arr, len); */
    /* select_sort(arr, len); */
    /* insert_sort(arr, len); */
    time_t end = time(NULL);
    return end - begin;
}

int main() {
    int *arr = random_arr(SIZE, MAX);
    /* print_arr(arr, SIZE); */

    /* // 冒泡排序 */ /* printf("冒泡排序："); */
    /* bubble_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    /* // 选择排序 */
    /* printf("选择排序："); */
    /* select_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    /* // 插入排序 */
    /* printf("插入排序："); */
    /* insert_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    /* // 希尔排序 */
    /* printf("希尔排序："); */
    /* shell_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    // 计算排序大数组的时间
    printf("排序%d个数，total_time: %ds\n", SIZE, sort_time(arr, SIZE));

    free(arr);
    return 0;
}
