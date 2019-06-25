#define NOTEST
#include "MergeSortedArray.c"

void MergeSort(size_t len, int arr[len])
{
    if (len == 1)
        return;

    const int len1 = len / 2;
    const int len2 = len - len1;
    MergeSort(len1, arr);
    MergeSort(len2, arr + len1);
    MergeSortedArrayInPlace(len1, arr, len2, arr + len1);
}

int main(void)
{
    int array[LEN] = {76, 32, 71, 52, 65, 69, 2, 27, 30, 67};

    MergeSort(LEN, array);

    PrintArr(LEN, array);
}
