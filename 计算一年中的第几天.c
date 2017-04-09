// 计算一年中的第几天
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int y,m,d,sum=0;
    scanf("%d-%d-%d", &y, &m, &d);
    switch(m-1){
        default: printf("input month is error! \n"); exit(0);
        case 11: sum += 30;
        case 10: sum += 31;
        case 9: sum += 30;
        case 8: sum += 31;
        case 7: sum += 31;
        case 6: sum += 30;
        case 5: sum += 31;
        case 4: sum += 30;
        case 3: sum += 31;
        case 2: if(y%4 == 0 && y%100 !=0 || y%400 == 0)
                    sum += 29;
                else
                    sum += 28;
        case 1: sum += 31;
    }
    sum += d;
    printf("%d\n", sum);
    return 0;
}