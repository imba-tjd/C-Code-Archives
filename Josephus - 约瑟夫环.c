/* 约瑟夫环问题
n个人围成一个圈，每个人分别标注为1、2、...、n，要求从1号从1开始报数，报到k的人出圈，接着下一个人又从1开始报数，如此循环，直到只剩最后一个人时，该人即为胜利者。
例如当n=10,k=4时，依次出列的人分别为4、8、2、7、3、10，9、1、6、5，则5号位置的人为胜利者。给定n个人，请你编程计算出最后胜利者标号数
*/
#include <stdio.h>
#define M 10

int main(void)
{
    // Initialization Array
    int n;
    int num[M];
    for (int i = 0; i < M; i++)
        num[i] = i + 1;

    scanf("%d", &n);

    // Solve
    int i = 0, t = 0, count = 0;
    while (count != M) // put all numbers
    {
        if (i == M - count) // loop array flag
            i = 0;

        if (t == n - 1)
        {
            printf("%d, ", num[i]);
            count++;
            t = 0;

            for (int j = i; j < M - count; j++) // refresh array
                num[j] = num[j + 1];
        }
        else
        {
            t++;
            i++;
        }
    }
    printf("\b\b.");
    return 0;
}
