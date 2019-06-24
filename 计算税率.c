#include <limits.h>
#include <stdio.h>

static const int Levels[] = {0, 3000, 5000, 10000, 15000, INT_MAX};
static const double Taxs[] = {0, 0.05, 0.08, 0.12, 0.2};

static int Filter(int num, int lower, int upper)
{
    return num <= upper ? num > lower ? num - lower : 0 : upper - lower;
}

int Sumtax(int num)
{
    int sum = 0;

    for (int i = 0; i < 5; i++)
        sum += Filter(num, Levels[i], Levels[i + 1]) * Taxs[i];

    return sum;
}

int main(void)
{
    int num;

    scanf("%d", &num);
    printf("%d\n", Sumtax(num));

    return 0;
}
