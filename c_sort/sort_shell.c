// 希尔排序
void sort_shell(int *arr, int len) {
    // 缩小增量
    for (int gap = len >> 1; gap > 0; gap >>= 1) {
        for (int i = gap; i < len; ++i) {   // 来牌
            int insertVal = arr[i];

            // 找插入位置
            int j = i - gap;
            for (; j >= 0 && arr[j] > insertVal; j -= gap) {
                arr[j + gap] = arr[j];
            }

            arr[j + gap] = insertVal;
        } 
    }
}
