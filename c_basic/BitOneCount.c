#include <stdio.h>

int main()
{
    //统计一个整型数字的内存内容中有多少个1（注意正负数都要计算）
    int num;
    printf("请输入一个整数：");
    scanf("%d", &num);

    unsigned int n = (unsigned int)num;
    size_t cnt = 0;
    while (n) {
        if (n & 1) cnt++;
        n >>= 1;
    }

    printf("%d的内存里有%ld个1\n", num, cnt);
}
