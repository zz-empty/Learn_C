#include <stdio.h>

typedef struct Date {
    int year;
    int month;
    int day;
}Date_t;

// 判断是否是闰年
int is_leapyear(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

// 获取月份的天数
int get_month_days(Date_t d) {
    const int base[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (d.month == 2 && is_leapyear(d.year)) {
        return 29;
    }
    return base[d.month - 1];
}

// 验证日期的有效性
int validate_date(Date_t d) {
    if (d.month < 1 || d.month > 12) return 0; 
    if (d.day < 1 || d.day > get_month_days(d)) return 0;
    return 1;
}

// 日期转天数 (从1900-1-1开始)
int date_to_days(Date_t d) {
    int days = 0;
    // 年份累计
    for (int i = 1900; i < d.year; ++i) {
        days += is_leapyear(i) ? 366 : 365;
    }

    // 月份累计
    for (int m = 1; m < d.month; ++m) {
        Date_t tmp = {d.year, m, 1};
        days += get_month_days(tmp);
    }

    // 天数累计
    return days + d.day - 1;
}

// 天数转日期 
Date_t days_to_date(int total_days) {
    Date_t result = {1900, 1, 1};

    while (total_days > 0) {
        int day_in_year = is_leapyear(result.year) ? 366 : 365;
        if (total_days >= day_in_year) {
            total_days -= day_in_year;
            result.year++;
        } else {
            break;
        }
    }

    while (total_days > 0) {
        int day_in_month = get_month_days(result);
        if (total_days > day_in_month) {
            total_days -= day_in_month;
            result.month++;
        } else {
            result.day = total_days + 1;
            total_days = 0;
        }
    }
    
    return result;
}

// 根据日期返回星期
const char *get_weekday(Date_t d) {
    const char * weeks[] = {"一", "二", "三", "四", "五", "六", "日"};
    int days = date_to_days(d);
    return weeks[days % 7];
}

int main()
{
    // 输入日期，输出经过n天以后的日期和星期
    Date_t date;
    int n;
    printf("请输入一个日期（年月日）：");
    scanf("%d%d%d", &date.year, &date.month, &date.day);

    if (!validate_date(date)) {
        printf("无效日期!\n");
        return -1;
    }

    // 输入经过多少天
    printf("请输入过了多少天：");
    scanf("%d", &n);

    // 计算新日期
    int total_days = date_to_days(date) + n;
    Date_t new_date = days_to_date(total_days);

    printf("\n计算结果\n");
    printf("原日期：%d-%02d-%02d 星期%s\n",
            date.year, date.month, date.day, get_weekday(date));
    printf("%d天后，%d-%02d-%02d 星期%s\n",
            n, new_date.year, new_date.month, new_date.day, get_weekday(new_date));

    return 0;
}
