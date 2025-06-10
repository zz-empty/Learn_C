#include <string.h>
void format_allchar(char *line) {
    // 去除line中的非法字符，并将大写字母转成小写
    char c;
    int len = strlen(line);
    for (int i = 0; i < len; ++i) {
        c = line[i];
        if (c >= 'A' && c <= 'Z') {
            line[i] += 32;
        }
        else if ('\n' == c) {
            continue;
        }
        else if (c >= 'a' && c <= 'z') {
            continue;
        }
        else {
            line[i] = ' ';
        }
    }
}
