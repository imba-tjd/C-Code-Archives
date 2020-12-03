// 不是我写的代码，但当时没记录出处。
// 如果用double来记录，直接循环乘，只能坚持到21，从22开始就会开始进行舍入；long double能坚持到22，但23位时不精确的部分会发生奇怪的变化
// 而且百度、Google、bing的结果都是这样算的
#include <stdio.h>
#include <stdlib.h>

int main(void) {
   int Data[40] = {0}; /*Store the 40 bit data*/
   int Digit;
   int N;

   Data[0] = Data[1] = 1;
   Digit = 1;

   scanf("%d", &N);

   for (int i = 1; i < N + 1; i++) {
      for (int j = 1; j < Digit + 1; j++)
         Data[j] *= i;

      for (int j = 1; j < Digit + 1; j++)
         if (Data[j] > 10)
            for (int r = 1; r < Digit + 1; r++) {
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
Please Enter a number what you want to calculus:5
1!=1
2!=2
3!=6
4!=24
5!=120
*/
