#include <stdio.h>

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {  // 待修改索引
        int minndx = i;
        for (int j = i + 1; j < n; j++)  // 在后面找最小的数的索引
            if (arr[j] < arr[minndx])
                minndx = j;
        int t;
        if (minndx != i)
            t = arr[minndx], arr[minndx] = arr[i], arr[i] = t;
    }
}

// 劣化版：每次都交换一下，也能保证一轮过后arr[i]是后面之中最小的
// 正常版是每次记录最小数下标，最后才交换一次。比较O(n^2)，移动O(n)
void selection_sort2(int arr[], int n) {
    int t;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])  // 从小到大排序
                t = arr[i], arr[i] = arr[j], arr[j] = t;
}

int main(void) {
    int arr[10] = {4, 28, 19, 8, 22, 14, 27, 25, 7, 11};
    selection_sort(arr, 10);
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
