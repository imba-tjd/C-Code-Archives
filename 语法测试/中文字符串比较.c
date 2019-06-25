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

    printf("%d\n", strcmp("赵六", "王五")); // 1
    printf("%d\n", strcmp("王五", "李四")); // 1
    printf("%d\n", strcmp("李四", "张三")); // 1
    putchar('\n');

    wprintf(L"%d\n", wcscmp(L"赵六", L"王五")); // 1
    wprintf(L"%d\n", wcscmp(L"王五", L"李四")); // 1
    wprintf(L"%d\n", wcscmp(L"李四", L"张三")); // 1
    putchar('\n');

    // 所以输入赵六 王五 李四 张三，输出顺序应该不会变
    // 可实际上，Win下非宽字符输出顺序，为李四 王五 张三 赵六；宽字符输出顺序为张三 李四 王五 赵六，都变了
    // 我猜测与输入有关，即输入和编译进去的字符串不一样。

    normalCmp();
    wideCmp();

    return 0;
}

/*
而且还有更诡异的事情：
Win下的vscode的debug的watch中加一个 `strcmp("你好","你好")` 或者 `strcmp("123","456")` 会直接导致gdb崩溃退出；Linux下有效。
Linux下那六个直接比较，只会输出三个1，而注释掉任意一组也还是三个1；normalCmp的结果是 张三 李四 王五 赵六，wideCmp没有输出！
曾经还出现过clang和gcc结果不同、`strcmp("李四", "张三")` 为1但 `strcmp("张三"，"李四")` 不为-1的情况
总之，我暂时的结论就是，不要在C语言里写中文！
*/

#define MAXSIZE 20
#define N 4

void normalCmp(void)
{
    printf("not wide\n");

    char sn[N][MAXSIZE], t[MAXSIZE];
    for (int i = 0; i < N; i++)
        scanf("%s", sn[i]);

    for (int i = 0; i < N - 1; i++)
    {
        int k = i; // 选择排序
        for (int j = i + 1; j < N; j++)
            if (strcmp(sn[j], sn[k]) < 0) // 从大到小排序
                k = j;

        strcpy(t, sn[i]);
        strcpy(sn[i], sn[k]);
        strcpy(sn[k], t);
    }

    printf("\n");
    for (int i = 0; i < N; i++)
        printf("%s\n", sn[i]);
}

void wideCmp(void)
{
    wprintf(L"wide\n");

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

    printf("\n");
    for (int i = 0; i < N; i++)
        wprintf(L"%s\n", sn[i]);
}
