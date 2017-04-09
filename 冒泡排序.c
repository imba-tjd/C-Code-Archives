// 冒泡排序算法
// https://zhidao.baidu.com/question/1754076342544723828.html
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    void sort(int *a, int l);
    int num[4];
    scanf("%d", num);
    sort(num,4);
    for(int i=0;i<3;i++)
        putchar(num[i]);
    return 0;
}

void sort(int *a, int l)//a为数组地址，l为数组长度。
{
    int i, j;
    int v;
    //排序主体
    for(i=0;i < l-1;i++)
        for(j=i+1;j < l;j++)
        {
            if(a[i] > a[j])//如前面的比后面的大，则交换。
            {
                v=a[i];
                a[i]=a[j];
                a[j]=v;
            }
        }
}
