// 插入排序
void sort_insert(int *arr, int len) {
    // 将后面元素挨个插入当前数组，从后向前比较
    // 保存来牌的值
    // 后移所有大于来牌的元素
    // 插入找到的位置
    for (int i = 1; i < len; ++i) {
        int insertVal = arr[i];   // 保存来牌

        // 找插入位置
        int j = i - 1;
        for (; j >= 0 && arr[j] > insertVal; --j) {
            arr[j + 1] = arr[j];
        }
       
        arr[j + 1] = insertVal;
    }
}
