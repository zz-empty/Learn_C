#include <stdio.h>

int main()
{
    //打印菱形
    int n = 5;

    //先打印上半部分
    for (int i = 1; i <= n; ++i) {
        //打印空格
        for (int j = n - i; j > 0; --j) printf(" ");

        //打印星号
        for (int j = 1; j <= i; ++j) {
            printf("*");
            if (j != 2 * i - 1) printf(" ");
        }

        printf("\n");
    }

    //打印下半部分
    for (int i = n - 1; i > 0; --i) {
        //打印空格
        for (int j = n - i; j > 0; --j) printf(" ");
        
        //打印星号
        for (int j = 1; j <= i; ++j) {
            printf("*");
            if (j != 2 * i - 1) printf(" ");
        }

        printf("\n");
    }
}
