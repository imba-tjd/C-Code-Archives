// 试写出一算法，在一个递增有序表A中采用折半查找算法查找为x的元素的递归算法。
// 试写出一算法，利用折半查找在一个有序表中插入一个元素x，并保持表的有序。
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // sprintf、strdup

#define DEFAULTSIZE 20
typedef int DataType;

typedef enum TableType {
    SmallToBig = 1,
    BigToSmall = -1
} TableType;

typedef struct Table
{
    DataType *elem;
    int count;
    int capacity;
    TableType type;
} * Table;

Table CreateTable(int capacity);
bool BinaryInsert(Table table, DataType data);
int BinarySearch(Table table, DataType data, int start, int end);
bool IsFull(Table table);
void Resize(Table table);
void PrintTable(Table table);

int Compare(DataType data1, DataType data2);
char *DataToString(DataType dt);

Table CreateTable(TableType type)
{
    Table table = calloc(1, sizeof(struct Table));
    if (table == NULL)
        exit(EXIT_FAILURE);

    table->elem = calloc(DEFAULTSIZE, sizeof(DataType));
    table->capacity = DEFAULTSIZE;
    table->type = type;

    return table;
}

inline bool IsFull(Table table)
{
    assert(table != NULL);

    return table->capacity == table->count;
}

void Resize(Table table)
{
    table->elem = realloc(table->elem, (table->capacity + DEFAULTSIZE) * sizeof(DataType));

    if (table->elem == NULL)
        exit(EXIT_FAILURE);

    memset(table->elem + table->capacity, 0, DEFAULTSIZE * sizeof(DataType));

    table->capacity += DEFAULTSIZE;
}

bool BinaryInsert(Table table, DataType data)
{
    assert(table != NULL && Compare != NULL);

    if (IsFull(table))
        Resize(table);

    // 以下为data插入start和end中间，实际是赋给end

    // if (table->count == 0)
    // {
    //     table->elem[0] = data;
    //     table->count++;
    //     return true;
    // }

    // int start = 0, end = table->count - 1;
    // int half, result;
    // if (Compare(table->elem[0], data) * table->type > 0) // 从小到大时，第一个元素比它还大，则它应该是新的第一
    //     end = 0;
    // else if (Compare(table->elem[table->count - 1], data) * table->type < 0) // 从小到大时，最后一个元素比它还小，则它应该是新的最后
    //     end = table->count;
    // else
    //     while (start + 1 != end)
    //     {
    //         half = (start + end) / 2;
    //         result = Compare(table->elem[half], data) * table->type;
    //         if (result > 0)
    //             end = half;
    //         else if (result < 0)
    //             start = half;
    //         else
    //             return false;
    //     }

    // DataType *p = &table->elem[table->count - 1];
    // while (*p != table->elem[end - 1])
    // {
    //     *(p + 1) = *p;
    //     p--;
    // }

    // table->elem[end] = data;
    // table->count++;

    int start = 0, end = table->count, half; // 使用不对称边界

    while (start != end)
    {
        half = (start + end) / 2; // 可用 >>1 替代。如果全部用指针，只能先算出一半的距离再加上头指针
        switch (Compare(table->elem[half], data) * table->type)
        {
        case 0:
            return false;
        case 1:
            end = half; // half没找到，因为是不对称的，直接赋给end就行
            continue;
        case -1:
            start = half + 1; // 前面是取得到的，所以要加一
            continue;
        }
    };

    memmove(table->elem + start + 1, table->elem + start, sizeof(DataType) * (table->count - start));
    table->elem[start] = data;
    table->count++;

    return true;
}

int BinarySearch(Table table, DataType data, int start, int end) // 使用对称边界，end减一以后才是有效的数据索引
{
    assert(table != NULL && Compare != NULL);

    if (end < 0) // 但如果count为0，end-1就会为负。所以还是应该用不对称的才好。
        return -1;

    if (start == end) // 剩唯一的一个时两者相等
    {
        if (table->elem[end] == data)
            return end;
        else
            return -1;
    }

    int half = (start + end) / 2;
    int result = Compare(table->elem[half], data) * table->type;
    if (result > 0)
        return BinarySearch(table, data, start, half - 1);
    else if (result < 0)
        return BinarySearch(table, data, half + 1, end);
    else
        return half;
}

void PrintTable(Table table)
{
    for (int i = 0; i < table->count; i++)
    {
        char *ds = DataToString(table->elem[i]);
        printf("%s\n", ds);
        free(ds);
    }
}

// 接口函数

char *DataToString(DataType dt)
{
    char buffer[BUFSIZ];
    sprintf(buffer, "%d", dt);
    return strdup(buffer);
}

int Compare(DataType data1, DataType data2)
{
    return data1 >= data2 ? data1 > data2 ? 1 : 0 : -1;
}

#define BI(table, data) BinaryInsert(table, data)
#define BS(table, data) BinarySearch(table, data, 0, table->count - 1)

int main(void)
{
    // Table table = CreateTable(BigToSmall);
    Table table = CreateTable(SmallToBig);

    BI(table, 1);
    BI(table, 2);
    BI(table, 4);
    BI(table, 3);
    BI(table, 0);
    BI(table, 5);

    // PrintTable(table);

    // printf("%d\n", BS(table, 2));
    printf("%d\n", BS(table, 7));
    // printf("%d\n", BS(table, 5));

    return 0;
}
