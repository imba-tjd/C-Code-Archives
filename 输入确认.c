// C Primer Plus 8.7 checking.c -- 输入确认（有更改）
#include <stdbool.h>
#include <stdio.h>

int get_int(void);                                      // 确认输入了一个整数
bool bad_limits(int begin, int end, int low, int high); // 确认范围的上下界是否有效
double sum_squares(int a, int b);                       // 计算从a到b之间的平方和

int main(void) {
    const int MIN = -1000; // 范围的下界限制
    const int MAX = +1000; // 范围的上界限制

    printf("This program compute the sum of the squares of integers in a range.\n"
           "The lower bound shoul not be less than -1000 and the upper bound should not be more than +1000.\n");
    do {
        printf("Enter the limits (enter 0 for both limits to quit): \n");
        printf("lower limit: ");
        int start = get_int();
        printf("upper limit: ");
        int stop = get_int();
        if (start == 0 && stop == 0)
            break;

        if (bad_limits(start, stop, MIN, MAX))
            printf("Please try again.\n");
        else {
            double answer = sum_squares(start, stop);
            printf("The sum of the squares of the integers from");
            printf("from %d to %d is %g\n", start, stop, answer);
        }
    } while (true);
    printf("Done.\n");
    return 0;
}

int get_int(void) {
    int input;
    while (scanf("%d", &input) != 1) {
        char ch;
        while ((ch = getchar()) != '\n') // 剔除错误的输入
            putchar(ch);
        printf(" is not an integer.\n"
               "Please enter an integer value, such as 25, -178, or 3: ");
    }
    return input;
}

double sum_squares(int a, int b) {
    double total = 0;
    for (int i = a; i <= b; i++)
        total += i * i;
    return total;
}

bool bad_limits(int begin, int end, int low, int high) {
    bool not_good = false;
    if (begin > end) {
        printf("%d isn't smaller than %d.\n", begin, end);
        not_good = true;
    }
    if (begin < low || end < low) {
        printf("Values must be %d or greater.\n", low);
        not_good = true;
    }
    if (begin > high || end > high) {
        printf("Values must be %d or less.\n", high);
        not_good = true;
    }
    return not_good;
}
