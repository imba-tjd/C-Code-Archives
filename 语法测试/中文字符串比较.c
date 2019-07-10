#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void normalCmp(void);
void wideCmp(void);

int main(void)
{
    setlocale(LC_ALL, "chs");

    // 因为我的代码用的是UTF8编码，这部分的硬编码字符串也是，此时strcmp无意义；而手动输入是能正常比较的
    // printf("%d\n", strcmp("赵六", "王五")); // 1
    // printf("%d\n", strcmp("王五", "李四")); // 1
    // printf("%d\n", strcmp("李四", "张三")); // 1

    // 输入赵六 王五 李四 张三：
    normalCmp(); // 李四 王五 张三 赵六，符合拼音顺序
    // putchar('\n');

    wprintf(L"%d\n", wcscmp(L"赵六", L"王五")); // 1
    wprintf(L"%d\n", wcscmp(L"王五", L"李四")); // 1
    wprintf(L"%d\n", wcscmp(L"李四", L"张三")); // 1
    putchar('\n');

    // wideCmp(); // 张三 李四 王五 赵六

    return 0;
}

/*
而且还有更诡异的事情：
Win下的vscode的debug的watch中加一个 `strcmp("你好","你好")` 或者 `strcmp("123","456")` 会直接导致gdb崩溃退出；Linux下有效。
Linux下那六个直接比较，只会输出三个1，而注释掉任意一组也还是三个1；normalCmp的结果是 张三 李四 王五 赵六，wideCmp没有输出！
曾经还出现过clang和gcc结果不同、`strcmp("李四", "张三")` 为1但 `strcmp("张三"，"李四")` 不为-1的情况
*/

#define MAXSIZE 20
#define N 4

void normalCmp(void)
{
    printf("Not Wide: ");

    char sn[N][MAXSIZE], t[MAXSIZE];
    for (int i = 0; i < N; i++)
        scanf("%s", sn[i]);

    for (int i = 0; i < N - 1; i++)
    {
        int k = i; // 选择排序
        for (int j = i + 1; j < N; j++)
            if (strcmp(sn[j], sn[k]) < 0) // 从大到小排序，但结果确是拼音从前往后排的
                k = j;

        strcpy(t, sn[i]);
        strcpy(sn[i], sn[k]);
        strcpy(sn[k], t);
    }

    putchar('\n');
    for (int i = 0; i < N; i++)
        printf("%s ", sn[i]);
    putchar('\n');
}

void wideCmp(void)
{
    wprintf(L"Wide: ");

    wchar_t sn[N][MAXSIZE], t[MAXSIZE];
    for (int i = 0; i < N; i++)
        wscanf(L"%s", sn[i]);

    for (int i = 0; i < N - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < N; j++)
            if (wcscmp(sn[j], sn[k]) < 0)
                k = j;

        wcscpy(t, sn[i]);
        wcscpy(sn[i], sn[k]);
        wcscpy(sn[k], t);
    }

    putchar('\n');
    for (int i = 0; i < N; i++)
        wprintf(L"%s ", sn[i]);
    putchar('\n');
}
