// 先输入你接下来要输入多少个数，然后输入一些数，要求输出那些奇数的累积，如果没有奇数就输出0
#include <stdio.h>

int main(void)
{
    int n, multi, k, flag;

    while (scanf("%d", &n) != EOF)
    {
        flag = 0;
        multi = 1;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &k);
            if (k % 2 != 0)
            {
                multi *= k;
                flag = 1;
            }
        }
        printf("%d\n", flag * multi);
    }
    return 0;
}
