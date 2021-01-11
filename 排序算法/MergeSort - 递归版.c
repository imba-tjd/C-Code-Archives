#define NOTEST
#include "MergeSortedArray.c"

void merge_sort(int arr[], int len) {
    if (len <= 1)
        return;

    const int len1 = len / 2;
    const int len2 = len - len1;
    merge_sort(arr, len1);
    merge_sort(arr + len1, len2);
    merge_sorted_array_in_place(arr, arr + len1, arr + len);
}

int main(void) {
    int arr[10] = {76, 32, 71, 52, 65, 69, 2, 27, 30, 67};
    merge_sort(arr, 10);
    print_arr(arr, 10);
}
