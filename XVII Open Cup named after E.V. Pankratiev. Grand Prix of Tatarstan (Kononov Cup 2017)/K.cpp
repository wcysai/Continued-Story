#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,a[MAXN];
struct segtree
{
    P val[4*MAXN];//minimum value over interval
    P val2[4*MAXN];//minimum value(larger index first) over interval
    ll sum[4*MAXN];//sum of value
    int f[4*MAXN]; //maximum height-pos over interval
    int g[4*MAXN]; //maximum height+pos over interval
    void pushup(int k)
    {
        sum[k]=sum[k*2]+sum[k*2+1];
        val[k]=min(val[k*2],val[k*2+1]);
        val2[k]=min(val2[k*2],val2[k*2+1]);
        f[k]=max(f[k*2],f[k*2+1]);
        g[k]=max(g[k*2],g[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            f[k]=-l; g[k]=l; val[k]=P(a[l],l); val2[k]=P(a[l],-l); sum[k]=a[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int p,int v)
    {
        if(l==r)
        {
            f[k]++; g[k]++; val[k].F=val2[k].F=v; sum[k]=v;
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p,v); else update(k*2+1,mid+1,r,p,v);
        pushup(k);
    }
    int get_left(int k,int l,int r,int p,int val)//first with f>=val at left of p
    {
        if(l>p) return 0;
        if(f[k]<val) return 0;
        if(l==r) return l;
        int mid=(l+r)/2;
        int x=get_left(k*2+1,mid+1,r,p,val);
        if(x!=0) return x; else return get_left(k*2,l,mid,p,val); 
    }
    int get_right(int k,int l,int r,int p,int val)//first with g>=val at right of p
    {
        if(r<p) return n+1;
        if(g[k]<val) return n+1;
        if(l==r) return l;
        int mid=(l+r)/2;
        int x=get_right(k*2,l,mid,p,val);
        if(x!=n+1) return x; else return get_right(k*2+1,mid+1,r,p,val);
    }
    int queryf(int k,int l,int r,int p)
    {
        if(l==r) return f[k];
        int mid=(l+r)/2;
        if(p<=mid) return queryf(k*2,l,mid,p); else return queryf(k*2+1,mid+1,r,p);
    }
    int queryg(int k,int l,int r,int p)
    {
        if(l==r) return g[k];
        int mid=(l+r)/2;
        if(p<=mid) return queryg(k*2,l,mid,p); else return queryg(k*2+1,mid+1,r,p);
    }
    P query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return P(INF,0);
        if(l>=x&&r<=y) return val[k];
        int mid=(l+r)/2;
        return min(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
    P query2(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return P(INF,0);
        if(l>=x&&r<=y) return val2[k];
        int mid=(l+r)/2;
        return min(query2(k*2,l,mid,x,y),query2(k*2+1,mid+1,r,x,y));
    }
}seg;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    seg.build(1,1,n);
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int lpos=seg.get_left(1,1,n,x-1,m-x),rpos=seg.get_right(1,1,n,x+1,m+x);
        if(lpos==0||seg.queryf(1,1,n,lpos)!=m-x) lpos++;
        if(rpos==n+1||seg.queryg(1,1,n,rpos)!=m+x) rpos--;
        P lp=seg.query2(1,1,n,lpos,x),rp=seg.query(1,1,n,x,rpos);
        lp.S=-lp.S;
        P p;
        if(lp.F!=rp.F) p=min(lp,rp);
        else if(x-lp.S<=rp.S-x) p=lp; else p=rp;
        seg.update(1,1,n,p.S,y);
        printf("%lld\n",seg.sum[1]);
    }
    return 0;
}