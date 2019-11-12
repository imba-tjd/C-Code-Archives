#include <stdio.h>

static int BinarySearchInternal(const int arr[], size_t from, size_t to, int target)
{
    if (to - from == 1)
        return arr[from] == target ? from : -1;

    size_t mid = from + (to - from) / 2;

    if (arr[mid] == target)
        return mid;
    else if (arr[mid] > target)
        return BinarySearchInternal(arr, from, mid, target);
    else
        return BinarySearchInternal(arr, mid + 1, to, target);
}

int BinarySearch(size_t len, const int arr[static len], int target)
{
    if (len == 0)
        return -1;

    // 返回值其实应该用ssize_t
    return BinarySearchInternal(arr, 0, len, target);
}

const int *BinarySearch2Internal(size_t len, const int arr[static len], int target)
{
    if (len == 0)
        return NULL;

    size_t mid = len / 2;
    if (arr[mid] == target)
        return &arr[mid];
    else if (arr[mid] > target)
        return BinarySearch2Internal(mid, arr, target);
    else
        return BinarySearch2Internal(len - mid - 1, arr + mid + 1, target);
}

int BinarySearch2(size_t len, const int arr[static len], int target)
{
    const int *result = BinarySearch2Internal(len, arr, target);
    return result == NULL ? -1 : result - arr;
}
