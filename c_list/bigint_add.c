#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 链表节点结构
typedef struct Node {
    int digit;
    struct Node *next;
} Node;

// 大整数结构
typedef struct {
    int sign;   // 1正数 -1负数
    Node *head;   // 个位在链表头
} BigInt;

// 创建新节点
Node* create_node(int digit) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->digit = digit;
    new_node->next = NULL;
    return new_node;
}

// 反转链表
Node* reverse_list(Node *head) {
    Node *pre = NULL, *cur = head, *next = NULL;
    while (cur) {
        next = cur->next;   // 保存下一个节点
        cur->next = pre;    // 将当前节点头插
        pre = cur;
        cur = next;         // 处理下一个节点
    }
    return pre;
}

// 比较两个大整数的绝对值大小
int compare_abs(Node *a, Node *b) {
    // 计算长度
    int len_a = 0, len_b = 0;
    Node *pa = a, *pb = b;
    while (pa && ++len_a) pa = pa->next;
    while (pb && ++len_b) pb = pb->next;    

    // 长度不相等
    if (len_a != len_b) return len_a > len_b ? 1 : -1;

    // 反转链表，挨个比较高位
    Node *rev_a = reverse_list(a);
    Node *rev_b = reverse_list(b);
    int result = 0;
    pa = rev_a;
    pb = rev_b;
    
    while (pa && pb) {
        if (pa->digit > pb->digit) {
            result = 1;
            break;
        } else if (pa->digit < pb->digit) {
            result = -1; 
            break;
        }
        pa = pa->next;
        pb = pb->next;
    }

    // 恢复原链表
    reverse_list(rev_a);
    reverse_list(rev_b);
    return result;
}

void free_list(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

// 字符串转大整数
BigInt str_to_bigint(const char *str) {
    BigInt num = {1, NULL};    
    if (*str == '-') {
        num.sign = -1;
        str++;
    }

    // 跳过前导零
    while (*str == '0' && *(str + 1)) str++;

    // 逆序存储数字
    Node **current = &num.head;
    for (int i = strlen(str) - 1; i >= 0; --i) {
        if (str[i] < '0' || str[i] > '9') {
            fprintf(stderr, "Invalid input: %c\n", str[i]);
            exit(EXIT_FAILURE);
        }
        *current = create_node(str[i] - '0');
        current = &(*current)->next;
    }
    return num;
}

// 加法运算（仅处理正数绝对值相加）
Node* add_digits(Node *a, Node *b) {
    Node *result = NULL;
    Node **current = &result;
    int carry = 0;

    while (a || b || carry) {
        int sum = carry;
        if (a) sum += a->digit;
        if (b) sum += b->digit;

        *current = create_node(sum % 10);
        carry = sum / 10;
        
        current = &(*current)->next;
        if (a) a = a->next;
        if (b) b = b->next;
    }

    return result;
}

// 减法运算 （a >= b) 
Node* sub_digits(Node *a, Node *b) {
    Node *result = NULL;
    Node **current = &result;
    int borrow = 0;

    while (a) {
        int a_digit = a->digit - borrow;    
        borrow = 0;
        int b_digit = b ? b->digit : 0;

        if (a_digit < b_digit) {
            a_digit += 10;
            borrow = 1;
        }

        *current = create_node(a_digit - b_digit);  // 加入结果
        current = &(*current)->next;    // 处理下一个节点
        
        a = a->next;    // a的下一个节点
        if (b) b = b->next;     // b的下一个节点
    }

    // 去除高位零
    result = reverse_list(result);
    while (result && result->digit == 0 && result->next) {
        Node *tmp = result;
        result = result->next;
        free(tmp);
    }

    return reverse_list(result);
}

BigInt add_bigint(BigInt a, BigInt b) {
    BigInt result = {1, NULL};
    
    if (a.sign == b.sign) {     // 同号相加
        result.head = add_digits(a.head, b.head);
        result.sign = a.sign;
    } else {     // 异号相加
        int cmp = compare_abs(a.head, b.head);
        if (0 == cmp) {
            result.head = create_node(0);
            return result;
        }

        if (cmp > 0) {
            result.head = sub_digits(a.head, b.head);
            result.sign = a.sign;
        } else {
            result.head = sub_digits(b.head, a.head);
            result.sign = b.sign;
        }
    }

    // 处理结果为0的情况
    if (result.head->digit == 0 && !result.head->next) {
        result.sign = 1;
    }

    return result;
}

// 大整数转字符串
char* bigint_to_str(BigInt num) {
    // 反转链表得到正确顺序
    Node *rev = reverse_list(num.head);

    // 计算字符串长度
    int len = 0;
    Node *current = rev;
    while (current && ++len) current = current->next;

    // 分配内存
    char *str = (char*)malloc(len + 2);     // 符号 + 数字 + '\0'
    int idx = 0;

    // 设置符号
    if (num.sign == -1) str[idx++] = '-';

    // 放数字
    current = rev;
    while (current) {
        str[idx++] = current->digit + '0';
        current = current->next;
    }
    str[idx] = '\0';

    // 恢复链表
    reverse_list(rev);
    return str;
}

int main() {
    char num1[100], num2[100];
    
    printf("输入第一个大整数：");
    scanf("%s", num1);
    printf("输入第二个大整数：");
    scanf("%s", num2);

    BigInt a = str_to_bigint(num1);
    BigInt b = str_to_bigint(num2);
    BigInt result = add_bigint(a, b);

    char *res_str = bigint_to_str(result);
    printf("计算结果：%s\n", res_str);

    // 释放内存
    free(res_str);
    free_list(a.head);
    free_list(b.head);
    free_list(result.head);

    return 0;
}
