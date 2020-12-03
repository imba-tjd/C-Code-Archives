// 《C语言解惑》
// 逻辑操作符的阻断特性

// #pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wunused-value"
#include <stdio.h>

#define PRINT3(x, y, z) printf(#x "=%d " #y "=%d " #z "=%d\n", x, y, z)

int main(void) {
    int x, y, z;
    x = y = z = 1;
    ++x || ++y && ++z;
    PRINT3(x, y, z);
    // x=2 y=1 z=1

    x = y = z = 1;
    ++x && ++y || ++z;
    PRINT3(x, y, z);
    // x=2 y=2 z=1

    x = y = z = -1;
    ++x || ++y && ++z;
    PRINT3(x, y, z);
    // x=0 y=0 z=-1

    x = y = z = -1;
    ++x && ++y || ++z;
    PRINT3(x, y, z);
    // x=0 y=0 z=-1
}
// #pragma GCC diagnostic pop
