#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1028

//最大支持32位整数（8位16进制）
#define HEX_BUFFER_SIZE 9

void decimalToBinary(int num, char *binary) {
    char tmp[32] = ""; //倒序存储转换后的二进制
    int i = 0; //用来放置二进制的位置

    while (num) {
        tmp[i++] = num % 2 ? '1' : '0';
        num /= 2;
    }

    //将tmp逆转，放入binary
    int j = 0;
    for (int k = i - 1; k >= 0; --k) {
        binary[j++] = tmp[k];
    }
    /* printf("tmp:%s, binary:%s\n", tmp, binary); */
}

int binaryTodecimal(const char *bin_str) {
    //使用位运算
    int decimal = 0;
    for (int i = 0; bin_str[i] != '\0'; ++i) {
        decimal = (decimal << 1) | (bin_str[i] - '0'); 
        printf("decimal = %d\n", decimal);
    } 
    return decimal;
}

void decimalToHex(int decimal, char *hex) {
    char hex_chars[] = "0123456789ABCDEF";  //字母映射表
    char tmp[HEX_BUFFER_SIZE] = "";

    //将10进制数转换成16进制
    int index = 0;
    while (decimal) {
        tmp[index++] = hex_chars[decimal % 16];
        decimal /= 16;
    }
    tmp[index] = '\0';

    //将倒序的16进制逆转
    for (int i = 0; i < index; ++i) {
        hex[i] = tmp[index - 1 - i];
    } 
}

//十六进制字符转数字
int hex_char_to_value(char c) {
    c = toupper(c);    
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + c - 'A';
    return -1;  //不会到这
}

//十六进制转数字
int hexToDecimal(const char *hex) {
    int result = 0;
    size_t start = 0;

    //如果有前缀，去掉
    if (strlen(hex) > 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
        start = 2;
    }

    for ( ; hex[start] != '\0'; ++start) {
        result = result * 16 + hex_char_to_value(hex[start]);
        printf("hex[%ld]:%c, result = %d\n", start, hex[start], result);
    }
    return result;
}

void test1()
{
    //将10进制数转换成2进制数（使用字符数组存储）
    int num = 56;
    char binary[33] = {0};
    
    printf("请输入十进制整数：");
    scanf("%d", &num);

    if (num < 0) {
        printf("本程序只能处理正整数！\n");
        return;
    }

    decimalToBinary(num, binary);
    printf("转换后的二进制：%s\n", binary);
}

void test2()
{
    //将二进制数转成十进制数 
    char binary[] = "10010011";
    int decimal = binaryTodecimal(binary);
    
    printf("binary:%s, decimal:%d\n", binary, decimal);
}

void test3()
{
    //将十进制数转成十六进制
    int decimal = 32767;
    char hex_str[HEX_BUFFER_SIZE] = "";

    decimalToHex(decimal, hex_str);
    printf("decimal:%d, hex_str:%s\n", decimal, hex_str);
}

int main() 
{
    //十六进制转十进制
    char hex[MAX_SIZE] = "0xABD";
    printf("hex:%s, decimal:%d\n", hex, hexToDecimal(hex)); 
}
