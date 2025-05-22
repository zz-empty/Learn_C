#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *digits;   // 逆序存储的数字
    int sign;       // 1正数 -1负数
}BigInt;

// 移除字符串末尾的0（逆序前的后导0）
char* remove_trailing_zeros(char *num) {
    int len = strlen(num);
    while (len > 1 && num[len - 1] == '0') {
        num[--len] = '\0';
    }
    return num;
}

// 比较两个大数的绝对值大小（逆序）
int compare_reverse(char *a, char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    if (len_a > len_b) return 1;
    if (len_a < len_b) return -1;
    for (int i = len_a - 1; i >= 0; --i) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

// 逆序加法（处理两个正数）
char* add_reverse(char *a, char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    int max_len = len_a > len_b ? len_a : len_b;
    char *res = (char*)calloc(max_len, sizeof(char));

    int carry = 0;
    for (int i = 0; i < max_len; ++i) {
        int n1 = (i < len_a) ? a[i] - '0' : 0;
        int n2 = (i < len_b) ? b[i] - '0' : 0;
        int sum = n1 + n2 + carry;
        res[i] = sum % 10 + '0';
        carry = sum / 10;
    }

    if (carry) res[max_len] = carry + '0';
    return res;
}

// 逆序减法（a >= b, 处理两个正数）
char* sub_reverse(char *a, char *b) {
    int len = strlen(a);
    int len_b = strlen(b);
    char *res = (char*)malloc(len + 1);
    memset(res, 0, len + 1);

    int borrow = 0;
    for (int i = 0; i < len; ++i) {
        int n1 = a[i] - '0' - borrow;
        int n2 = (i < len_b) ? b[i] - '0': 0;
        borrow = 0;
        if (n1 < n2) {
            n1 += 10;
            borrow = 1;
        }
        res[i] = n1 - n2 + '0';
    }

    return remove_trailing_zeros(res);
}

// 解析输入字符串
BigInt parse_input(const char *input) {
    BigInt num = {NULL, 1};
    if (*input == '-') {
        num.sign = -1;
        input++;
    } else if (*input == '+') {
        input++;
    }

    // 跳过前导0
    while (*input == '0' && *(input + 1) == '0') ++input;

    int len = strlen(input);
    num.digits = (char*)malloc(len + 2);
    for (int i = 0; i < len; ++i) {
        num.digits[i] = input[len - 1 - i];
    }
    num.digits[len] = '\0';
    return num;
}

// 大整数加法主函数
char *big_add(const char *a, const char *b) {
    BigInt num1 = parse_input(a);
    BigInt num2 = parse_input(b);

    // 符号相同的情况
    if (num1.sign == num2.sign) {
        char *sum = add_reverse(num1.digits, num2.digits);
        int len = strlen(sum);
        for (int i = 0; i < len / 2; ++i) {
            char tmp = sum[i];
            sum[i] = sum[len - 1 - i];
            sum[len - 1 - i] = tmp;
        }
        char *res = (char*)malloc(len + 2);
        sprintf(res, "%s%s", (num1.sign != 1) ? "-": "", sum);
        free(sum);
        return res;
    }

    // 符号不同的情况
    int cmp = compare_reverse(num1.digits, num2.digits);
    char *abs_result;
    int res_sign;

    if (cmp == 1) {
        abs_result = sub_reverse(num1.digits, num2.digits);
        res_sign = num1.sign;
    } else {
        abs_result = sub_reverse(num2.digits, num1.digits);
        res_sign = num2.sign;
    }

    // 处理结果, 逆转
    int len = strlen(abs_result);
    for (int i = 0; i < len / 2; ++i) {
        char tmp = abs_result[i];
        abs_result[i] = abs_result[len - 1 - i];
        abs_result[len - 1 - i] = tmp;
    }

    char *res = (char*)malloc(len + 2);
    sprintf(res, "%s%s", (res_sign == 1) ? "": "-", abs_result);
    free(abs_result);
    return res;
}

int main() {
    char a[100], b[100];
    // 输入第一个大数
    printf("输入第一个大数：");
    scanf("%s", a);
    printf("输入第二个大数：");
    scanf("%s", b);


    char *result = big_add(a, b);
    printf("计算结果：%s\n", result);
    free(result);
    return 0;
}
