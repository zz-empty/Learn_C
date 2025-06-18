#include "minheap.h"
#include <string.h>

// 创建最小堆
MinHeap* createMinHeap() {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->words = (Word**)malloc(HEAP_CAPACITY * sizeof(char*));
    heap->size = 0;
    return heap;
}

// 交换堆的两个元素
void swap(MinHeap *heap, int i, int j) {
    Word *temp = heap->words[i];
    heap->words[i] = heap->words[j];
    heap->words[j] = temp;
}

// 维护堆的性质（上浮）
void heapifUp(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->words[index]->value >= heap->words[parent]->value) break;
        swap(heap, index, parent);
        index = parent;
    }
}

// 维护堆的性质（下沉）
void heapifDown(MinHeap *heap, int index) {
    int minIndex = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->words[left]->value < heap->words[minIndex]->value) {
        minIndex = left;
    }
    if (right < heap->size && heap->words[right]->value < heap->words[minIndex]->value) {
        minIndex = right;
    }
    if (minIndex != index) {
        swap(heap, index, minIndex);
        heapifDown(heap, minIndex);
    }
}

void buildHeap(MinHeap *heap) {
    for (int i = (heap->size - 1) / 2; i >= 0; --i) {
        heapifDown(heap, i);
    }
}

// 插入元素到堆中
int push(MinHeap *heap, char *key, int value) {
    // 检查重复键
    for (int i = 0; i < heap->size; ++i) {
        if (strcmp(heap->words[i]->key, key) == 0) {
            // 释放旧节点
            free(heap->words[i]->key);
            free(heap->words[i]);

            // 用最后一个节点覆盖当前位置
            heap->words[i] = heap->words[heap->size - 1];
            heap->size--;

            // 重建堆的性质
            buildHeap(heap);
            break;
        }
    }

    // 正常加入逻辑
    if (heap->size >= HEAP_CAPACITY) {
        if (value <= heap->words[0]->value) return 0;

        // 替换堆顶
        free(heap->words[0]->key);
        free(heap->words[0]);

        Word *newWord = (Word*)malloc(sizeof(Word));
        newWord->key = strdup(key);
        newWord->value = value;

        heapifDown(heap, 0);
        return 1;
    }

    // 插入新节点
    Word *newWord = (Word*)malloc(sizeof(Word));
    newWord->key = strdup(key);
    newWord->value = value;

    heap->words[heap->size] = newWord;
    heapifUp(heap, heap->size);
    heap->size++;
    return 1;
}

// 释放堆内存
void freeMinHeap(MinHeap *heap) {
    for (int i = 0; i < heap->size; ++i) {
        free(heap->words[i]->key);
        free(heap->words[i]);
    }
    free(heap->words);
    free(heap);
}
