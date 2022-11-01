#include <stdio.h>

// 端序(字节序)：大于1字节的对象，如short，地址由小到大分配2字节，如果低位字节在前则为小端序，如果高位在前则为大端序
typedef union {
    unsigned short st;
    struct {
        unsigned char a;
        unsigned char b;
    };
} ByteOrder;

// 低位在前
typedef union {
    unsigned char ch;
    struct {
        unsigned char c0 : 1;
        unsigned char c1 : 1;
        unsigned char c2 : 1;
        unsigned char c3 : 1;
        unsigned char c4 : 1;
        unsigned char c5 : 1;
        unsigned char c6 : 1;
        unsigned char c7 : 1;
    };
} BitOrder;

int main(void) {
    ByteOrder bo;
    bo.st = 0xFF00;  // 00为低位，FF为高位
    if (bo.a == 0)   // 小端序
        printf("low(%p): %X high(%p): %X\n", &bo.a, bo.a, &bo.b, bo.b);

    BitOrder bito;
    bito.ch = 6;  // 0b110
    printf("%d %d %d %d\n",
           bito.c0, bito.c1, bito.c2, bito.c3);  // 0 1 1 0

    bito.ch = 7;  // 0b111
    printf("%d %d %d %d\n",
           bito.c0, bito.c1, bito.c2, bito.c3);  // 1 1 1 0

    bito.ch = 8;  // 0b1000
    printf("%d %d %d %d\n",
           bito.c0, bito.c1, bito.c2, bito.c3);  // 0 0 0 1
}
