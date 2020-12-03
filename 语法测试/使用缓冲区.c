// 《C陷阱与缺陷》
// 使用“不对称边界”，bufptr指向的就是下一个应该被写入的节点，(bufptr - buffer)即是已有数据的节点的个数

#define N 30
char buffer[N], *bufptr = buffer;
void flusshbuffer(){} // 仅为示意

void mymemcpy(char *dest, const char *src, int k) {
    while (k-- > 0)
        *dest++ = *src++;
}

void bufwrite(char *src, int n) {
    while (n > 0) {
        if (bufptr == &buffer[N]) // 使用最后一个元素的后一个元素的地址是允许的
            flusshbuffer();

        int rem = N - (bufptr - buffer); // 或 (buffer + N) - bufptr
        int k = n > rem ? rem : n;
        mymemcpy(bufptr, src, k);

        bufptr += k;
        src += k;
        n -= k;
    }
    flusshbuffer();
}
