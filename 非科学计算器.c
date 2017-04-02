//非科学计算器
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    double a, b, d;
    char op;
    scanf("%lf%c%lf",&a, &op, &b);
    switch (op) {
      case  '+' :  d=a+b; break;
      case  '-':   d=a-b; break;
      case  '*':   d=a*b; break;
      case  '/':   if (b!=0){ d=a/b; break;}
      default:  printf("Error\n");
                exit(0);
    }
    printf("=%.2f\n",d);
    return 0;
}