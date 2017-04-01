/**
    �ṹ��쳲���������һϵ�о�����С�ѵ��и����ļ��ϡ�ÿ�����Ĺؼ��ִ��ڻ�������ĸ����Ĺؼ���
    ÿ����������   p��ָ�򸸽�㣬
                      left��right��ָ����ߺ��ұߵ��ֵܽ�㣬�γ�һ��˫����ṹ��
                      child:ָ��ĳһ�����ӽ�㣬
                      mark;��ǰ����Ƿ�ʧȥ�����ӣ�
                      d:��ǰ���ĺ��ӵĸ���
    ���Ķȣ�ָ��㺢�ӵĸ���
    ���ʣ�Extract-Min������Fab-Heap���㣬���ڽ��Ķȵ�iС�Ľ�㣬��ȴ��ڵ���i-2
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

    void Insert_List(int x,int y){          /** ��x���뵽y�������У�y��Ϊ�� */
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

    void Link(int x,int y){                 /** ��x��Ϊy�ĺ��ӽ��,����x��y���ڸ��б��� */
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
                Link(y,x);                                  /** ��y����Ϊx�ĺ��� */
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

    void Union(){}              /** �ϲ� */

    void Extract_Min(){         /** ��ȡ��С�Ľ�� */
        int z=root;
        if (~z){
            bool flag=0;
            for (int i=t[z].c;flag&&i!=t[z].c;i=t[i].l){
                Insert_List(i,root);
                t[i].p=-1;
                flag=1;
            }
            Delete_List(z);
            if (z==t[z].r)              /** ����ֻ��һ����� */
                root=-1;
            else {                      /** ��ʱ��root������С�Ľ�㣬��ҪConsolidate���� */
                root=t[z].r;
                Consolidate();
            }
        }
    }

    void Cut(int x,int y){                          /** ��x��y���ӽ���Ƴ� */
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

    void Decrease(int x,int k){                     /** �ؼ��ּ�ֵ */
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
