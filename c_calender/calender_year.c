#include <stdio.h>
#include <string.h>

#define LINE 7
#define MAX_DAYS 50

// 存储年月日
typedef struct Date {
    int year;
    int month;
    int day;
}Date_t;

// 存储月份, 天数和月份第一天的星期
typedef struct Month_Days_Week {
    int month;
    int month_days;
    int first_weekday;
}Month_t;

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

/* // 验证日期的有效性 */
/* int validate_date(Date_t d) { */
/*     if (d.month < 1 || d.month > 12) return 0; */ 
/*     /1* if (d.day < 1 || d.day > get_month_days(d)) return 0; *1/ */
/*     return 1; */
/* } */

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
const char *get_weekdayday(Date_t d) {
    const char * weekdays[] = {"一", "二", "三", "四", "五", "六", "日"};
    int days = date_to_days(d);
    return weekdays[days % 7];
}

// 根据月的天数和第一天的星期打印日历
void canlender_month(Month_t mt, char canlender[][MAX_DAYS]) {
    int month = mt.month;
    int days = mt.month_days;
    int weekday = mt.first_weekday;

    /* char canlender[6][50]; */
    memset(canlender, 0, sizeof(char) * 6 * 50);
    int n = 0;

    /* printf("days = %d, week = %d\n", days, weekday); */

    // 输入标题行
    sprintf(canlender[n++] ,"%-3d%4s%4s%4s%4s%4s%4s%4s", month, "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN");
    sprintf(canlender[n], "%3s", " ");  // 每行的对齐
    
    int i = 1; // 控制换行
    int j = 1; // 控制天数
              
    // 输入week - 1个空格, 表示每月的开始星期
    for (;i < weekday; ++i) {
        sprintf(canlender[n] + strlen(canlender[n]), "%4s", " ");
    }

    // 输入每个星期的内容 
    for ( ; j <= days; ++i, ++j) {
        sprintf(canlender[n] + strlen(canlender[n]), "%4d", j);
        if (0 == i % 7) {
            ++n;
            sprintf(canlender[n], "%3s", " ");  // 每行的对齐
        }
    }

    /* // 验证日历是否正确 */
    /* for (n = 0; n < LINE; ++n) { */
    /*     printf("%-31s\n", canlender[n]); */
    /* } */
}



// 根据年，打印年日历
void canlender_year(int year) {
    Month_t months[13];
    // 初始化每一个月的天数和星期
    for (int i = 1; i <= 12; ++i) {
        Date_t tmp = {year, i, 1};
        months[i].month = i;
        months[i].month_days = get_month_days(tmp);
        months[i].first_weekday = date_to_days(tmp) % 7 + 1;
    }

    /* for (int i = 0; i < 12; ++i) { */
    /*     printf("第%d月，days:%d, first_weekday:%d\n", i + 1, mdw[i].month_days, mdw[i].first_weekday); */
    /* } */

    for (int i = 1; i <= 6; ++i) {
        char canlender1[LINE][MAX_DAYS];
        char canlender2[LINE][MAX_DAYS];

        canlender_month(months[i], canlender1);
        canlender_month(months[i + 6], canlender2);

        for (int j = 0; j < LINE; ++j) {
            printf("%-31s", canlender1[j]);
            printf("%3s", " ");
            printf("%-31s\n", canlender2[j]);
        }
    }
}

int main()
{
    //输入年，得到一整年的日历
    Date_t date = {1, 1, 1};
    printf("请输入一个日期（年）：");
    scanf("%d", &date.year);

#if 0
    //得到该月的天数，和第一天的星期
    int month_day = get_month_days(date); 
    int first_weekday = date_to_days(date) % 7 + 1;    //1 2 3 4 5 6 7
                                               
    //打印月日历
    canlender_month(month_day, first_weekday); 
#endif

    canlender_year(date.year);
    return 0;
}
