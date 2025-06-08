#include <stdio.h>

int count_grid_paths(int m, int n) {
    if (m == 0 || n == 0) return 1;
    if (m < 0 || n < 0) return 0;
    return count_grid_paths(m - 1, n) + count_grid_paths(m, n - 1);
}

int main() {
    int m, n;
    printf("输入(m, n): ");
    scanf("%d%d", &m, &n);

    int paths = count_grid_paths(m, n); 
    printf("从(0,0)走到(%d,%d)有%d种路径\n", m, n, paths);
    return 0;
}
