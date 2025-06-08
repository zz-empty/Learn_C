#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
    int *date;
    int size;
    int capacity;
}Vec_t, *pVec_t;

// 初始化一个可变数组容器
void init(pVec_t pV, int capacity) {
    pV->date = (int*)malloc(sizeof(int) * capacity);
    memset(pV->date, 0, sizeof(Vec_t));
    pV->size = 0;
    pV->capacity = capacity;
}

void push_back(pVec_t pV, int num) {
    if (pV->size >= pV->capacity) {
        // 容量不足, 扩充2倍
        Vec_t tmp = *pV;
        pV->capacity = 2 * pV->capacity;
        pV->date = (int*)malloc(sizeof(int) * pV->capacity);    // 扩充
        memset(pV->date, 0, sizeof(int) * pV->capacity);  //初始化新数组
        memcpy(pV->date, tmp.date, tmp.size * sizeof(int));     // 拷贝旧数据
        free(tmp.date); // 释放旧数组
        tmp.date = NULL;
    }
    pV->date[pV->size++] = num;
    printf("num:%d, size:%d\n", num, pV->size);
}

void print_vector(pVec_t pV) {
    printf("vec_date: ");
    if (pV->size) {
        for (int i = 0; i < pV->size; ++i) {
            printf("%-5d", pV->date[i]);
        }
    }
    printf("\n");
    printf("vec.size:%d, vec.capacity:%d\n\n", pV->size, pV->capacity);
}

// 释放可变数组
void desctory(pVec_t pVec) {
    if (pVec->date != NULL) {
        free(pVec->date);
        memset(pVec, 0, sizeof(Vec_t));
    }
}

int main()
{
    // 利用动态数组，实现类似于C++ vector的push_back功能
    
    // 申请一个可变数组
    Vec_t vec;
    init(&vec, 2);
    print_vector(&vec);

    // 插入元素
    push_back(&vec, 2);
    push_back(&vec, 4);
    print_vector(&vec);
    push_back(&vec, 7);
    push_back(&vec, 9);
    print_vector(&vec);
    push_back(&vec, 5);
    print_vector(&vec);

    // 释放可变数组
    desctory(&vec);
}
