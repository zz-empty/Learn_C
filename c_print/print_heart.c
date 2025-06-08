#include <stdio.h>

int main()
{
    //用星号打印心形
    int n = 8;  //最大行

    //打印上半部分
    int line_up = n % 2 == 1 ? n / 2 + 1 : n / 2;
    //上边界是2，下边界是总行数-1
    for (int i = 2; i < line_up; ++i) {
        //打印前导空格
        for (int j = line_up - i; j > 0; --j) {
            printf(" ");
        }
        //打印星号
        for (int j = 1; j <= i; ++j) {
            printf("*");
            if (j != i) {
                printf(" ");
            }
        }
        //打印中间空格
        if (n % 2) {
            //如果最大行是奇数，打印中间空格时，就要比前导空格少一行
            for (int j = 2 * (line_up - i) - 1; j > 0; --j) {
                printf(" ");
            }
        }
        else {
            //如果最大行是偶数，就打印两倍的前导空格，再多打一个就来对齐
            for (int j = 2 * (line_up - i); j >= 0; --j) {
                printf(" ");
            }
        }

        //打印星号
        for (int j = 1; j <= i; ++j) {
            printf("*");
            if (j != i) {
                printf(" ");
            }
        }
        
        printf("\n");
    }

    //打印下半部分
    for (int i = 1; i <= n; ++i) {
        //打印空格
        for (int j = 1; j < i; ++j) {
            printf(" ");
        }
        //打印星号
        for (int j = n; j >= i; --j) {
            printf("*");
            //每打印一个星号，就打印一个空格，直到最后一个星号
            if (j != i) {
                printf(" ");
            }
        }
        printf("\n");
    } 
    return 0;
}
