// 试写出一算法，实现用开放定址法中线性探测再散列解决冲突的散列表查找功能。
// int hash_search(v,t) // v是查找的给定值，t为散列表
#include <stdbool.h>
#include <stdio.h>
#define MAXSIZE 8
#define INSERT(value) hash_insert(table, value)
#define SEARCH(value) hash_search(table, value)

int hash_insert(int table[], int value)
{
    int index, flag;
    index = flag = value % MAXSIZE;

    while (table[index] != 0)
    {
        index = (index + 1) % MAXSIZE;
        if (index == flag)
            return false;
    }

    table[index] = value;
    return true;
}

int hash_search(int table[], int value)
{
    int index, flag;
    index = flag = value % MAXSIZE;

    do
    {
        if (table[index] == value)
            return index;
        else
            index = (index + 1) % MAXSIZE;
    } while (index != flag);

    return -1;
}

int main(void)
{
    int table[MAXSIZE] = {0};
    INSERT(4);
    INSERT(28);
    INSERT(19);
    INSERT(8);
    INSERT(22);
    INSERT(14);
    INSERT(27);
    INSERT(25);

    printf("%d %d %d %d %d %d %d %d\n",
           SEARCH(4), SEARCH(28), SEARCH(19), SEARCH(8), SEARCH(22), SEARCH(14), SEARCH(27), SEARCH(25));

    return 0;
}