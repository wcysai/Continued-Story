#include<bits/stdc++.h>
typedef long long ll;
#define maxn 200005
using namespace std;
int n,q;
int lc[maxn],rc[maxn],w[maxn],s[maxn];
int lpos[maxn],rpos[maxn],cnt;
void dfs(int u)
{
    if(!u)return;
    lpos[u]=++cnt;
    dfs(lc[u]);
    dfs(rc[u]);
    rpos[u]=cnt;
}
ll sumv[maxn<<2];
void pushup(int x)
{
    sumv[x]=sumv[x<<1]+sumv[x<<1|1];
}
void update(int rt,int l,int r,int pos,int v)
{
    if(l==r)
    {
        sumv[rt]=v;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)update(rt<<1,l,mid,pos,v);
    else update(rt<<1|1,mid+1,r,pos,v);
    pushup(rt);
}
ll query(int rt,int l,int r,int ql,int qr)
{
    ll ans=0;
    int mid=(l+r)>>1;
    if(ql<=l&&r<=qr)return sumv[rt];
    if(ql<=mid)ans+=query(rt<<1,l,mid,ql,qr);
    if(qr>mid)ans+=query(rt<<1|1,mid+1,r,ql,qr);
    return ans;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n+1;++i)scanf("%d",&w[i+n]);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&s[i],&lc[i],&rc[i]);
        if(lc[i]<0)lc[i]=-lc[i]+n;
        if(rc[i]<0)rc[i]=-rc[i]+n;
    }
    dfs(1);
    for(int i=n+1;i<=2*n+1;++i)
    {
        update(1,1,2*n+1,lpos[i],w[i]);
    }
    while(q--)
    {
        int op;
        scanf("%d",&op);
        if(op==1)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            u+=n;
            w[u]=v;
            update(1,1,2*n+1,lpos[u],w[u]);
        }
        else
        {
            int u;
            scanf("%d",&u);
            int x=lc[u],y=rc[u];
            ll m1=query(1,1,2*n+1,lpos[x],rpos[x]);
            ll m2=query(1,1,2*n+1,lpos[y],rpos[y]);
            double ans=(double)m2/(double)(m1+m2);
            ans*=(double)s[u];
            printf("%.15f\n",ans);
        }
    }
}