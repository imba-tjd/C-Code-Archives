// 开放定址法中线性探测再散列解决冲突的散列表查找功能
#include <assert.h>
#include <stdio.h>

// 返回0表示满了，插入失败
int hash_insert(int table[], int len, int value) {
    int index = value % len;
    const int flag = index;  // 用于标记是否找完了一圈

    while (table[index] != 0)                     // 把0看作NULL
        if ((index = (index + 1) % len) == flag)  // 实际上也属于循环条件，是失败分支
            return 0;

    table[index] = value;
    return 1;
}

int hash_search(int table[], int len, int value) {
    int index = value % len;
    const int flag = index;

    while (table[index] != value)
        if ((index = (index + 1) % len) == flag)
            return -1;

    return index;
}

int hash_search2(int table[], int len, int value) {
    int index = value % len;
    const int flag = index;

    do {
        if (table[index] == value)
            return index;  // 思路互换，此处是成功分支
        else
            index = (index + 1) % len;
    } while (index != flag);

    return -1;
}

int main(void) {
#define LEN 8
    int table[LEN] = {0};
    int values[] = {4, 28, 19, 8, 22, 14, 27, 25};
    for (int i = 0; i < 8; i++)
        hash_insert(table, LEN, values[i]);

    int result[] = {4, 5, 3, 0, 6, 7, 1, 2};
    for (int i = 0; i < 8; i++) {
        assert(result[i] == hash_search(table, LEN, values[i]));
        assert(result[i] == hash_search2(table, LEN, values[i]));
    }

    assert(hash_insert(table, LEN, 10) == 0);
    assert(hash_search(table, LEN, 10) == -1);
    assert(hash_search2(table, LEN, 10) == -1);
}
