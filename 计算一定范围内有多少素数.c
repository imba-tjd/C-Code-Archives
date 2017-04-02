//计算一定范围内有多少素数
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int n=0,count=0;
    printf("This program is used to count how many prime numbers are there and print them, from 2 to your input number.\n\
Just input a number:");
    scanf("%d", &n);
    for(int i=2,flag=1;i<=n;i++,flag=1)
    {
        for(int j=2; j*j<=i;j++)
        {
            if (i%j==0)
            {
                flag=0;
                break;
            }
        }
        if (flag==1)
        {
            printf("%d\n", i);
            count++;
        }
    }
    printf("total:%d\n",count);
    return 0;
}