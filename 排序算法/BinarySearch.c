#include <stdio.h>

static int BinarySearchInternal(const int arr[], size_t from, size_t to, int target)
{
    if (to - from == 1)
        return arr[from] == target ? from : -1;

    size_t mid = from + (to - from) / 2;

    if (arr[mid] == target)
        return mid;
    else if (arr[mid] < target)
        return BinarySearchInternal(arr, mid, to, target);
    else
        return BinarySearchInternal(arr, from, mid, target);
}

int BinarySearch(size_t len, const int arr[static len], int target)
{
    if (len == 0)
        return -1;

    // 返回值其实应该用ssize_t
    return BinarySearchInternal(arr, 0, len, target);
}
