#include <stdio.h>
#include <string.h>

#define SIZE 20
#define MAX 100
#define MAXKEY 1000
#define SWAP_INT(a, b) {int tmp = a; a = b; b = tmp;} 

int* random_arr(int len, int max);
void print_arr(int *arr, int len);

// qsort的参数
int compare(const void *p1, const void *p2) {
    int *l = (int*)p1;
    int *r = (int*)p2;
    return *l - *r;
}

int hash(char *key) {
	int h = 0, g;
	while (*key) {
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAXKEY;
}

void print_strings(char (*p)[MAX], int len) {
    printf("-------------------------\n");
    for (int i = 0; i < len; ++i) {
        printf("%s\n", p[i]);
    }
    printf("-------------------------\n");
}


int main() {
    char dict[SIZE][MAX] = {
        "word", "heahty",
        "eat", "tiger",
        "wave", "win",
        "zero", "you",
        "sky", "tree",
        "abandon", "bird",
        "mouse", "house",
        "welcome", "is",
        "hello", "world",
        "teacher", "fight"
    };

    print_strings(dict, SIZE);

    // 哈希查找
    int hashTable[MAXKEY] = {0};    // 哈希表，下标是数组元素，元素是数组下标
    memset(hashTable, -1, sizeof(int) * MAXKEY);    // 初始化为-1，表示没有这个元素
    // 遍历原数组的每个元素，通过哈希算法转化，放入哈希表
    for (int i = 0; i < SIZE; ++i) {
        hashTable[hash(dict[i])] = i;
    }

    // 输入字符串，查看是否在数组中，如果在返回下标
    char tmp[MAX] = "";
    printf("输入一个字符串：");
    scanf("%s", tmp);
    int result = hashTable[hash(tmp)];
    if (-1 == result) {
        printf("数组中没有这个元素\n");
    } else {
        printf("%s的下标是%d\n", tmp, result);
    }
}

