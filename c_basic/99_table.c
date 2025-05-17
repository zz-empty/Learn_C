#include <stdio.h>

int main()
{
    //外层控制行、内层控制列
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf("%dx%d=%-3d", j, i, j * i);
        }
        printf("\n");
    }
}
