// 冒泡排序
void sort_bubble(int *arr, int len) {
    // 升序，就每次去掉最后的最大值
    for (int i = len - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
