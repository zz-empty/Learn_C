#include <stdlib.h>
#include <time.h>

// 生成一个随机数组
int* random_arr(int len, int max) {
    srand(time(NULL));
    int *arr = (int*)malloc(len * sizeof(int));

    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % max;
    }
    return arr;
}
