/* 寻找完数
 完数是特殊的自然数。它所有的真约数（即除了自身以外的约数）的和，恰好等于它本身。
 第一个完全数是6，它有约数1、2、3、6，除去它本身6外，其余3个数相加，1+2+3=6
 第二个完全数是28，它有约数1、2、4、7、14、28，除去它本身28外，其余5个数相加，1+2+4+7+14=28。
 要求：输入一个整数m，输出区间[1,m]内最大的完数。
 例如：输入32，输出28。*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int Maxperfect(int m);
    int m;
    scanf("%d", &m);
    printf("%d", MaxPerfect(m));
    return 0;
}

int MaxPerfect(int m)
{
    int Calc(int num);
    for (int i = m; i > 0; i--)
        if (Calc(i))
            return i;
    return 0;
}

int Calc(int num)
{
    int sum = 0;
    for (int i = 1; i < num; i++)
        if (num % i == 0)
            sum += i;
    if (sum == num)
        return 1;
    else
        return 0;
}
