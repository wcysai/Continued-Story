#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int n,q;
int a[maxn];
int fa[maxn],ch[maxn][2],sz[maxn],val[maxn],addv[maxn],rt,stk[maxn],top;
void pushup(int x)
{
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
}
void pushdown(int x)
{
    if(addv[x])
    {
        int v=addv[x],lc=ch[x][0],rc=ch[x][1];
        if(lc)val[lc]+=v,addv[lc]+=v;
        if(rc)val[rc]+=v,addv[rc]+=v;
        addv[x]=0;
    }
}
void rot(int x,int &k)
{
    int y=fa[x],z=fa[y],kind;
    if(ch[y][0]==x)kind=1;else kind=0;
    if(y==k)k=x;
    else
    {
        if(ch[z][0]==y)ch[z][0]=x;
        else ch[z][1]=x;
    }
    ch[y][kind^1]=ch[x][kind];
    fa[ch[y][kind^1]]=y;
    ch[x][kind]=y;fa[y]=x;fa[x]=z;
    pushup(y);pushup(x);
}
void splay(int x,int &k)
{
    stk[top=1]=x;
    for(int i=x;fa[i]!=k;i=fa[i])stk[++top]=fa[i];
    for(int i=top;i;--i)pushdown(stk[i]);
    while(x!=k)
    {
        int y=fa[x],z=fa[y];
        if(y!=k)
        {
            if((ch[y][0]==x)^(ch[z][0]==y))rot(x,k);else rot(y,k);
            rot(x,k);
        }
    }
}
int getkth(int x,int k)
{
    pushdown(x);
    int s=sz[ch[x][0]];
    if(k==s+1)return x;
    if(k<=s)return getkth(ch[x][0],k);
    else return getkth(ch[x][1],k-s-1);
}
void add(int l,int r,int v)
{
    int x=getkth(rt,l);
    cerr<<x<<endl;
    int y=getkth(rt,r+2);
    cerr<<y<<endl;
    splay(x,rt);
    cerr<<"xxxxxxxxxxxxxx"<<endl;
    splay(y,ch[x][1]);
    cerr<<"yyyyyyyyyyyyyy"<<endl;
    int z=ch[y][0];
    val[z]+=v;addv[z]+=v;
}
void build(int l,int r,int f)
{
    if(l>r)return;
    int mid=(l+r)>>1;
    sz[mid]=1;fa[mid]=f;
    val[mid]=a[mid-1];
    if(mid<f)ch[f][0]=mid;else ch[f][1]=mid;
    if(l==r)return;
    build(l,mid-1,mid);build(mid+1,r,mid);
    pushup(mid);
}
void ins(int &x,int z,int f)
{
    if(!x){x=z;fa[x]=f;return;}
    if(val[z]<=val[x])ins(ch[x][0],z,x);
    else ins(ch[x][1],z,x);
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    a[n+1]=1000000007;
    sort(a+1,a+n+1);
    rt=(n+3)/2;
    build(1,n+2,rt);
    for(int i=1;i<=n;++i)
    {
        int x=getkth(rt,i+1);
        printf("%d %d\n",x,val[x]);
    }
    while(q--)
    {
        int op,x;
        scanf("%d%d",&op,&x);
        if(op==1)
        {
            int ans=getkth(rt,x+1);
            printf("%d\n",val[ans]);
        }
        else
        {
            int ql,qr,l,r;
            l=1,r=n,ql=n+1;
            while(l<=r)
            {
                int mid=(l+r)>>1;
                int v=val[getkth(rt,mid+1)];
                if(v>x)ql=mid,r=mid-1;
                else l=mid+1;
            }
            l=1;r=n;qr=0;
            while(l<=r)
            {
                int mid=(l+r)>>1;
                int v=val[getkth(rt,mid+1)];
                if(v<=2*x)qr=mid,l=mid+1;
                else r=mid-1;
            }
            if(qr<n)
            {
                add(qr+1,n,-x);
            }
            if(ql<=qr)
            {
                for(int i=ql;i<=qr;++i)
                {
                    int u=getkth(rt,i);
                    int v=getkth(rt,i+2);
                    int w=ch[v][0];
                    ch[v][0]=0;fa[w]=0;
                    val[w]-=x;
                    ins(rt,w,0);
                }
            }
        }
    }
}
