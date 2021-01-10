#include <limits.h>
#include <stdio.h>

// 0-3000对应0
static const int Levels[] = {0, 3000, 5000, 10000, 15000, INT_MAX};
static const double Taxs[] = {0, 0.05, 0.08, 0.12, 0.2};

// num-lower但不低于0且不高于upper
static int filter(int num, int lower, int upper) {
    return num > upper ? upper - lower:
            num > lower ? num - lower : 0;
}

int tax_sum(int num) {
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += filter(num, Levels[i], Levels[i + 1]) * Taxs[i];
    return sum;
}

int main(void) {
    int num;
    scanf("%d", &num);
    printf("%d\n", tax_sum(num));
}
