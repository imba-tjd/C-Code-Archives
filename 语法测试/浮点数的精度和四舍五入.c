// http://tieba.baidu.com/p/5442657055
// https://rationmcu.com/clang/2416.html
// http://bbs.csdn.net/topics/70084538/
// http://bbs.csdn.net/topics/390321157

#include <stdio.h>

int main(void) {
    double a1, a2, a3, a4, a5, a6, a7;

    a1 = 0.555;
    a2 = 1.555;
    a3 = 2.555;
    a4 = 3.555;
    a5 = 4.555;
    a6 = 5.555;
    a7 = 6.555;
    printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f\n", // 当想要保留两位小数时
           a1, a2, a3, a4, a5, a6, a7);
    // 0.56 1.55 2.56 3.56 4.55 5.55 6.55
    // 有的会”四舍五入“，有的不会

    // “加0.5”的方法
    printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
           a1 + 0.005, a2 + 0.005, a3 + 0.005, a4 + 0.005, a5 + 0.005, a6 + 0.005, a7 + 0.005);
    // 0.56 1.56 2.56 3.56 4.56 5.56 6.56
    // 看起来成功四舍五入了，然而：

    a1 = 0.554;
    a2 = 1.554;
    a3 = 2.554;
    a4 = 3.554;
    a5 = 4.554;
    a6 = 5.554;
    a7 = 6.554;
    printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
           a1 + 0.005, a2 + 0.005, a3 + 0.005, a4 + 0.005, a5 + 0.005, a6 + 0.005, a7 + 0.005);
    // 0.56 1.56 2.56 3.56 4.56 5.56 6.56
    // 本来此时不应该四舍五入的
    // 总之结论是不要直接依靠printf的精度来四舍五入。也许加0.5对于四舍五入到整数是可用的

    // 解决办法：
    double Round(double num, unsigned digit);
    printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
           Round(a1, 2), Round(a2, 2), Round(a3, 2), Round(a4, 2), Round(a5, 2), Round(a6, 2), Round(a7, 2));
}

// 未处理负数，理论上去掉负号计算完再加上即可
double Round(double num, unsigned digit) {
    int resize = 1;
    for (unsigned i = 0; i < digit; i++)
        resize *= 10; // 可以用pow替代

    // 利用 (int)(1.4+0.5) == 1；(int)(1.5+0.5) == 2
    // 分子的两个强转也可用math.h的floor替代，或者整个分子都可以用round(num*resize)替代
    // 虽然还是不懂0.15本来是0.14999但*10后就完全是1.5了
    return (double)((int)(num * resize + 0.5)) / resize;
}
