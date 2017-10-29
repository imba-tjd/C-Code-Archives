// https://my.oschina.net/Tsybius2014/blog/495953
// http://blog.csdn.net/coder_xia/article/details/6707600
// 只包含因子2、3和5的数称作丑数。1，2，3，4，5，6，8，9，10，12，15，16，18是最前面的13个丑数。

#include <stdio.h>

int main()
{
    int i;
    int n, count = 0, num;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &num);
        if (isUgly(num))
            count++;
    }
    printf("%d", count);
    return 0;
}

int isUgly(int num)
{
    if (num <= 0)
        return 0;

    while (num % 2 == 0)
        num /= 2;
    while (num % 3 == 0)
        num /= 3;
    while (num % 5 == 0)
        num /= 5;

    if (num == 1)
        return 1;
    else
        return 0;
}
