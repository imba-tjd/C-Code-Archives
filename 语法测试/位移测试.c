#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PR(x) printf("%d\n", x)

int main(void) {
    PR(INT_MAX); // 2147483647

    PR(0xffff);      // 65535
    PR(0xffff >> 1); // 32767

    PR(~0);       // -1
    PR(~0U);      // -1
    PR(~0U >> 1); // 2147483647

    PR(0x7fff);                      // 32767
    PR((unsigned short)0xffff >> 1); // 32767
    PR((short)0xffff >> 1);          // -1
}
