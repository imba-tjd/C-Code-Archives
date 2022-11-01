// https://tieba.baidu.com/p/8110443070

#include <stdio.h>

int main(void) {
    // glibc和ucrt遵循“四舍六入五成双”，msvcrt遵循“四舍五入”
    printf("%.f %.f %.f %.f %.f %.f\n", 0.5, 1.5, 2.5, 3.5, 4.5, 5.5);  // 0 2 2 4 4 6

    // 但是浮点有误差，出现多于一位的小数时只有0.375这种能精确表示的才会确定变成0.38
    printf("%.1f %.1f %.1f %.1f %.1f %.1f\n", 0.05, 1.05, 2.05, 3.05, 4.05, 5.05);  // 0.1 1.1 2.0 3.0 4.0 5.0
    printf("%.1f %.1f %.1f %.1f %.1f %.1f\n", 0.15, 1.15, 2.15, 3.15, 4.15, 5.15);  // 0.1 1.1 2.1 3.1 4.2 5.2

    // 保留两位小数的情形
    double a0, a1, a2, a3, a4, a5;
    a0 = 0.555, a1 = 1.555, a2 = 2.555, a3 = 3.555, a4 = 4.555, a5 = 5.555;
    printf("%.2f %.2f %.2f %.2f %.2f %.2f\n", a0, a1, a2, a3, a4, a5);
    // 0.56 1.55 2.56 3.56 4.55 5.55

    // 解决办法

    // 四舍五入：加0.5。保留两位小数时加0.005
    printf("%.2f %.2f %.2f %.2f %.2f %.2f\n",
           a0 + 0.005, a1 + 0.005, a2 + 0.005, a3 + 0.005, a4 + 0.005, a5 + 0.005);
    // 0.56 1.56 2.56 3.56 4.56 5.56

    // 截断：
    double Floor(double num, unsigned digit);
    printf("%.2f %.2f %.2f %.2f %.2f %.2f\n",
           Floor(a0, 2), Floor(a1, 2), Floor(a2, 2), Floor(a3, 2), Floor(a4, 2), Floor(a5, 2));
}

// 未处理负数，理论上去掉负号计算完再加上即可
double Floor(double num, unsigned digit) {
    int resize = 1;
    for (unsigned i = 0; i < digit; i++)
        resize *= 10;  // 可以用pow替代

    // 利用 (int)(1.4+0.5) == 1；(int)(1.5+0.5) == 2
    // 分子的两个强转也可用math.h的floor替代，或者整个分子都可以用round(num*resize)替代
    // 虽然还是不懂0.15本来是0.14999但*10后就完全是1.5了
    return (double)((int)(num * resize + 0.5)) / resize;
}
