/* 进制转换：输入一个十进制数N，将它转换成R进制数输出。

输入样例
7 2
23 12
-4 3

输出样例
111
1B
-11
*/

#include <stdio.h>

static int R;

void convert(int a) {
    if (a >= R)
        convert(a / R);  // 先递归后输出，倒序

    char ch = a % R;
    putchar(ch < 10 ? ch + '0' : ch + 'A' - 10);  // 10才对应A
}

int main(void) {
    int N;
    scanf("%d %d", &N, &R);

    if (N < 0)
        putchar('-');
    convert(N >= 0 ? N : -N);
    putchar('\n');
}
