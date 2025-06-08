#include <stdio.h>

typedef struct Date {
    int _year;
    int _month;
    int _day;
}Date_t, *pDate_t;

//判断是否是闰年
int is_leap_year(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

//得到当月最大天数
int get_max_days(int year, int month) {
    if (month < 1 || month > 12) {
        return -1;
    }
    if (2 == month) {
        return 28 + is_leap_year(year);
    } else if (4 == month || 6 == month || 9 == month || 11 == month) {
        return 30;
    } else {
        return 31;
    }
}

//得到当年最大天数
int max_days_year(int year) {
    return 365 + is_leap_year(year);
}

//根据月日计算出当年的天数
int count_days(Date_t date) {
    int days = 0;
    for (int i = 1; i < date._month; ++i) {
        days += get_max_days(date._year, i); 
    }

    return days + date._day;
}

int days_of_dates(Date_t d1, Date_t d2) {
    //求两个日期间的天数
    //如果是同一年的直接相减
    //如果不在同一年，大的年-小的年 + 大的天数 + 小的剩余天数
    
    if (d1._year == d2._year) {
        int days1 = count_days(d1);
        int days2 = count_days(d2);
        return  days1 > days2 ? days1 - days2 : days2 - days1; 
    }

    //确保d1的年份是大的
    if (d1._year < d2._year) {
        Date_t tmp = d1;
        d1 = d2;
        d2 = tmp;
    }
    
    int days = 0;
    days += count_days(d1) + max_days_year(d2._year) - count_days(d2);
    d2._year++;
    while (d1._year > d2._year) {
        days += max_days_year(d2._year);
        d2._year++; 
    }
    return days;
}

int main()
{
    Date_t d1, d2;
    printf("请输入第一个日期（年-月-日）：");
    scanf("%d%d%d", &d1._year, &d1._month, &d1._day);
    printf("请输入第二个日期（年-月-日）：");
    scanf("%d%d%d", &d2._year, &d2._month, &d2._day);

    printf("两个日期相差的天数：%d\n", days_of_dates(d1, d2));
}
