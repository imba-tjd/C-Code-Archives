#include <limits.h>
#include <stdio.h>

#define PR(x) printf("%d\n", x)
typedef unsigned char uchar;

int main(void) {
    PR(INT_MAX);  // 2147483647

    PR(0xffff);       // 65535
    PR(0xffff >> 1);  // 32767

    PR(~0);        // -1
    PR(~0U);       // -1，因为全为1的无符号数按按%d输出
    PR(~0 >> 1);   // -1，保留负号
    PR(~0U >> 1);  // 2147483647

    PR(0x7fff);                       // 32767
    PR((unsigned short)0xffff >> 1);  // 32767
    PR((short)0xffff >> 1);           // -1，截断到short再保留符号提升到int再保留符号右移
}

void set1(uchar c, int ndx) { // ndx∈[0,7]
    c |= 1 << ndx;
}

void set0(uchar c, int ndx) {
    c &= ~(1 << ndx);
}

int hasn(uchar c, int ndx) {
    return c & 1 << ndx;  // 优先位移
}

uchar xor_(uchar a, uchar b) {   // 用&和|模拟^；异或相当于位的!=。不明白为什么函数名为xor时格式化会出问题
    return (a & ~b) | (~a & b);  // 不加括号也行
}

uchar not(uchar c) {
    return 1 ^ c;  // 当另一个数为1时，与c异或就相当于取反
}

uchar self(uchar c) {
    return 0 ^ c;  // 当另一个数为0时，与c异或还是c自己
}

int zero(uchar c) {
    return c ^ c;  // 归零律
}
