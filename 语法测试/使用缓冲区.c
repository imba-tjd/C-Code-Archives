// 《C陷阱与缺陷》
// 使用“不对成边界”，bufptr指向的就是下一个应该被写入的节点，(bufptr - buffer)即是已有数据的节点的个数

#define N 30
char buffer[N], *bufptr = buffer;
void flusshbuffer(); // 去掉警告

void newmemcpy(char *dest, const char *source, int k)
{
    while (--k > 0)
        *dest++ = *source++;
}

void bufwrite(char *p, int n)
{
    int k, rem;
    while (n > 0)
    {
        if (bufptr == &buffer[N]) // 使用最后一个元素的后一个元素的地址是允许的
            flusshbuffer();

        rem = N - (bufptr - buffer); // 或 (buffer + N) - bufptr
        k = n > rem ? rem : n;
        newmemcpy(bufptr, p, k);

        bufptr += k;
        p += k;
        n -= k;
    }
    flusshbuffer();
}
