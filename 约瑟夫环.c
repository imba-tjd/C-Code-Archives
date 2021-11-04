/* Josephus 约瑟夫环问题
n个人围成一个圈，每个人分别标注为1、2、...、n，要求从1号从1开始报数，报到k的人出圈，接着下一个人又从1开始报数，如此循环，直到只剩最后一个人时，该人即为胜利者。
例如当n=10,k=4时，依次出列的人分别为4、8、2、7、3、10，9、1、6、5，则5号位置的人为胜利者。给定n个人，请你编程计算出最后胜利者标号数 */

#include <stdio.h>
#define N 10

int main(void) {
    int num[N];
    for (int i = 0; i < N; i++)
        num[i] = i + 1;

    int k;
    scanf("%d", &k);

    int i = 0, cnt = 1, out = 0;  // 分别代表 当前位置，本轮报到多少，出圈几个人
    while (out != N) {
        if (i == N - out)  // 循环下标
            i = 0;

        if (cnt == k) {
            printf("%d ", num[i]);

            out++;
            cnt = 1;

            for (int j = i; j < N - out; j++)  // 去掉那个人，往前移
                num[j] = num[j + 1];
        } else
            cnt++, i++;
    }
}
