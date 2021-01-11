#include <stdio.h>

void selection_sort(int arr[], int n) {
    int t;
    for (int i = 0; i < n - 1; i++) {
        int minndx = i;
        for (int j = i + 1; j < n; j++)  // 从后面找一个数
            if (arr[j] < arr[minndx])
                minndx = j;
        if (minndx != i)
            t = arr[minndx], arr[minndx] = arr[i], arr[i] = t;
    }
}

// 劣化版：每次都交换一下。
// 正常版的是每次记录下标，最后才交换一次。比较O(n^2)，移动O(n)
void selection_sort2(int arr[], int n) {
    int t;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])  // 从小到大排序
                t = arr[i], arr[i] = arr[j], arr[j] = t;
}

int main() {
    int arr[10] = {4, 28, 19, 8, 22, 14, 27, 25, 7, 11};
    selection_sort(arr, 10);
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
