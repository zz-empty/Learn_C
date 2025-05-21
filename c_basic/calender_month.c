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
    /* if (d.day < 1 || d.day > get_month_days(d)) return 0; */
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

// 根据月的天数和第一天的星期打印日历
void canlender_month(int days, int week) {
    printf("days = %d, week = %d\n", days, week);
    printf("%4s%4s%4s%4s%4s%4s%4s\n", "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN");
    
    int i = 1; //i 用来控制换行
    // 打印week - 1个空格
    for (;i < week; ++i) {
        printf("%4s", " ");
    }

    for (int j = 1; j <= days; ++i, ++j) {
        printf("%4d", j);
        if (0 == i % 7) printf("\n");
    }
}

int main()
{
    //输入年月，得到该月的日历
    Date_t date;
    printf("请输入一个日期（年月）：");
    scanf("%d%d", &date.year, &date.month);
    date.day = 1;

    if (!validate_date(date)) {
        printf("无效日期!\n");
        return -1;
    }

    //得到该月的天数，和第一天的星期
    int month_day = get_month_days(date); 
    int first_week = date_to_days(date) % 7 + 1;    //1 2 3 4 5 6 7
                                               
    //打印月日历
    canlender_month(month_day, first_week); 
    return 0;
}
