#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000
/* #define SIZE 300000000 */
#define MAX 100

void sort_bubble(int *arr, int len);
void sort_select(int *arr, int len);
void sort_insert(int *arr, int len);
void sort_shell(int *arr, int len);

int* random_arr(int len, int max);
void print_arr(int *arr, int len);

// 计算排序时间
int time_sort(int *arr, int len) {
    time_t begin = time(NULL);
    sort_shell(arr, len);
    /* sort_bubble(arr, len); */
    /* sort_select(arr, len); */
    /* sort_insert(arr, len); */

    /* qsort(arr, len, sizeof(int), compare); */
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

    /* // 堆排序 */
    /* heap_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    /* // 归并排序 */
    /* merge_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    /* // 基数排序 */
    /* count_sort(arr, SIZE); */
    /* print_arr(arr, SIZE); */

    // 计算排序大数组的时间
    printf("排序%d个数，total_time: %ds\n", SIZE, time_sort(arr, SIZE));

    free(arr);
    return 0;
}
