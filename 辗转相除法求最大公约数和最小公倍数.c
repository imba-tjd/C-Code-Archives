// 辗转相除法求最大公约数和最小公倍数
#include <stdio.h>

int main(void)
{
  int m, n, r, p, gcd, lcm;
  scanf("%d%d", &m, &n);
  p = m * n;
  r = m % n;
  while (r != 0)
  {
    m = n;
    n = r;
    r = m % n;
  }
  gcd = n;
  lcm = p / gcd;
  printf("gcd=%d, lcm=%d\n", gcd, lcm);
  return 0;
}
