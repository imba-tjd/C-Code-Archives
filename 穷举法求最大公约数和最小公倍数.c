//穷举法求最大公约数和最小公倍数
#include <stdio.h>

int max(int a, int b)
{
    return a > b ?a:b;
}

int min(int a, int b)
{
    return a < b ?a:b;
}

int ys(int x,int y)
{
    int i, a, b;
    b=max(x, y);
    a=min(x, y);
    for(i=a;i >= 1;i--)
        if(a%i == 0 && b%i == 0)
            return i;
    return 1;
}

int bs(int x,int y)
{
    int i, a, b;
    b=max(x, y);
    a=min(x, y);
    for(i=b;i <= a*b;i++)
        if(i%b == 0 && i%a == 0)
            return i;
    return a*b;
}

int main(void)
{
    int x, y;
    scanf("%d%d", &x, &y);
    printf("%d %d", ys(x,y), bs(x,y));
    return 0;
}