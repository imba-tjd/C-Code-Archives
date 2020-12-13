// 计算某一天是星期几
// 以1900年1月1日星期一为基准；不要试图以手动输入年月日星期为基准去算，否则就连年是否要加1都需要大量判断；不过现在才发现tm_wday已经算好了

#include <locale.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

typedef struct {
    int year;
    int month;
    int day;
} Date;

Date GetToday(void) {
    time_t tt = time(NULL);
    struct tm *lt = localtime(&tt);
    return (Date){lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday};
}

static const int DaysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static inline int IsLeapYear(int year) { return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; }

int GetWeek(Date date) {
    int days = 0;
    for (int i = 1900; i < date.year; i++)
        days += IsLeapYear(i) ? 366 : 365;
    for (int i = 1; i < date.month; i++)
        days += DaysPerMonth[i];
    days += date.day;
    if (date.month > 2 && IsLeapYear(date.year))
        days += 1;
    return days % 7;
}

static const char *CNWeeks[] = {"天", "一", "二", "三", "四", "五", "六"};
static inline const char *GetCNWeek(Date date) { return CNWeeks[GetWeek(date)]; }

int main(void) {
    Date today = GetToday();
    printf("今天的日期是： %d 年 %d 月 %d 日，星期%s。\n", today.year, today.month, today.day, GetCNWeek(today));

    assert(5 == GetWeek((Date){1901, 2, 1}));
    assert(4 == GetWeek((Date){2000, 6, 1}));
}
