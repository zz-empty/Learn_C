#define SWAP_INT(a, b) {int tmp = a; a = b; b = tmp;}

// 将数组根据pivot划分成左边小于pivot，右边大于等于pivot
int patition(int *arr, int left, int right) {
    int i, j;
    for (i = left, j = left; i < right; ++i) {
        if (arr[i] < arr[right]) {
            SWAP_INT(arr[i], arr[j]);
            ++j;
        } 
    }
    SWAP_INT(arr[right], arr[j]);
    return j;
}

// 快速排序，左闭右闭区间
void quick_sort(int *arr, int left, int right) {
    if (left < right) {
        int pivot = patition(arr, left, right);
        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot + 1, right);
    } 
}
