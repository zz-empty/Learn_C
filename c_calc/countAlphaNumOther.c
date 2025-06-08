#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1028

//统计字符串中的字母个数、数字个数、其他字符个数
void countAlphaNumOther(char *str, int *cnt_alp, int *cnt_num, int *cnt_oth) {
    int len = strlen(str);

    for (int i = 0; i < len; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            ++*cnt_num;
        } else if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            ++*cnt_alp;
        } else {
            ++*cnt_oth;
        }
    }
}

typedef struct Category {
    char name[4];
    int cnt;
}Category_t;


//根据字母、数字和其他字符，打印柱状图, 按照数量关系排列
void printCharChart(int cnt_alp, int cnt_num, int cnt_oth) {
    //有三部分，第一层打印个数，之后根据个数打印图形，最后一层打印标签
    //用数据结构存储名字和次数，再降序排列
    Category_t cate[3] = {
        {"alp", cnt_alp},
        {"num", cnt_num},
        {"oth", cnt_oth}
    };

    //降序排列
    for (int i = 0; i < 3; ++i) {
        int max = i;
        for (int j = i; j < 3; ++j) {
            if (cate[max].cnt < cate[j].cnt) {
                max = j;
            }
        }
        Category_t tmp = cate[i];
        cate[i] = cate[max];
        cate[max] = tmp;
    }

    //查看排序结果是否正确
    for (int i = 0; i < 3; ++i) {
        printf("cate[%d].name = %s, cate[%d].cnt = %d\n", i, cate[i].name, i, cate[i].cnt);
    }

    //打印图形
    char star[] = "*****";
    char gap[] = "   "; 
    //以最多的行数为标准，开始从上往下打印
    for (int i = cate[0].cnt; i >= 0; --i) {
        if (cate[0].cnt == i) {
            char str[20];
            int len = sprintf(str, "%d", cate[0].cnt);
            int total_spaces = 5 - len;
            int left = total_spaces / 2;
            int right = total_spaces - left;
            printf("%*s%s%*s\n", left, "", str, right, "");            //打印最大的数量
            continue;
        } else {
            printf("%s", star);
        }

        //打印第二种
        if (cate[1].cnt == i) {
            printf("%s", gap);
            char str[20];
            int len = sprintf(str, "%d", cate[1].cnt);
            int total_spaces = 5 - len;
            int left = total_spaces / 2;
            int right = total_spaces - left;
            printf("%*s%s%*s\n", left, "", str, right, "");            //打印最大的数量
            continue;
        } else if (cate[1].cnt > i) {
            printf("%s", gap);
            printf("%s", star);
        }

        //打印第三种
        if (cate[2].cnt == i) {
            printf("%s", gap);
            char str[20];
            int len = sprintf(str, "%d", cate[2].cnt);
            int total_spaces = 5 - len;
            int left = total_spaces / 2;
            int right = total_spaces - left;
            printf("%*s%s%*s\n", left, "", str, right, "");            //打印最大的数量
            continue;
        } else if (cate[2].cnt > i) {
            printf("%s", gap);
            printf("%s", star);
        }

        printf("\n");
    }
    printf(" %s     %s     %s\n", cate[0].name, cate[1].name, cate[2].name);
}

int main()
{
    //统计字符串中的不同类型数量，分成三种字母、数字和其他字符
    /* char str[] = "niyou dabing side 886 222## diewa~!"; */

    //从stdin读取一个字符串，并去掉末尾的换行符
    char str[20] = "";
    printf("please input a str:");
    fgets(str, sizeof(str) - 1, stdin);
    if (strlen(str) > 0) {
        str[strlen(str) - 1] = '\0';
    }
    puts(str);
    printf("len: %ld\n", strlen(str));

    //字母计数、数字计数、其他字符计数
    int cnt_alp = 0, cnt_num = 0, cnt_oth = 0;

    countAlphaNumOther(str, &cnt_alp, &cnt_num, &cnt_oth);
    printf("cnt_alp:%d, cnt_num:%d, cnt_oth:%d\n", cnt_alp, cnt_num, cnt_oth); 

    printCharChart(cnt_alp, cnt_num, cnt_oth);

    return 0;
}
