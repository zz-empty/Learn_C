#include <stdio.h>

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
