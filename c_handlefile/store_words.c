#include "minheap.h"
#include "hashmap.h"
#include <stdio.h>
#include <string.h>

#define WORD_SIZE 128

void store_words(HashMap *map, MinHeap *heap, const char *line) {
    char word[WORD_SIZE] = "";
    int index = 0;
    int len = strlen(line);
    for (int i = 0; i < len; ++i) {
        if (line[i] != ' ') {
            word[index++] = line[i];
        } else {
            // 如果word的长度大于1，表示一个单词
            word[index] = '\0';
            if (strlen(word) > 1) {
                // 存入哈希表
                put(map, word, 1);                
                /* printf("%d\t%s\n", get(map, word), word); */
                // 存入最小堆
                push(heap, word, get(map, word));
            }
            // 重置word
            index = 0;
            word[0] = '\0';
        }
    }
}
