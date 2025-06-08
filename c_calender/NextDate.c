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
    int months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    --date._month; //总天数不能加当月的
    if (1 == date._month) return date._day;
    if (2 == date._month) return 31 + date._day;

    //判断是否是闰年
    int leapyear = date._year % 400 == 0 || (date._year % 4 == 0 && date._year % 100 != 0);    
    int days = months[1] + months[2] + leapyear;
    while (date._month > 2) {
        /* printf("days:%d, month:%d\n", days, date._month); */
        days += months[date._month]; 
        --date._month; 
    } 

    return days + date._day;
}

//根据日期计算出第二天的日期
Date_t getdate(Date_t date) {
    Date_t result; //下一天的日期
                   
    result = date;
    int days = count_days(date);//当天日期的天数
    int leapyear = date._year % 400 == 0 || (date._year % 4 == 0 && date._year % 100 != 0);    
    printf("leapyear = %d\n", leapyear);
    //如果是年末
    if ((leapyear == 1 && 366 == days) || (leapyear == 0 && 365 == days)) {
        printf("是年末!\n");
        ++result._year;
        result._month = 1;
        result._day = 1;
        return result;
    } 

    //不是年末, 是当月最后一天
    if (31 == date._day && 
       (1 == date._month || 3 == date._month || 5 == date._month ||
        7 == date._month || 8 == date._month || 10 == date._month)) {
        result._month++;
        result._day = 1; 
        return result;
    } else if (30 == date._day && 
            (4 == date._month || 6 == date._month || 
             9 == date._month || 11 == date._month)) {
        result._month++;
        result._day = 1;
        return result;
    } else if (28 + leapyear == date._day && 2 == date._month) {
        result._month++;
        result._day = 1;
        return result;
    }

    //不是年末，也不是月末
    result._day++;
    return result;
}

/* 输入年月日，输出该日期的下一天的年月日 
 * 思路：
 *  两个函数解决，一个算闰年，一个算当月最大天数
 * */
int main()
{
    printf("请输入年月日：");
    Date_t date;
    scanf("%d%d%d", &date._year, &date._month, &date._day);

    int max_days = get_max_days(date._year, date._month);
    date._day++;    //日期增加

    //判断边界，月末，年末
    if (date._day > max_days) {
        date._month++;
        date._day = 1;
        if (date._month > 12) {    //年末
            date._year++;
            date._month = 1;
        }
    }

    printf("下一天的日期是：%4d-%d-%d\n", date._year, date._month, date._day);
}
