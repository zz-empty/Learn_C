#include <stdio.h>
#include <string.h>

void reverse(char *str) {
    int len = strlen(str);
    char tmp;
    for (int i = 0; i < len / 2; ++i) {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

void print_str(char *str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        putchar(str[i]);
    }
    printf("\n");
}

int main()
{
    // 大整数加法
    char s1[] = "100000000000000000000000000000000000";
    char s2[] = "2000000000000000000000";

    reverse(s1);
    reverse(s2);
    
    print_str(s1);
    print_str(s2);

    // 相加
    int flag = 0; //表示进位
    char result[100] = "";
    int i = 0;
    for (; s1[i] != '\0' && s2[i] != '\0'; ++i) {
        int num = s1[i] - '0' + s2[i] - '0' + flag;
        result[i] = num % 10 + '0';
        if (num > 9) {
            flag = 1;
        }
    }

    while (i < (int)strlen(s1)) {
        int num = s1[i] - '0' + flag;
        result[i] = num % 10 + '0';
        if (num > 9) flag = 1;
        ++i;
    }
    while (i < (int)strlen(s2)) {
        int num = s2[i] - '0' + flag;
        result[i] = num % 10 + '0';
        if (num > 9) flag = 1;
        ++i;
    }

    puts(result);
    reverse(result);
    puts(result);
}
