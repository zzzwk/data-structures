#include <stdio.h>

const int N=10005;
int d[N]={5,2,3,1,9,4,7,6,8,0};

void quick_sort(int low,int high){
    if (low>=high) return ;
    int l=low,r=high,key=d[low];
    while (l<r){
        while (l<r&&d[r]>=key) r--;
        d[l]=d[r];
        while (l<r&&d[l]<=key) l++;
        d[r]=d[l];
    }
    d[l]=key;
    quick_sort(low,l-1);
    quick_sort(l+1,high);
}
/**
    取最小n个数
    结果是最小的n个数在数组的前n个
*/
void leastNsum(int low,int high,int n){
    if (low>=high) return ;
    int l=low,r=high,key=d[low];
    while (l<r){
        while (l<r&&d[r]>=key) r--;
        d[l]=d[r];
        while (l<r&&d[l]<=key) l++;
        d[r]=d[l];
    }
    d[l]=key;
    int tn=l-low+1;
    if (tn==n||tn-1==n) return ;
    else if (n>tn) leastNsum(l+1,high,n-tn);
    else leastNsum(low,l-1,n);
}

int main()
{
    /*
    quick_sort(0,9);
    for (int i=0;i<10;i++)
        printf("%d\n",d[i]);
    */
    leastNsum(0,9,7);
    for (int i=0;i<7;i++)
        printf("%d\n",d[i]);
    return 0;
}
