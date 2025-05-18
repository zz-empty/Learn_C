#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1001
#define SWAP(a,b) {int tmp = a; a = b; b = tmp;}

int main() {
    //生成一个数量为1001的数组，只有一个数重复
    srand(time(NULL));
    int arr[MAX];
    for (int i = 1; i <= 1000; ++i) {
        arr[i] = i;
    }
    arr[0] = rand() % 1001;
    printf("重复的数：%d\n", arr[0]);

    //打乱数组的顺序
    for (int i = 0; i < 1000; ++i) {
        int j = rand() % (i+1);
        SWAP(arr[i], arr[j]);
    }

    //求出1~1000的和
    long sum = 1000 * 1001 / 2;
    for (int i = 0; i < 1001; ++i) {
        sum -= arr[i];
    }
    printf("找出的数是：%ld\n", -sum);

    return 0;
}
