// 不是我写的代码，但当时没记录出处。至少23!的计算结果与百度一致。
// 如果直接循环乘，用double只能坚持到21，从22开始就会开始进行舍入；long double能坚持到22，但23位时不精确的部分会发生奇怪的变化
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int Data[40] = {1, 1}; /*Store the 40 bit data*/
    int Digit = 1;
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= Digit; j++)
            Data[j] *= i;

        for (int j = 1; j <= Digit; j++)
            if (Data[j] > 10)
                for (int r = 1; r <= Digit; r++) {
                    if (Data[Digit] > 10)
                        Digit++;

                    Data[r + 1] += Data[r] / 10;
                    Data[r] = Data[r] % 10;
                }

        printf("%d!=", i);

        for (int k = Digit; k > 0; k--)
            printf("%d", Data[k]);

        printf("\n");
    }
}
/* 输出：
1!=1
2!=2
3!=6
4!=24
5!=120
*/
