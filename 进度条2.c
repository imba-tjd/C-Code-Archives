#include <stdio.h>
#include <unistd.h>

const int WIDTH = 25;
const char *BLANK = "";

int main(void)
{
    for (int i = 0; i <= 100; i += 1) // 进度
    {
        static int position = 0;
        static int lefttoright = 1;

        printf("[%*s<=>%-*s]", position, BLANK, WIDTH - position - 3, BLANK);
        fflush(stdout);

        usleep(200000LL);

        if (lefttoright)
        {
            if (position++ == WIDTH - 3)
            {
                lefttoright = 0;
                position -= 2;
            }
        }
        else
        {
            if (--position == -1)
            {
                lefttoright = 1;
                position += 2;
            }
        }

        printf("\r");
    }
}
