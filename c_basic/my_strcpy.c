#include <stdio.h>
#define STR_SIZE 1024

void myStrcpy(char *dest, char *src) {
    int i = 0;
    for (; src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int myStrlen(char *str) {
    int size = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        size++;
    }
    return size;
}

int myStrcmp(char *s1, char *s2) {
    // s1 > s2 返回1
    // s1 < s2 返回-1
    // s1 = s2 返回0

    int i = 0;
    for (; s1[i] != '\0' && s2[i] != '\0'; ++i) {
        if (s1[i] < s2[i]) {
            return -1;
        } else if (s1[i] > s2[i]) {
            return 1;
        }
    }

    if (s1[i]) return 1;
    else if (s2[i]) return -1;
    else return 0;
}

void myStrcat(char *dest, char *str) {
    int i = 0;
    int len = myStrlen(dest);
    for (; str[i] != '\0'; ++i) {
        dest[i + len] = str[i];
    }
    dest[i + len] = '\0';
}

void test()
{
    char str[STR_SIZE] = ""; 
    printf("请输入一个字符串：");
    fgets(str, STR_SIZE, stdin);
    if ('\n' == str[myStrlen(str) - 1]) {
        str[myStrlen(str) - 1] = '\0';
    }
    puts(str);

    /* char s2[STR_SIZE] = ""; */
    /* myStrcpy(s2, str); */
    /* puts(s2); */

    char s2[STR_SIZE] = "";
    printf("请输入另一个字符串：");
    fgets(s2, STR_SIZE, stdin);
    if ('\n' == s2[myStrlen(s2) - 1]) {
        s2[myStrlen(s2) - 1] = '\0';
    }
    puts(s2);
    
    if (myStrcmp(str, s2) == 1) {
        printf("s1大于s2\n");
    } else if (myStrcmp(str, s2) == -1) {
        printf("s1小于s2\n");
    } else {
        printf("s1等于s2\n");
    }
}

int main()
{
    char str[STR_SIZE] = ""; 
    printf("请输入一个字符串：");
    fgets(str, STR_SIZE, stdin);
    if ('\n' == str[myStrlen(str) - 1]) {
        str[myStrlen(str) - 1] = '\0';
    }
    puts(str);

    /* char s2[STR_SIZE] = ""; */
    /* myStrcpy(s2, str); */
    /* puts(s2); */

    char s2[STR_SIZE] = "";
    printf("请输入另一个字符串：");
    fgets(s2, STR_SIZE, stdin);
    if ('\n' == s2[myStrlen(s2) - 1]) {
        s2[myStrlen(s2) - 1] = '\0';
    }
    puts(s2);
    
    myStrcat(str, s2);
    puts(str);
}
