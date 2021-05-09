#include<bits/stdc++.h>
#define maxn 500005
using namespace std;
typedef long long ll;
int n,q;
int a[maxn],L[maxn],R[maxn];
int stk[maxn],top;
map< pair<int,int>,int > used;
vector< pair<int,ll> > g[maxn];
int lc[maxn*40],rc[maxn*40],T[maxn],cnt;
ll sumv[maxn*40];
void build(int &x,int l,int r)
{
    x=++cnt;
    lc[x]=rc[x]=sumv[x]=0;
    int mid=(l+r)>>1;
    if(l==r)return;
    build(lc[x],l,mid);build(rc[x],mid+1,r);
}
void update(int &x,int pre,int l,int r,int pos,ll w)
{
    x=++cnt;
    lc[x]=lc[pre];rc[x]=rc[pre];sumv[x]=sumv[pre]+w;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(pos<=mid)update(lc[x],lc[pre],l,mid,pos,w);
    else update(rc[x],rc[pre],mid+1,r,pos,w);
}
ll query(int u,int v,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)return sumv[u]-sumv[v];
    int mid=(l+r)>>1;
    ll ans=0;
    if(ql<=mid)ans+=query(lc[u],lc[v],l,mid,ql,qr);
    if(qr>mid)ans+=query(rc[u],rc[v],mid+1,r,ql,qr);
    return ans;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    top=0;
    for(int i=1;i<=n;++i)
    {
        while(top&&a[stk[top]]<=a[i])--top;
        if(top)L[i]=stk[top];else L[i]=0;
        stk[++top]=i;
    }
    top=0;
    for(int i=n;i>=1;--i)
    {
        while(top&&a[stk[top]]<=a[i])--top;
        if(top)R[i]=stk[top];else R[i]=n+1;
        stk[++top]=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(L[i]>=1&&R[i]<=n)
        {
            if(used.count(make_pair(L[i],R[i])))continue;
            g[L[i]].push_back(make_pair(R[i],1ll*(R[i]-L[i]-1)*(min(a[L[i]],a[R[i]])-a[i])));
            used[make_pair(L[i],R[i])]=1;
        }
    }
    build(T[0],1,n);
    for(int i=1;i<=n;++i)
    {
        T[i]=T[i-1];
        for(auto p:g[i])
        {
            update(T[i],T[i],1,n,p.first,p.second);
        }
    }
    while(q--)
    {
        int L,R;
        scanf("%d%d",&L,&R);
        ll ans=query(T[n],T[L-1],1,n,1,R);
        printf("%lld\n",ans);
    }
}