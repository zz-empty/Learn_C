#ifndef __STU_H__
#define __STU_H__

#define ID_MAX 20
#define NAME_MAX 50

typedef enum { Famale, Male } Gender;

typedef struct Student {
  char id[ID_MAX];
  char name[NAME_MAX];
  Gender gender;
  float scores[3];
  float total_score;
  struct Student *next;
} Stu, *pStu;

typedef struct StudentList {
  Stu *pHead;
  Stu *pTail;
  int size;
} List;

// 初始化链表
void initList(List *list);
// 头插
void insertList(List *list, Stu *stu);
// 从文件中读取数据构建链表
void getStuList(const char *filename, List *list);
// 将链表按总分降序写回到原来的文件
void saveList(const char *filename, List *list);
// 释放链表
void freeList(List *list);

#endif // !DEBU
