/* https://zhidao.baidu.com/question/1373274175506565859.html
给定两个仅由大写字母或小写字母组成的字符串(长度介于1到10之间)，它们之间的关系是以下4中情况之一：
1：两个字符串长度不等。比如 Beijing 和 Hebei。
2：两个字符串不仅长度相等，而且相应位置上的字符完全一致(区分大小写)，比如 Beijing 和 Beijing。
3：两个字符串长度相等，相应位置上的字符仅在不区分大小写的前提下才能达到完全一致（也就是说，它并不满足情况2）。比如 beijing 和 BEIjing。
4：两个字符串长度相等，但是即使是不区分大小写也不能使这两个字符串一致。比如 Beijing 和 Nanjing。
编程判断输入的两个字符串之间的关系属于这四类中的哪一类，给出所属的类的编号。

严格程度依次是2341。本代码实现了两种方式，但其实本质上就是一种。
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

static inline bool EitherEnd(char a, char b) { return a == '\0' || b == '\0'; }
static inline bool BothEnd(char a, char b) { return a == '\0' && b == '\0'; }
static inline bool Equals(char a, char b) { return a == b; }
static inline bool EqualsIgnoreCase(char a, char b) {
    static const int DISTANCE = 'a' - 'A';
    return a == b || a + DISTANCE == b || a == b + DISTANCE;
}

#define ARGS str1[i], str2[i]

int SwitchCompare(const char *str1, const char *str2) {
    int status = 2;
    for (int i = 0; !BothEnd(ARGS); i++) {
        switch (status) {
        case 2: {
            if (!Equals(ARGS))
                status = 3;  // 要继续测试case 3
            else
                continue;
        }
        case 3: {
            if (!EqualsIgnoreCase(ARGS))
                status = 4;
            else
                continue;
        }
        case 4: {
            if (EitherEnd(ARGS))
                return 1;  // 不能像另一种一样break出循环，因为在switch里
        }
        }
    }
    return status;
}

int LoopCompare(const char *str1, const char *str2) {
    int status = 2;
    for (int i = 0; !BothEnd(ARGS); i++) {
        if (status == 2 && !Equals(ARGS))
            status = 3;
        if (status == 3 && !EqualsIgnoreCase(ARGS))
            status = 4;
        if (status == 4 && EitherEnd(ARGS)) {
            status = 1;
            break;
        }
    }
    return status;
}

void Test(void) {
    typedef struct {
        const char *str1;
        const char *str2;
    } Case;

    Case cases[4] = {
        // 注意case是关键字，要么用_case；因为四个测试用例刚好和状态对应，就硬编码长度了
        {"Beijing", "Hebei"},
        {"Beijing", "Beijing"},
        {"beijing", "BEIjing"},
        {"Beijing", "Nanjing"},
    };

    for (int i = 0; i < 4; i++) {
        assert(i + 1 == SwitchCompare(cases[i].str1, cases[i].str2));
        assert(i + 1 == LoopCompare(cases[i].str1, cases[i].str2));
    }
    puts("Tests passed.");
}

int main(void) {
    Test();  // 自动测试

    // 手动使用
    char str1[11], str2[11];
    scanf("%s %s", str1, str2);

    int s1, s2;
    s1 = SwitchCompare(str1, str2);
    s2 = SwitchCompare(str1, str2);

    printf("%d %d\n", s1, s2);
}
