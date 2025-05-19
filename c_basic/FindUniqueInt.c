#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE_1 51
#define MAX_SIZE_2 12
#define MAX_SIZE_3 13
#define M 100

void printIntArr(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%-3d", arr[i]);
    }
    printf("\n");
}

void test()
{
    //101个数，其中存在50对重复数，1个独特数，求独特数
    int num[MAX_SIZE_1] = {0};
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE_1 / 2; ++i) {
        num[i] = num[MAX_SIZE_1 - 1 - i] = rand() % M;
    }
    num[MAX_SIZE_1 / 2] = rand() % M;

    printIntArr(num, MAX_SIZE_1);

    int result = 0;
    for (int i = 0; i < MAX_SIZE_1; ++i) {
        result ^= num[i];
    }

    printf("独特数是：%d\n", result);
}

void test2()
{
    //102个数，其中存在50对重复数，2个互不相同的独特数，求这两个独特数（提示想方设法转换成a情况）
    int num[MAX_SIZE_2] = {0};
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE_2 - 1 / 2; ++i) {
        num[i] = num[MAX_SIZE_2 - 2 - i] = rand() % M;
    }
    num[(MAX_SIZE_2 - 1) / 2] = rand() % M;
    num[MAX_SIZE_2 - 1] = num[(MAX_SIZE_2 - 1) / 2] + rand() % MAX_SIZE_2 + 1;
    printIntArr(num, MAX_SIZE_2);
    
    //利用分割器
    int xor_num = 0;
    for (int i = 0; i < MAX_SIZE_2; ++i) {
        xor_num ^= num[i];
    }
    int mask = xor_num & -xor_num;

    //分成两组，得出两个数
    int a = 0, b = 0;
    for (int i = 0; i < MAX_SIZE_2; ++i) {
        if (num[i] & mask) {
            a ^= num[i];
        } else {
            b ^= num[i];
        }
    }

    printf("两个独特数是：%d, %d\n", a, b);
}

//处理非零异或和的情况
void find_with_xor(int arr[], int size, int *a, int *b, int *c) {
    int xor_all = 0;
    for (int i = 0; i < size; ++i) xor_all ^= arr[i];

    //得到一个分割器
    int mark = xor_all & -xor_all;

    //分离第一个独特数a
    for (int i = 0; i < size; ++i) {
        if (arr[i] & mark) *a ^= arr[i];
    }

    //计算剩余两个数的异或
    int xor_ba = xor_all ^ *a;
    int mark2 = xor_ba & -xor_ba;

    //分离b和c
    *b = *c = 0;
    for (int i = 0; i < size; ++i) {
        if (!(arr[i] & mark)) {  //对剩余元素处理
            if (arr[i] & mark2) *b ^= arr[i];
            else *c ^= arr[i];
        }
    }
}

//处理异或和为零的情况
void find_with_hash(int arr[], int size, int *a, int *b, int *c) {
    int max_num = arr[0];
    for (int i = 0; i < size; ++i) {
        if (arr[i] > max_num) max_num = arr[i];
    }

    //建立一个hash表
    int *hash = (int*)calloc(max_num + 1, sizeof(int));
    //初始化hash表
    for (int i = 0; i < size; ++i) {
        hash[arr[i]]++;
    }

    //找到三个为1的数
    int index = 0;
    for (int i = 0; i < max_num + 1; ++i) {
        if (hash[i] == 1) {
            if (index == 0) *a = hash[i];
            else if (index == 1) *b = hash[i];
            else if (index == 2) *c = hash[i];
            index++;
        }
    }

    free(hash);
    hash = NULL;
}

void find_unique(int arr[], int size, int *a, int *b, int *c) {
    //先求数组的异或和
    int xor_all = 0;
    for (int i = 0; i < size; ++i) {
        xor_all ^= arr[i];
    }
    printf("xor_all:%d\n", xor_all);
    
    if (xor_all) {
        find_with_xor(arr, size, a, b, c);
    } else {
        find_with_hash(arr, size, a, b, c);
    }
}

int main()
{
    //103个数，其中存在50对重复数，3个互不相同的独特数，求这三个独特数
    int num[MAX_SIZE_3] = {0};
    srand(time(NULL));
    int len = MAX_SIZE_3 - 2;
    for (int i = 0; i < len / 2; ++i) {
        num[i] = num[len - 1 - i] = rand() % M;
    }
    num[len / 2] = rand() % M;
    num[MAX_SIZE_3 - 2] = num[len / 2] + 1;
    num[MAX_SIZE_3 - 1] = num[len / 2] + 2;
    printIntArr(num, MAX_SIZE_3);

    int a, b, c;
    find_unique(num, MAX_SIZE_3, &a, &b, &c); 
    printf("a:%d, b:%d, c:%d\n", a, b, c);
}
