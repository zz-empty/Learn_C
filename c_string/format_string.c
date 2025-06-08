#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 1024

void split_digits_letters(char *str) {
    // 将一个字符串的数字和字母分开，数字在前，字母在后
    // 用两个数组分别存储数字和字母
    int len = strlen(str);
    char *digest = (char*)malloc(len + 1);
    char *letters = (char*)malloc(len + 1);

    int d_idx = 0;
    int l_idx = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            digest[d_idx++] = str[i]; 
        } else {
            letters[l_idx++] = str[i];
        }
    }

    digest[d_idx] = '\0';
    letters[l_idx] = '\0';
    strcpy(str, digest);
    strcat(str, letters);

    free(digest);
    free(letters);
}

void replace_space(char *str) {
    // 将空格替换成%020
    // 有越界风险，确保str不会访问越界

    int len = strlen(str);
    char *tmp = (char*)malloc(2 * len);
    int t_idx = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (' ' == str[i]) {
            tmp[t_idx++] = '%';
            tmp[t_idx++] = '0';
            tmp[t_idx++] = '2';
            tmp[t_idx++] = '0';
        } else {
            tmp[t_idx++] = str[i];
        }
    }

    tmp[t_idx] = '\0';
    strcpy(str, tmp); 
}

void remove_char(char *str, char c) {
    // 移除字符串中的某个字符
    int len = strlen(str);
    char *tmp = (char*)malloc(len + 1);
    int t_idx = 0;
    for (int i = 0; str[i] != '0'; ++i) {
        if (c != str[i]) {
            tmp[t_idx++] = str[i];
        }
    }
    strcpy(str, tmp);
}

int exist(char *str, char c) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (c == str[i]) {
            return 1;
        }
    }
    return 0;
}

void removeDuplicates(char *str) {
    // 去除重复元素
    int idx = 0;
    char *tmp = (char*)malloc(strlen(str));
    for (int i = 0; str[i] != '\0'; ++i) {
        if (!exist(tmp, str[i])) {
            tmp[idx++] = str[i];
        }
    }

    tmp[idx] = '\0';
    strcpy(str, tmp);
}

void removeExtraSpaces(char *str) {
    // 删除句子中的多余空格，前导空格，尾随空格
    int idx = 0;
    char *tmp = (char*)malloc(strlen(str));
    memset(tmp, 0, strlen(str));

    int i = 0;
    for (; str[i] == ' '; ++i); // 删除前导空格
    for (; str[i] != '\0'; ++i) {
        if (i - 1 > 0 && str[i - 1] == ' ' && str[i] == ' ') {
            // 有连续空格, 跳过这个元素
            continue;
        }
        tmp[idx++] = str[i];
    }

    tmp[idx - 1] == ' ' ? tmp[idx - 1] = '\0' : 1;
    strcpy(str, tmp);
}

int split_words(char *str) {
    // 字符串里只有单词和空格
    int cnt = 0;
    char word[STR_SIZE] = "";
    int w_idx = 0;

    // 从字符串中拆出单词
    for (int i = 0; str[i] != '\0'; ++i) {
        if (' ' != str[i]) {
            word[w_idx++] = str[i];
        } else {
            // 读取到了一个单词
            ++cnt;
            // 打印单词
            word[w_idx] = '\0';
            puts(word);
            w_idx = 0;
        }
    }

    if (strlen(word)) {
        ++cnt;
        // 打印单词
        word[w_idx] = '\0';
        puts(word);
    }
    return cnt;
}

int main()
{
    
    // 读取一个字符串
    printf("请输入一个字符串：");
    char str[STR_SIZE] = "";
    fgets(str, STR_SIZE, stdin);
    str[strlen(str) - 1] = '\0';
    puts(str);

    /* // 分离数字和字母 */
    /* split_digits_letters(str); */
    /* puts(str); */

    /* // 替换空格为%020 */
    /* replace_space(str); */
    /* puts(str); */ 

    /* // 移除某个字符 */
    /* remove_char(str, 'a'); */
    /* puts(str); */


    /* // 去除重复元素 */
    /* removeDuplicates(str); */
    /* puts(str); */

    // 删除多余空格
    removeExtraSpaces(str);
    /* puts(str); */

    // 得到字符串包含的单词个数
    printf("这个字符串包含%d个单词\n", split_words(str));
}
