// 生成四位互不相同的四位数
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    for (int i = 1; i < 5; i++) //以下为四重循环
        for (int j = 1; j < 5; j++)
            for (int k = 1; k < 5; k++)
                for (int l = 1; l < 5; l++)
                {
                    if (i != k && i != j && i != l && j != k && j != l && l != k) //确保i、j、k，l四位互不相同
                        printf("%d%d%d%d\n", i, j, k, l);
                }
}
