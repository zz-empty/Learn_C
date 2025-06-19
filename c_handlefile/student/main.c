#include "stu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // 引用学生文件
  if (2 != argc) {
    fprintf(stderr, "Error: need stuinfo file\n");
    return -1;
  }

  // 根据文件内容得到一个学生链表
  List stulist;
  initList(&stulist);
  getStuList(argv[1], &stulist);

  // 将排序后的链表写回文件
  saveList(argv[1], &stulist);

  // 释放链表
  freeList(&stulist);
}
