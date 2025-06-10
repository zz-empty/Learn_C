#ifndef __MINHEAP_H__
#define __MINHEAP_H__
#include <stdlib.h>

#define HEAP_CAPACITY 10    // 最小堆容量
typedef struct {
    char *key;
    int value;
} Word;
typedef struct {
    Word **words;
    int size;
} MinHeap;


MinHeap* createMinHeap();
void swap(MinHeap *heap, int i, int j);
void heapifUp(MinHeap *heap, int index);
void heapifDown(MinHeap *heap, int index);
void buildHeap(MinHeap *heap);
int push(MinHeap *heap, char *key, int value);
void freeMinHeap(MinHeap *heap);

#endif
