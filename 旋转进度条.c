#include <stdio.h>
#include <unistd.h> // posix的sleep

const char *Characters = "-\\|/";

int main(void)
{
    for (int i = 0; i <= 10; i++)
    {
        printf("%c (%-3d%%)", Characters[i % 4], i * 10);
        fflush(stdout);
        sleep(1);
        printf("\r");
    }
    printf("\n");
}
