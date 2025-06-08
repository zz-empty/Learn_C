#define SWAP_INT(a, b) {int tmp = a; a = b; b = tmp;}

// 从pos位置开始向下调整大根堆
void adjustMaxHeap(int *arr, int pos, int len) {
    // pos是父结点下标, 确保pos位置的结点大于所有下属结点
    // 先找出最大的孩子下标
    // 再与父结点比较。如果比父结点大，就交换。交换后如果孩子结点存在，就继续向下比较。
    int dad = pos;  // 父结点下标
    int son = 2 * pos + 1;  // 左孩子下标
    
    while (son < len) {
        if (son + 1 < len && arr[son + 1] > arr[son]) {
            son = son + 1;
        }

        if (arr[son] > arr[dad]) {      // 孩子节点 > 父节点, 交换并向下循环
            SWAP_INT(arr[son], arr[dad]);
            dad = son;
            son = 2 * dad + 1;
        } else {    // 父结点 > 孩子结点，退出
            break; 
        }
    }
}

// 堆排序
void heap_sort(int *arr, int len) {
    // 最后一个父结点编号:len / 2, 下标: len / 2 - 1

    // 从最后一个父结点开始调整大根堆，直到第一个结点
    for (int i = len / 2 - 1; i >= 0; --i) {
        adjustMaxHeap(arr, i, len);
    }
    // 交换第一个结点和最后一个结点，减少堆的规模
    SWAP_INT(arr[0], arr[len - 1]);
    // 对剩余元素从头建堆，建完后，交换堆顶和最后元素，缩小堆的规模。重复直到堆的规模为2
    for (int i = len - 1; i > 1; --i) {
        adjustMaxHeap(arr, 0, i);
        SWAP_INT(arr[0], arr[i - 1]);
    }
}

