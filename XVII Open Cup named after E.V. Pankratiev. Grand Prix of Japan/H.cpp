#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c[MAXN],a[MAXN],last[MAXN],ans[MAXN];
struct segtree
{
    int mini[4*MAXN];
    void pushup(int k)
    {
        mini[k]=min(mini[k*2],mini[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        mini[k]=0;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int p,int v)
    {
        if(l==r)
        {
            mini[k]=v;
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p,v); else update(k*2+1,mid+1,r,p,v);
        pushup(k);
    }
    int query(int k,int l,int r,int v)
    {
        if(l==r) return l;
        int mid=(l+r)/2;
        if(mini[k*2]<v) return query(k*2,l,mid,v); else return query(k*2+1,mid+1,r,v);

    }
}seg;
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;i++) scanf("%d%d",&c[i],&a[i]);
    seg.build(1,1,n);
    seg.update(1,1,n,1,1);
    for(int i=2;i<=n;i++)
    {
        if(seg.mini[1]>=i-c[i]) ans[i]=0; else ans[i]=seg.query(1,1,n,i-c[i])-1;
        last[ans[i]+1]=i;
        seg.update(1,1,n,ans[i]+1,i);
    }
    int s=0;
    for(int i=2;i<=n;i++) if(a[i]&1) s^=ans[i];
    if(s) puts("First"); else puts("Second");
    return 0;
}
