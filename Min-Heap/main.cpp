#include <stdio.h>
#include <malloc.h>
#include <algorithm>
using namespace std;

const int N=10005;
int test[N];

struct Min_Heap{
    int *A,heap_size;

    Min_Heap(){}
    Min_Heap(int _heap_size,int* _A){
        heap_size=_heap_size;
        A=_A;
    }

    void Maintain(int s){       //维护堆性质
        int l=s<<1,r=l+1,largest=s;
        if (l<=heap_size&&A[l]<A[largest])
            largest=l;
        if (r<=heap_size&&A[r]<A[largest])
            largest=r;
        if (largest!=s){
            swap(A[largest],A[s]);
            Maintain(largest);
        }
    }

    void Build(){
        for (int i=heap_size>>1;i;i--)
            Maintain(i);
    }

    void Heap_Sort(){       //最小堆，排序结果从大到小
        Build();
        for (int i=heap_size;i>1;i--){
            swap(A[i],A[1]);
            heap_size--;
            Maintain(1);
        }
    }

};

struct Priority_Queue{
    struct Min_Heap heap;
    int queue_size,*A;

    Priority_Queue(int _size=500){
        queue_size=_size+1;
        A=(int*)malloc(sizeof(int)*queue_size);
        heap.A=A;
        heap.heap_size=0;
    }

    void Insert(int a){
        if (heap.heap_size==queue_size){
            queue_size<<=1;
            int *tp=(int*)malloc(sizeof(int)*queue_size);
            for (int j=1;j<=heap.heap_size;j++) tp[j]=A[j];
            free(A);
            heap.A=A=tp;
        }
        heap.heap_size++;
        A[heap.heap_size]=a;
        for (int i=heap.heap_size;i>1&&A[i>>1]>A[i];i>>=1)
            swap(A[i],A[i>>1]);
    }

    int First_Element(){
        return heap.heap_size>0?A[1]:-1;
    }

    void Delete(){
        if (heap.heap_size>0){
            A[1]=A[heap.heap_size];
            heap.heap_size--;
            heap.Maintain(1);
        }
    }
};

int main()
{
    /*
    int t_size;
    FILE *fs=fopen("in","r"),*fp=fopen("out","w");
    while (fscanf(fs,"%d",&t_size)!=EOF){
        for (int i=1;i<=t_size;i++)
            fscanf(fs,"%d",&test[i]);
        struct Min_Heap a=Min_Heap(t_size,test);
        a.Heap_Sort();
        for (int j=1;j<=t_size;j++)
            fprintf(fp,"%d%c",test[j],j==t_size?'\n':' ');
    }
    */
    int op,t;
    struct Priority_Queue q=Priority_Queue();
    while (scanf("%d",&op)!=EOF){
        if (op==1){
            scanf("%d",&t);
            q.Insert(t);
        }
        else if (op==2) q.Delete();
        printf("%d\n",q.First_Element());
    }
    return 0;
}
