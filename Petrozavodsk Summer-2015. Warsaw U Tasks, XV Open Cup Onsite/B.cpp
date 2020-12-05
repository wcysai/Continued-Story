#include<bits/stdc++.h>
#define maxn 1000005
typedef long long ll;
using namespace std;
int n,m;
int a[maxn],lst[maxn],lst2[maxn];
ll w[maxn];
ll maxv[maxn<<2],addv[maxn<<2];
void pushup(int rt)
{
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
}
void pushdown(int rt)
{
    if(addv[rt])
    {
        ll t=addv[rt];
        maxv[rt<<1]+=t;maxv[rt<<1|1]+=t;
        addv[rt<<1]+=t;addv[rt<<1|1]+=t;
        addv[rt]=0;
    }
}
void add(int rt,int l,int r,int ql,int qr,ll v)
{
    if(ql>qr)return;
    if(ql<=l&&r<=qr)
    {
        maxv[rt]+=v;addv[rt]+=v;
        return;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(ql<=mid)add(rt<<1,l,mid,ql,qr,v);
    if(qr>mid)add(rt<<1|1,mid+1,r,ql,qr,v);
    pushup(rt);
}
ll query(int rt,int l,int r,int ql,int qr)
{
    ll ans=0;
    if(ql<=l&&r<=qr)return maxv[rt];
    pushdown(rt);
    int mid=(l+r)>>1;
    if(ql<=mid)ans=max(ans,query(rt<<1,l,mid,ql,qr));
    if(qr>mid)ans=max(ans,query(rt<<1|1,mid+1,r,ql,qr));
    pushup(rt);
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(int i=1;i<=m;++i)scanf("%lld",&w[i]);
    ll ans=0;
    for(int i=1;i<=n;++i)
    {
        add(1,1,n,lst[a[i]]+1,i,w[a[i]]);
        add(1,1,n,lst2[a[i]]+1,lst[a[i]],-w[a[i]]);
        ans=max(ans,query(1,1,n,1,i));
        //if(i==4)cerr<<query(1,1,n,1,1)<<endl;
        //cerr<<i<<" "<<query(1,1,n,1,i)<<endl;
        lst2[a[i]]=lst[a[i]];
        lst[a[i]]=i;
    }
    printf("%lld\n",ans);
}
