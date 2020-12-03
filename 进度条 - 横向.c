#include <stdio.h>
#include <unistd.h>

const int WIDTH = 25;
#define BLANK ""

int main(void) {
    int position = 0;
    int lefttoright = 1; // 当前正从左往右还是从右往左的flag
    for (int i = 0; i <= 100; i += 1) {
        printf("[%*s<=>%-*s]", position, BLANK, WIDTH - position - 3, BLANK);
        fflush(stdout);

        usleep(200000); // 0.2秒

        if (lefttoright) {
            if (position++ == WIDTH - 3) {
                lefttoright = 0;
                position -= 2;
            }
        } else {
            if (--position == -1) {
                lefttoright = 1;
                position += 2;
            }
        }

        putchar('\r');
    }
    putchar('\n');
}
