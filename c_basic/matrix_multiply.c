#include <stdio.h>

int main()
{
    int row1, col1;
    int row2, col2;
    
    // 输入第一个矩阵
    printf("请输入第一个矩阵的行数和列数：");
    scanf("%d%d", &row1, &col1);
    int matrix_a[row1][col1];

    printf("请输入第一个矩阵的元素：");
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1; ++j) {
            scanf("%d", &matrix_a[i][j]); 
        }
    }

    // 输入第一个矩阵
    printf("请输入第二个矩阵的行数和列数：");
    scanf("%d%d", &row2, &col2);
    int matrix_b[row2][col2];

    printf("请输入第二个矩阵的元素：");
    for (int i = 0; i < row2; ++i) {
        for (int j = 0; j < col2; ++j) {
            scanf("%d", &matrix_b[i][j]); 
        }
    }


    // 计算矩阵乘积
    int result[row1][col2];
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < col1; ++k) {
                result[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }

    // 打印结果
    printf("\n乘积矩阵；%dx%d\n", row1, col2);
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            printf("%6d", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
