#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#define HASH_TABLE_SIZE 1024    // 哈希表大小


// 单词结构，用哈希表存储单词, 用链表法解决哈希冲突
typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode, *pHashNode;

// 哈希表
typedef struct {
    pHashNode *buckets;
} HashMap;

// 哈希函数
unsigned int hash(const char* key);

// 创建哈希表
HashMap* createHashMap();

// 插入/更新键值对
void put(HashMap *map, const char *key, int value);

// 获取键的值
int get(HashMap *map, const char *key);

// 释放哈希表
void freeHashMap(HashMap *map);


#endif
