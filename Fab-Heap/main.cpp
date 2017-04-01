/**
    结构：斐波那契堆是一系列具有最小堆的有根树的集合。每个结点的关键字大于或等于它的父结点的关键字
    每个结点包括，   p：指向父结点，
                      left和right：指向左边和右边的兄弟结点，形成一个双链表结构，
                      child:指向某一个孩子结点，
                      mark;当前结点是否失去过孩子，
                      d:当前结点的孩子的个数
    结点的度：指结点孩子的个数
    性质：Extract-Min操作后，Fab-Heap满足，对于结点的度第i小的结点，其度大于等于i-2
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

const int N=1005;

typedef struct{
    int l,r,p,c,d,k;
    bool m;
}node;

struct Fab_heap{
    node t[N];
    int cnt,root;
    Fab_heap(){
        cnt=0;
        root=-1;
    }

    int getNew(int k){
        t[cnt].d=t[cnt].m=0;
        t[cnt].p=t[cnt].c=-1;
        t[cnt].k=k;
        return cnt++;
    }

    void Insert_List(int x,int y){          /** 将x插入到y的链表中，y不为空 */
        int l=t[y].l;
        t[x].r=y;
        t[x].l=l;
        t[y].l=x;
        t[l].r=x;
    }

    void Delete_List(int x){
        int l=t[x].l,r=t[x].r;
        t[l].r=r;
        t[r].l=l;
    }

    void Link(int x,int y){                 /** 将x变为y的孩子结点,其中x和y都在根列表里 */
        Delete_List(x);
        if (t[y].c==-1) t[y].c=t[x].l=t[x].r=x;
        else Insert_List(x,t[y].c);
        t[x].p=y;
        t[y].d++;
        t[x].m=0;
    }

    void Consolidate(){
        int f[N]={-1};
        bool flag=0;
        for (int i=root;flag&&i!=root;i=t[i].l){
            flag=1;
            int x=i,d=t[x].d;
            while (~f[d]){
                int y=f[d];
                if (t[x].k>t[y].k)
                    swap(x,y);
                Link(y,x);                                  /** 将y连接为x的孩子 */
                d++;
            }
            f[d]=x;
        }
        int END=root;
        for (int j=t[root].l;j!=END;j=t[j].l){
            flag=1;
            if (t[j].k<t[root].k) root=j;
        }
    }

    void Insert(int x){
        int cur=getNew(x);
        if (root==-1){
            t[cur].l=t[cur].r=cur;
            root=cur;
        }
        else{
            Insert_List(cur,root);
            if (t[root].k>x) root=cur;
        }
    }

    void Union(){}              /** 合并 */

    void Extract_Min(){         /** 抽取最小的结点 */
        int z=root;
        if (~z){
            bool flag=0;
            for (int i=t[z].c;flag&&i!=t[z].c;i=t[i].l){
                Insert_List(i,root);
                t[i].p=-1;
                flag=1;
            }
            Delete_List(z);
            if (z==t[z].r)              /** 堆内只有一个结点 */
                root=-1;
            else {                      /** 此时的root不是最小的结点，需要Consolidate操作 */
                root=t[z].r;
                Consolidate();
            }
        }
    }

    void Cut(int x,int y){                          /** 将x从y的子结点移除 */
        if (t[x].r==x) t[y].c=-1;
        else Delete_List(x);
        t[y].d--;
        Insert_List(x,root);
        t[x].p=-1;
        t[x].m=0;
    }

    void Cascading_Cut(int x){
        int y=t[x].p;
        if (~y){
            if (t[x].m){
                Cut(x,y);
                Cascading_Cut(y);
            }
            else t[x].m=1;
        }
    }

    void Decrease(int x,int k){                     /** 关键字减值 */
        t[x].k=k;
        int y=t[x].p;
        if (~y&&t[x].k<t[y].k){
            Cut(x,y);
            Cascading_Cut(y);
        }
        if (t[x].k<t[root].k) root=x;
    }
};

int main()
{

    return 0;
}
