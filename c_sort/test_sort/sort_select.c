// 选择排序
void sort_select(int *arr, int len) {
    // 升序， 每次去掉最后的最大值
    // 每次选出一个最大值的下标，与最后一位交换
    for (int i = len - 1; i > 0; --i) {
        int max = i;
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[max]) max = j;
        }
        int tmp = arr[max];
        arr[max] = arr[i];
        arr[i] = tmp;
    }
}
