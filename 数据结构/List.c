// 打算做出一个会自动扩展的、可用的顺序表；类似于C#的List
// 但是没写完，因为错误处理有点难弄，不想所有的函数都返回bool。暂时考虑的是失败时直接打印错误信息退出。但是自定义错误error_n是没有的，需要处理
// 另一个问题是自动扩展需要重新分配空间，这样是无法使用柔性数组的。
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#ifndef LIST_DATATYPE
#define LIST_DATATYPE int
#endif
typedef LIST_DATATYPE listdt;

typedef struct _list
{
    size_t length;
    listdt data[];
} * list;

list list_new(size_t initlen);
void list_delete(list lst);
void list_append(list lst, listdt data);
void list_insert(list lst, listdt data, size_t index);
void list_remove(list lst, size_t index);
listdt list_get(list lst, size_t index);
void list_set(list lst, listdt data, size_t index);
bool list_exist(list lst, listdt data);
size_t list_indexof(list lst, listdt data);
size_t list_lastindexof(list lst, listdt data);
// size_t list_length(list lst);
void list_shrink(list lst);
void list_fill(list lst, listdt data);
void list_clear(list lst);

static noreturn void Perror(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

static inline size_t GetSize(size_t len) { return sizeof(struct _list) + sizeof(listdt) * len; }
#define FORLIST for (size_t i = 0; i < lst->length; i++)

static void *Malloc(size_t len)
{
    void *lst = malloc(GetSize(len));
    if (lst == NULL)
        Perror("初始化失败");
    return lst;
}

static void *Realloc(list lst, size_t siz)
{
    return realloc(lst, siz);
}

static void Expand(list lst)
{
}

list list_new(size_t initlen)
{
    if (initlen == 0) // 给个默认大小
        initlen = 512;

    list lst = Malloc(initlen);
    lst->length = 0;
    return lst;
}

void list_delete(list lst)
{
    free(lst);
}

void list_append(list lst, listdt data)
{
    lst->data[lst->length++] = data;
}

listdt list_get(list lst, size_t index)
{
    return lst->data[index];
}
void list_set(list lst, listdt data, size_t index)
{
    lst->data[index] = data;
}
size_t list_indexof(list lst, listdt data)
{
    FORLIST
    {
        if (lst->data[i] == data)
            return i;
    }
    return -1;
}

size_t list_lastindexof(list lst, listdt data)
{
    for (size_t i = lst->length; i >= 0; i--)
        if (lst->data[i] == data)
            return i;
    return -1;
}

bool list_exist(list lst, listdt data)
{
    return list_indexof(lst, data) != -1;
}

void list_fill(list lst, listdt data)
{
    FORLIST
    lst->data[i] = data;
}

void list_clear(list lst)
{
    FORLIST
    lst->data[i] = 0; // 无法用list_fill因为可能不存在0到listdt的转换
}
