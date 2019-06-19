/* https://zhidao.baidu.com/question/1373274175506565859.html
给定两个仅由大写字母或小写字母组成的字符串(长度介于1到10之间)，它们之间的关系是以下4中情况之一：
1：两个字符串长度不等。比如 Beijing 和 Hebei。
2：两个字符串不仅长度相等，而且相应位置上的字符完全一致(区分大小写)，比如 Beijing 和 Beijing。
3：两个字符串长度相等，相应位置上的字符仅在不区分大小写的前提下才能达到完全一致（也就是说，它并不满足情况2）。比如 beijing 和 BEIjing。
4：两个字符串长度相等，但是即使是不区分大小写也不能使这两个字符串一致。比如 Beijing 和 Nanjing。
编程判断输入的两个字符串之间的关系属于这四类中的哪一类，给出所属的类的编号。
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

static inline bool EitherEnd(char a, char b) { return a == '\0' || b == '\0'; }

static inline bool BothEnd(char a, char b) { return a == '\0' && b == '\0'; }

static inline bool Equals(char a, char b) { return a == b; }

static inline bool EqualsIgnoreCase(char a, char b)
{
    static const int DISTANCE = 'a' - 'A';
    return a == b || a + DISTANCE == b || a == b + DISTANCE;
}

#define ARGS str1[i], str2[i]

int SwitchCompare(char *str1, char *str2)
{
    int status = 2;

    for (int i = 0; !BothEnd(ARGS); i++)
    {
        switch (status)
        {
        case 2:
        {
            if (!Equals(ARGS))
                status = 3;
        }
        case 3:
        {
            if (!EqualsIgnoreCase(ARGS))
                status = 4;
        }
        case 4:
        {
            if (EitherEnd(ARGS))
                return 1;
        }
        }
    }

    return status;
}

int LoopCompare(char *str1, char *str2)
{
    int status = 2;
    for (int i = 0; !BothEnd(ARGS); i++)
    {
        if (status == 2 && !Equals(ARGS))
            status = 3;
        if (status == 3 && !EqualsIgnoreCase(ARGS))
            status = 4;
        if (status == 4 && EitherEnd(ARGS))
        {
            status = 1;
            break;
        }
    }
    return status;
}

typedef struct
{
    char str1[10];
    char str2[10];
} Case;

void AssertOnce(Case _case, int expect, int (*callback)(char *str1, char *str2))
{
    int status;
    status = callback(_case.str1, _case.str2);
    assert(status == expect);
}

void Test(void)
{
    Case cases[4] = {
        {"Beijing", "Hebei"},
        {"Beijing", "Beijing"},
        {"beijing", "BEIjing"},
        {"Beijing", "Nanjing"},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(*cases); i++)
    {
        AssertOnce(cases[i], i + 1, &SwitchCompare);
        AssertOnce(cases[i], i + 1, &LoopCompare);
    }
}

int main(void)
{
    Test();

    char str1[11], str2[11];
    scanf("%s %s", str1, str2);

    int s1, s2;
    s1 = SwitchCompare(str1, str2);
    s2 = SwitchCompare(str1, str2);

    printf("%d %d\n", s1, s2);

    return 0;
}
