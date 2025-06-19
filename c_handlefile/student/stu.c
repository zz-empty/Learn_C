#include "stu.h"
#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 2056
// 宏开关
#define ON 1
#define OFF 0

// 初始化链表
void initList(List *list) {
  list->pHead = list->pTail = NULL;
  list->size = 0;
}
// 头插
void insertList(List *list, Stu *stu) {
  if (!list->pHead) {
    list->pHead = list->pTail = stu;
  } else {
    stu->next = list->pHead;
    list->pHead = stu;
  }

  list->size++;
}

void printStu(Stu *node) {
  printf("%s\t%s\t%s\t%5.2f\t%5.2f\t%5.2f\t%5.2f\n", node->id, node->name,
         node->gender == Male ? "男" : "女", node->scores[0], node->scores[1],
         node->scores[2], node->total_score);
}

void printList(List *list) {
  Stu *p = list->pHead;
  while (p) {
    printStu(p);
    p = p->next;
  }
}

// 从文件中读取数据构建链表
void getStuList(const char *filename, List *list) {
  FILE *fp_r = (FILE *)fopen(filename, "r");

  char line[LINE_MAX];
  size_t size = 0;
  // 先读一下标题行，舍弃掉
  fgets(line, LINE_MAX, fp_r);
  // 读取每个学生数据
  while (1) {
    char *result = fgets(line, LINE_MAX, fp_r);
    if (NULL == result)
      break;
    // printf("%s", line);

    // 生成一个新的学生结构体
    Stu *node = (Stu *)malloc(sizeof(Stu));
    // 格式化读取
    char gender[10];
    sscanf(line, "%s %s %s %f %f %f", node->id, node->name, gender,
           &node->scores[0], &node->scores[1], &node->scores[2]);
    if (0 == strcmp(gender, "男")) {
      node->gender = Male;
    } else {
      node->gender = Famale;
    }
    node->total_score = node->scores[0] + node->scores[1] + node->scores[2];

#if ON
// 测试是否正确
// printStu(node);
#endif

    // 插入链表
    insertList(list, node);
  }

  fclose(fp_r);
}

// qsort参数
int compare_stu(const void *p1, const void *p2) {
  // p1 p2 是指向成员的指针
  Stu *s1 = *(Stu **)p1;
  Stu *s2 = *(Stu **)p2;

  // 浮点数无法比较相等
  if (s1->total_score > s2->total_score) {
    return -1;
  } else if (s1->total_score < s2->total_score) {
    return 1;
  }
  return 0;
}

// 将链表按总分降序写回到原来的文件
void saveList(const char *filename, List *list) {
  // printList(list);
  // 按总分递减排序链表
  pStu *arr = (pStu *)malloc(list->size * sizeof(pStu));
  pStu p = list->pHead;
  for (int i = 0; p; ++i, p = p->next) {
    arr[i] = p;
  }
#if OFF
  // 测试arr是否加载正确
  printf("------------------arr_init\n");
  for (int i = 0; i < list->size; ++i) {
    printStu(arr[i]);
  }
#endif

  qsort(arr, list->size, sizeof(Stu *), compare_stu);

#if OFF
  // 测试排序是否正确
  printf("-----------------qsort_arr\n");
  for (int i = 0; i < list->size; ++i) {
    printStu(arr[i]);
  }
#endif

  // 将链表写回文件
  FILE *fp_w = (FILE *)fopen(filename, "w");

  p = list->pHead;
  while (p) {
    fprintf(fp_w, "%s\t%s\t%s\t%5.2f\t%5.2f\t%5.2f\t%5.2f\n", p->id, p->name,
            p->gender == Famale ? "女" : "男", p->scores[0], p->scores[1],
            p->scores[2], p->total_score);
    p = p->next;
  }
  printf("写入成功！\n");

  fclose(fp_w);

  // 释放arr
  free(arr);
}

// 释放链表
void freeList(List *list) {
  while (list->pHead) {
    Stu *temp = list->pHead;
    list->pHead = list->pHead->next;
    free(temp);
    temp = NULL;
  }
  list->size = 0;
}
