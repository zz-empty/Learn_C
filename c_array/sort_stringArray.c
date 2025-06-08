#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
#define STR_SIZE 100

void sort_strArray(char strs[][STR_SIZE], int len) {
    for (int i = len - 1; i > 0; --i) {
        int max = i;
        for (int j = 0; j < i; ++j) {
            if (strcmp(strs[j], strs[max]) > 0) {
                max = j;
            } 
        }
        char tmp[STR_SIZE];
        strcpy(tmp, strs[i]);
        strcpy(strs[i], strs[max]);
        strcpy(strs[max], tmp);
    } 
}

void sort_strIndex(char **pI, int len) {
    for (int i = len - 1; i > 0; --i) {
        int max = i;
        for (int j = 0; j < i; ++j) {
            if (strcmp(pI[j], pI[max]) > 0) {
                max = j;
            } 
        }
        char *tmp = pI[i];
        pI[i] = pI[max];
        pI[max] = tmp;
    } 
}

void print_arrays(char p[][STR_SIZE], int len) {
    printf("--------------------------------\n");
    for (int i = 0; i < len; ++i) {
        puts(p[i]);
    }
    printf("--------------------------------\n");
}

void print_indexs(char **p, int len) {
    printf("--------------------------------\n");
    for (int i = 0; i < len; ++i) {
        puts(p[i]);
    }
    printf("--------------------------------\n");
}

int compare_str(const void *p1, const void *p2) {
    const char *s1 = (char*)p1;
    const char *s2 = (char*)p2;
    return strcmp(s1, s2);
}

int compare_index(const void *p1, const void *p2) {
    const char *s1 = *(char**)p1;
    const char *s2 = *(char**)p2;
    return strcmp(s1, s2);
}


int main() {
    char strs[N][STR_SIZE] = {
        "string",
        "king",
        "sky",
        "sea",
        "daught",
        "wine",
        "healthy",
        "apple",
        "love",
        "away"
    };

    /* sort_strArray(strs, N); */
    print_arrays(strs, N);
    
#if 1
    // 建立索引, 使用索引排序
    char* indexs[N];
    for (int i = 0; i < N; ++i) {
        indexs[i] = strs[i];
    }

    /* sort_strIndex(indexs, N); */
    /* print_indexs(indexs, N); */
    /* print_arrays(strs, N); */
#endif

    /* qsort(strs, N, STR_SIZE, compare_str); */    
    qsort(indexs, N, sizeof(char*), compare_index);    
    print_indexs(indexs, N);
    print_arrays(strs, N);
}
