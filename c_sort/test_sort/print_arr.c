#include <stdio.h>
// 打印int数组
void print_arr(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%3d", arr[i]);
    }
    printf("\n");
}
