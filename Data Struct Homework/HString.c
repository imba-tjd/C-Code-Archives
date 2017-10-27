// 试写一算法，在串的堆分配存储结构上实现串的连接操作Concat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *ch;
    int length;
} HString;

HString CreateHString(char *string);
HString HConcat(HString hs1, HString hs2);

HString CreateHString(char *string)
{
    HString hs;
    hs.length = strlen(string);
    hs.ch = (char *)malloc(sizeof(char) * (hs.length + 1));
    strcpy(hs.ch, string);
    return hs;
}

HString HConcat(HString hs1, HString hs2)
{
    char *ch = (char *)malloc(sizeof(char) * (hs1.length + hs2.length + 1));
    strcpy(ch, hs1.ch);
    strcat(ch, hs2.ch);
    return CreateHString(ch);
}

int main(void)
{
    HString hs1, hs2, hs3;

    hs1 = CreateHString("Hello");
    hs2 = CreateHString(" World!");
    hs3 = HConcat(hs1, hs2);

    printf("%s\n", hs1.ch);
    printf("%s\n", hs2.ch);
    printf("%s\n", hs3.ch);

    return 0;
}