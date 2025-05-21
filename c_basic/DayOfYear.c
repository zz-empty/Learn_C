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

//根据月日计算出当年的天数
int count_days(Date_t date) {
    int days = 0;
    for (int i = 1; i < date._month; ++i) {
        days += get_max_days(date._year, i); 
    }

    return days + date._day;
}

int main()
{
    Date_t date;
    printf("请输入年月日：");
    scanf("%d%d%d", &date._year, &date._month, &date._day);
    printf("year:%d, month:%d, day:%d\n", date._year, date._month, date._day);

    int days = count_days(date); 
    printf("是当年的第%d天\n", days);
}
