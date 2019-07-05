// 计算某一天是星期几
// 以1900年1月1日星期一为基准；不要试图改成手动输入年月日星期的基准再去算，连年是否要加1都需要大量判断
// 获取当前的时间代码来源：https://zhidao.baidu.com/question/17712149.html

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>

typedef struct
{
    int year;
    int month;
    int day;
} Date;

static inline Date SetDate(int year, int month, int day) { return (Date){year, month, day}; }

Date GetToday(void)
{
    Date today;

    struct tm *lt;
    time_t tt = time(NULL);
    lt = localtime(&tt);

    today.year = lt->tm_year + 1900;
    today.month = lt->tm_mon + 1;
    today.day = lt->tm_mday;

    return today;
}

static const int DaysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static inline bool IsLeapYear(int year) { return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; }

int GetWeek(Date date)
{
    unsigned days = 0;
    for (int i = 1900; i < date.year; i++)
        days += IsLeapYear(i) ? 366 : 365;
    for (int i = 1; i < date.month; i++)
        days += DaysPerMonth[i];
    days += date.day - 1;
    if (date.month > 2 && IsLeapYear(date.year))
        days += 1;

    return (days + 1) % 7; // 加1是因为0算星期天，而1900年1月1日是星期一
}

static const wchar_t *CNWeeks[] = {L"天", L"一", L"二", L"三", L"四", L"五", L"六"};
static inline const wchar_t *GetCNWeek(Date date) { return CNWeeks[GetWeek(date)]; }

int main(void)
{
    setlocale(LC_ALL, "chs");
    Date today = GetToday();
    wprintf(L"今天的日期是： %d 年 %d 月 %d 日，星期%s。\n", today.year, today.month, today.day, GetCNWeek(today));

    Date date = SetDate(1901, 2, 1);
    wprintf(L"%s", GetCNWeek(date));

    // getchar();
    return 0;
}
