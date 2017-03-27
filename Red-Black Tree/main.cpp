/**

Red-Black Tree
一、定义
    1、每个结点或是红色或是黑色
    2、根结点是黑色
    3、每个叶结点（NIL）是黑色的
    4、如果一个节点是红色的，则其两个子节点都是黑色的
    5、没个结点到所有后代子结点均包含数目相同的黑色结点

二、性质
    1、红黑树上从根节点到叶子结点的简单路径中，没有一条路径会是其他路径的2倍。因为所有路径黑高相同，而红色结点最多占一半少一个。
    2、由性质1可以得出，n个结点的红黑树高度至多为2lg(n+1)
三、操作
    1、左旋、右旋
                    x               y
                   / \    右旋=>   / \
                  y   c   左旋<=  a   x
                 / \                 / \
                a   b               b   c
*/

#include <stdio.h>
#include <queue>
using namespace std;

const int N=1005;
typedef struct {
    int ch[2],p,d;
    bool c;                                 /** c=0表示红色 */
}node;

struct Red_Black_Tree{
    int root;
    int cnt;
    node t[N];

    Red_Black_Tree(){
        cnt=0;
        root=-1;
    }

    int getNew(int x,int pre){
        t[cnt].p=pre;
        t[cnt].ch[0]=t[cnt].ch[1]=-1;
        t[cnt].d=x;
        t[cnt].c=0;
        return cnt++;
    }

    void Rotate(int x,int type){        /** type=0,右旋，type=1,左旋*/
        int y=t[x].ch[type],p=t[x].p;
        t[x].ch[type]=t[y].ch[type^1];
        t[y].ch[type^1]=x;
        if (~t[y].ch[type^1]) t[t[y].ch[type^1]].p=x;
        t[y].p=p;
        if (p==-1) root=y;
        else if (t[p].ch[0]==x) t[p].ch[0]=y;
        else t[p].ch[1]=y;
        t[x].p=y;
    }

    int getSub(int x){
        while (~t[x].ch[0])
            x=t[x].ch[0];
        return x;
    }

    void Transplant(int x,int y){
        if (t[x].p==-1) root=y;
        else if (t[t[x].p].ch[0]==x)
            t[t[x].p].ch[0]=y;
        else t[t[x].p].ch[1]=y;
        if (~y) t[y].p=t[x].p;
    }

    void Insert_Fix(int x){
        int y,p=t[x].p;
        while (~p&&!t[p].c){
            for (int i=0;i<2;i++)
                if (t[t[p].p].ch[i]==p){
                    y=t[t[p].p].ch[i^1];
                    if (~y&&!t[y].c){
                        t[y].c=t[p].c=1;
                        x=t[p].p;
                        p=t[x].p;
                        t[x].c=0;
                        break;
                    }
                    else {
                        if (t[p].ch[i^1]==x){
                            Rotate(p,i^1);
                            p=t[p].p;
                        }
                        t[p].c=1;
                        t[t[p].p].c=0;
                        Rotate(t[p].p,i);
                        p=-1;                       /** 退出*/
                        break;
                    }
                }
        }
        t[root].c=1;
    }

    void Delete_Fix(int x){
        int w,p;
        while (x!=root&&t[x].c){
            for (int i=0;i<2;i++){
                p=t[x].p;
                if (t[p].ch[i]==x){
                    w=t[p].ch[i^1];
                    if (!t[w].c){
                        t[w].c=1;
                        t[p].c=0;
                        Rotate(p,i^1);
                        w=t[p].ch[i^1];
                    }
                    if ((t[w].ch[0]==-1||t[t[w].ch[0]].c)&&(t[w].ch[1]==-1||t[t[w].ch[1]].c)){            /** 此时x的兄弟结点w必为黑色,因为x的父节点必是红色 */
                        t[w].c=0;
                        x=t[x].p;
                    }
                    else {
                        if (t[t[w].ch[i^1]].c){
                            t[w].c=0;
                            t[t[w].ch[i]].c=1;
                            Rotate(w,i);
                            w=t[w].p;
                        }
                        t[p].c=t[t[w].ch[i^1]].c=1;
                        t[w].c=t[p].c;                      /** 将w的颜色赋值为其父结点的颜色*/
                        Rotate(p,i^1);
                        x=root;                             /** x的额外层黑色已经去掉，退出循环*/
                    }
                }
            }
        }
        t[x].c=1;
    }

    void Insert(int x){
        int tp=root,p=-1;
        while (~tp){
            p=tp;
            if (t[tp].d<x) tp=t[tp].ch[1];
            else tp=t[tp].ch[0];
        }
        int n=getNew(x,p);
        if (p==-1) root=n;
        else if (t[p].d<x) t[p].ch[1]=n;
        else t[p].ch[0]=n;
        Insert_Fix(n);
    }

    void Delete(int x){
        int tp=root;
        while (~tp){
            if (t[tp].d<x)
                tp=t[tp].ch[1];
            else if (t[tp].d>x)
                tp=t[tp].ch[0];
            else break;
        }
        if (tp==-1) return ;
        int origin_color=t[tp].c,z;              /** z:删除的位置上的新结点 */
        if (t[tp].ch[0]==-1){
            z=t[tp].ch[1];
            Transplant(tp,z);
        }
        else if (t[tp].ch[1]==-1){
            z=t[tp].ch[0];
            Transplant(tp,z);
        }
        else {
            int y=getSub(t[tp].ch[1]);
            z=t[y].ch[1];
            origin_color=t[y].c;
            if (t[y].p!=tp){
                Transplant(y,t[y].ch[1]);
                t[y].ch[1]=t[tp].ch[1];
                t[t[tp].ch[1]].p=y;
            }
            Transplant(tp,y);
            t[y].ch[0]=t[tp].ch[0];
            t[t[tp].ch[0]].p=y;
            t[y].c=t[tp].c;
        }
        if (~z&&origin_color) Delete_Fix(z);
    }
}test;

void Print_Test(){
    node *T=test.t;
    queue <int> q;
    q.push(test.root);
    while (!q.empty()){
        int tmp=q.front();
        q.pop();
        int l=T[tmp].ch[0];
        if (~l){
            q.push(l);
            l=T[l].d;
        }
        int r=T[tmp].ch[1];
        if (~r){
            q.push(r);
            r=T[r].d;
        }
        printf("%d   color:%d\nlchild: %d,rchild: %d\n",T[tmp].d,T[tmp].c,l,r);
    }
}

int main()
{
    /*
    int op,d;
    FILE *fs=fopen("in","r");
    while (fscanf(fs,"%d%d",&op,&d)!=EOF){
        if (op==1) test.Insert(d);
        else test.Delete(d);
        printf("Case:\n");
        Print_Test();
    }
    */
    node *T=test.t;
    FILE *fs=fopen("in2","r");
    test.root=0;
    int i=0;
    while (fscanf(fs,"%d%d%d%d%d",&T[i].d,&T[i].ch[0],&T[i].ch[1],&T[i].p,&T[i].c)!=EOF) i++;
    Print_Test();
    scanf("%d",&i);
    test.Delete_Fix(i);
    Print_Test();
    return 0;
}
