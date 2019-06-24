// https://my.oschina.net/Tsybius2014/blog/495953
// http://blog.csdn.net/coder_xia/article/details/6707600
// 只包含因子2、3和5的数称作丑数。1，2，3，4，5，6，8，9，10，12，15，16，18是最前面的13个丑数。
#include <stdbool.h>
#include <stdio.h>

bool isUgly(int num)
{
    if (num <= 0)
        return false;

    while (num % 2 == 0)
        num /= 2;
    while (num % 3 == 0)
        num /= 3;
    while (num % 5 == 0)
        num /= 5;

    return num == 1;
}

int main(void)
{
    int n, count;
    count = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int num;
        scanf("%d", &num);

        if (isUgly(num))
            count++;
    }

    printf("%d\n", count);
    return 0;
}
