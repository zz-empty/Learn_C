#include <stdio.h>

typedef struct Date {
    int _year;
    int _month;
    int _day;
    int _week;
}Date_t;

int main()
{
    //根据年月日，得出这一天的星期
    Date_t date;
    printf("请输入一个年月日：");
    scanf("%d%d%d", &date._year, &date._month, &date._day);
    
    //求出这个日期距离公元元年的天数
    
    //计算到前一年的天数
    int leap_count = (date._year - 1) / 4 - (date._year - 1) / 100 + (date._year - 1) / 400;
    int total_days = (date._year - 1) * 365 + leap_count;

    //处理当前年份的月份天数
    int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((date._year % 4 == 0 && date._year % 100 != 0) || date._year % 400 == 0) {
        month_days[1] = 29; 
    }

    //累加当月之前的天数
    for (int i = 0; i < date._month - 1; ++i) {
        total_days += month_days[i];
    }

    //加上当前日期的天数
    total_days += date._day - 1; //从零开始计数

    //计算星期索引
    const char *weekdays[] = {
        "星期一",
        "星期二",
        "星期三",
        "星期四",
        "星期五",
        "星期六",
        "星期日",
    };

    date._week = total_days % 7;
    printf("该日期是：%s\n", weekdays[date._week]);
    return 0;
}
