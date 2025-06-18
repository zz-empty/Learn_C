#include "hashmap.h"
#include "minheap.h"
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 1024

void format_allchar(char *line);
void store_words(HashMap *map, MinHeap *heap, const char *line);

int main(int argc, char *argv[]) {
    if (2 != argc) {
        fprintf(stderr, "args error\n");
        return -1;
    }

    FILE *fp_read = (FILE*)fopen(argv[1], "r");
    HashMap *map = createHashMap();// 用哈希表存储所有单词
    MinHeap *heap = createMinHeap();// 用最小堆存储词频前10的单词

    // 按行处理数据
    char line[LINE_SIZE] = "";
    int n = 1;
    while (fgets(line, LINE_SIZE, fp_read)) {
        if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
        format_allchar(line);   // 将非字母换成空格，大写变小写
        /* puts(line); */
        store_words(map, heap, line); // 剥离出line中的每个单词, 存入哈希表&最小堆

        // 打印最小堆
        /* printf("--------------------------\n"); */
        /* for (int i = 0; i < heap->size; ++i) { */
        /*     printf("%d(%s)   ", heap->words[i]->value, heap->words[i]->key); */
        /* } */
        /* printf("\n"); */

        // 控制打印的行数
        /* if (n++ >= 10) break; */ 
    }

    // 打印词频前10的单词
    printf("--------------------------\n");
    for (int i = 0; i < heap->size; ++i) {
        printf("%d\t%s\n", heap->words[i]->value, heap->words[i]->key);
    }

    // 释放哈希表和最小堆
    freeHashMap(map);
    freeMinHeap(heap);
    fclose(fp_read);
    return 0;
}
