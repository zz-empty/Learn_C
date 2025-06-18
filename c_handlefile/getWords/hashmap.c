#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// 哈希函数（简单的字符串哈希）
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % HASH_TABLE_SIZE;
}

// 创建哈希表
HashMap* createHashMap() {
    HashMap *map = (HashMap*)malloc(sizeof(HashMap));
    map->buckets = (HashNode**)calloc(HASH_TABLE_SIZE, sizeof(HashNode*));
    return map;
}

// 插入/更新键值对
void put(HashMap *map, const char *key, int value) {
    unsigned int index = hash(key);
    HashNode *node = map->buckets[index];

    // 查找是否已经存在该键, 如果已经存在, value++;
    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value++;
            return;
        }
        node = node->next;
    }
    
    // 创建新节点
    HashNode *newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = strdup(key);
    newNode->value = value;
    // 挂到哈希表的某个链表的表头
    newNode->next = map->buckets[index];
    map->buckets[index] = newNode;
}

// 获取键的值
int get(HashMap *map, const char *key) {
    unsigned int index = hash(key);
    HashNode *cur = map->buckets[index];
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            return cur->value;
        }
        cur = cur->next;
    }
    return 0;   // 未找到返回0
}

// 释放哈希表
void freeHashMap(HashMap *map) {
    // 先释放每个节点的链表
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        HashNode *cur = map->buckets[i];
        while (cur) {
            HashNode *tmp = cur;
            cur = cur->next;
            free(tmp->key);
            free(tmp);
        }
    }

    // 释放哈希表
    free(map->buckets);
    free(map);
}
