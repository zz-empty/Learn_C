#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    printf("请输入一个整数: ");
    scanf("%d", &n);

    int matrix[n][n];
    memset(matrix, 0, sizeof(int) * n * n);

    // 方向数组 , 右 下 左 上
    int directions[4][2] = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0}
    };

    int dir = 0;    // 当前方向索引
    int row = 0, col = 0;
    matrix[row][col] = 1;

    for (int num = 2; num <= n * n; ++num) {
        // 尝试沿当前方向移动   
        int next_row = row + directions[dir][0];
        int next_col = col + directions[dir][1];

        // 检查是否越界或已填充
        if (next_row >= 0 && next_row < n && next_col >= 0 && next_col < n &&
                matrix[next_row][next_col] == 0) {
            printf("继续, ");
            row = next_row;
            col = next_col;
        } else {
            // 顺时针转向
            printf("转向, ");
            dir = (dir + 1) % 4;
            row += directions[dir][0];
            col += directions[dir][1];
        }

        matrix[row][col] = num;
        printf("[%d][%d] = %d\n", row, col, num);
    }

    // 打印矩阵
    printf("\n蛇形矩阵：\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d", matrix[i][j]); 
        }
        printf("\n");
    }

    return 0;
}
