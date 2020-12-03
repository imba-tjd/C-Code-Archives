// 用（递归）分治法设计一个算法，在数组A中寻找最大元素和最小元素
#include <stdio.h>

void MaxAndMin(const int arr[], int n, int *max, int *min) {
    if (n == 1) {
        *max = *min = arr[0];
        return;
    }

    int half = n / 2;
    int max1, max2, min1, min2;
    MaxAndMin(arr, half, &max1, &min1);
    MaxAndMin(arr + half, n - half, &max2, &min2);
    *max = max1 > max2 ? max1 : max2;
    *min = min1 < min2 ? min1 : min2;
}

int main(void) {
    int arr[] = {85, 75, 75, 59, 7, 30, 36, 16, 27, 80, 53, 78, 69, 85, 75};
    int max, min;
    MaxAndMin(arr, sizeof(arr) / sizeof(*arr), &max, &min);
    printf("%d %d\n", max, min);
}
