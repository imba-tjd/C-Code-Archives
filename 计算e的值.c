// 计算e的值
#include <stdio.h>

int main(void)
{
    double cal_e(double e);
    int n;
    double e = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) // 计算要达到的精度
        e /= 10;
    printf("%f", cal(e));
    return 0;
}

double cal_e(double e)
{
    double s = 0;
    for (int i = 1, t = 1; 1; i++)
    {
        t *= i;
        s += 1.0 / t;
        if (e > 1.0 / t)
            return s;
    }
}
