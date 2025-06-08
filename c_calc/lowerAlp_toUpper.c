#include <stdio.h>

int main()
{
    char ch = 0;
    printf("小写字母转成大写字母，非法字符不响应，输入?退出\n");
    while (1) {
        ch = getchar();
        if (ch == '?') break;
        if (ch > 'z' || ch < 'a') continue;
        printf("ch = %c\n", ch + 'A' - 'a');
    }
    return 0;
}
