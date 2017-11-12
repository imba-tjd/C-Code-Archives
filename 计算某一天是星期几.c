// 计算某一天是星期几
// 以1900年1月1日星期一为基准
// 获取当前的时间代码来源：https://zhidao.baidu.com/question/17712149.html

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

typedef struct
{
    int year;
    int month;
    int day;
} Date;

static const int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const wchar_t *CNWeeks[] = {L"天", L"一", L"二", L"三", L"四", L"五", L"六"};

Date SetDate(int year, int month, int day);
Date GetToday(void);
bool IsLeapYear(int year);
int GetWeek(Date date);
wchar_t *GetCNWeek(Date date);

Date SetDate(int year, int month, int day)
{
    Date date;
    date.year = year;
    date.month = month;
    date.day = day;
    return date;
}

Date GetToday(void)
{
    Date today;

    struct tm *lt;
    time_t tt;
    time(&tt);
    lt = localtime(&tt);

    today.year = lt->tm_year + 1900;
    today.month = lt->tm_mon + 1;
    today.day = lt->tm_mday;

    return today;
}

bool IsLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int GetWeek(Date date)
{
    int baseWeek = 1;
    int days = 0;
    for (int i = 1900; i < date.year; i++)
        days += IsLeapYear(i) ? 366 : 365;
    for (int i = 1; i < date.month; i++)
        days += daysPerMonth[i];
    days += date.day - 1;
    if (date.month > 2 && IsLeapYear(date.year))
        days += 1;

    days %= 7;
    baseWeek += days;
    if (baseWeek > 7)
        baseWeek -= 7;
    return baseWeek;
}

wchar_t *GetCNWeek(Date date)
{
    return (wchar_t *)CNWeeks[GetWeek(date)];
}

int main(void)
{
    setlocale(LC_ALL, "chs");
    Date Today = GetToday();
    wprintf(L"今天的日期是： %d 年 %d 月 %d 日，星期%s。\n", Today.year, Today.month, Today.day, GetCNWeek(Today));

    Date date = SetDate(1901, 2, 1);
    wprintf(L"%s", GetCNWeek(date));

    getchar();
    return 0;
}
