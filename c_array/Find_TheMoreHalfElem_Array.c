#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE 15
#define M 30
#define SWAP(a, b) {int tmp = a; a = b; b = tmp;}

//打印数组
void print_array_int(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%3d", arr[i]);
    } 
    printf("\n");
}

//选择排序排序数组
void selectSort(int *arr, int len) {
    for (int i = len - 1; i > 0; --i) {
        //每次找出最大值下标，与arr[i]交换
        int max = 0;
        for (int j = 1; j <= i; ++j) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }
        SWAP(arr[i], arr[max]);
    }
}

typedef struct Elem {
    int _elem;  //元素
    int _cnt;   //出现的数量
}Elem_t, *pElem_t;

//找到超过数组数量一般的元素
int find_theHalfElem(int *arr, int len) {
    Elem_t elems[ARRAY_SIZE];
    memset(&elems, 0, sizeof(elems));
    int size_elems = 0;

    //遍历arr数组，对每个元素进行处理
    int exist;  //表示元素是否出现在elems
    for (int i = 0; i < len; ++i) { 
        exist = 0;
        //遍历elems，查看是否这个元素，如果有增加其数量，当数量超过一半就返回这个元素
        for (int j = 0; j < size_elems; ++j) {
            if (elems[j]._elem == arr[i]) {
                exist = 1;
                ++elems[j]._cnt;
                if (elems[j]._cnt > len / 2) {
                    return elems[j]._elem;
                }
            }
        }
        //如果没有找到这个元素，就将其加入elems
        if (!exist) {
            elems[size_elems]._elem = arr[i];
            elems[size_elems]._cnt = 1;
            ++size_elems;
        }
    }
    //没有超过一半的元素，就返回-1
    return -1;
}

//打乱数组的顺序
void mass_array(int *arr, int len) {
    srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        int pos = rand() % (len - 1); 
        SWAP(arr[i], arr[pos]);
    } 
}


int main()
{
    //找数量超出一半的元素

    //初始化一个随机数组, 将其中某个元素的数量超过一半
    srand(time(NULL)); 
    int *arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        arr[i] = rand() % M;
    }
    int repeat = rand() % (ARRAY_SIZE / 2);
    for (int i = ARRAY_SIZE / 2; i < ARRAY_SIZE; ++i) {
        arr[i] = arr[repeat];
    }
    mass_array(arr, ARRAY_SIZE);
    print_array_int(arr, ARRAY_SIZE);

    //使用一个数据结构，记录元素和其数量，如果数量超过一半就返回
    int result = find_theHalfElem(arr, ARRAY_SIZE);
    printf("超过数组一半数量的元素是:%d\n", result);

    //释放数组
    free(arr);
    arr = NULL;
    return 0;
}
