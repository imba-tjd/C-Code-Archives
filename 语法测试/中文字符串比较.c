// 测试字符串能否按拼音顺序比较：啊 吧 从 的 额
// 测试结果：Win下GBK+UCRT无需任何设置，strcmp就能按拼音比较，wcscmp无论怎么设置都无法按拼音比较
// 有一种说法是 GB2312里一级汉字是按拼音排序的，其他的汉字按部首/笔划排序，所以能按拼音排序的汉字只有3000多个
// 还发现VSC的debug的watch中无法添加strcmp()的调用
// Linux无论怎么设置都全失败

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>

void test_strcmp(void) {
    assert(strcmp("吧", "啊") == 1);
    assert(strcmp("从", "吧") == 1);
    assert(strcmp("的", "从") == 1);
    assert(strcmp("额", "的") == 1);
    assert(strcmp("啊", "从") == -1);
    assert(strcmp("吧", "的") == -1);
    assert(strcmp("从", "额") == -1);
}

void test_strcoll(void) {
    assert(strcoll("吧", "啊") == 1);
    assert(strcoll("从", "吧") == 1);
    assert(strcoll("的", "从") == 1);
    assert(strcoll("额", "的") == 1);
    assert(strcoll("啊", "从") == -1);
    assert(strcoll("吧", "的") == -1);
    assert(strcoll("从", "额") == -1);
}

void test_wcscmp(void) {
    assert(wcscmp(L"吧", L"啊") == 1);
    assert(wcscmp(L"从", L"吧") == 1);
    assert(wcscmp(L"的", L"从") == 1);
    assert(wcscmp(L"额", L"的") == 1);
    assert(wcscmp(L"啊", L"从") == -1);
    assert(wcscmp(L"吧", L"的") == -1);
    assert(wcscmp(L"从", L"额") == -1);
}

int main(void) {
#ifdef linux
    setlocale(LC_ALL, "zh_CN.UTF-8");
#else
    setlocale(LC_ALL, "");  // Chinese (Simplified)_China.936
#endif

    puts(setlocale(LC_ALL, NULL));
    test_strcmp();
    test_strcoll();
    test_wcscmp();
}
