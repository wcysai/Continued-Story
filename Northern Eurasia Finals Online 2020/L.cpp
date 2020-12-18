#include<bits/stdc++.h>
#define maxn 600005
using namespace std;
int n,LS[maxn],RS[maxn],VA[maxn],q,QL[maxn],QR[maxn];
int dv[maxn],d;
int vmin[maxn],vmax[maxn];
vector<int> g[maxn];
void dfs(int u)
{
    vmin[u]=VA[u];vmax[u]=VA[u];
    if(LS[u])
    {
        dfs(LS[u]);
        vmin[u]=min(vmin[u],vmin[LS[u]]);
    }
    if(RS[u])
    {
        dfs(RS[u]);
        vmax[u]=max(vmax[u],vmax[RS[u]]);
    }
}
int lc[maxn*60],rc[maxn*60],sumv[maxn*60];
int T[maxn],cnt;
void update(int &x,int pre,int l,int r,int pos)
{
    x=++cnt;
    lc[x]=lc[pre];rc[x]=rc[pre];
    sumv[x]=sumv[pre]+1;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(pos<=mid)update(lc[x],lc[pre],l,mid,pos);
    else update(rc[x],rc[pre],mid+1,r,pos);
}
void build(int &x,int l,int r)
{
    x=++cnt;
    sumv[x]=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(lc[x],l,mid);
    build(rc[x],mid+1,r);
}
int query(int x,int y,int l,int r,int ql,int qr)
{
    if(ql>qr)return 0;
    if(ql<=l&&r<=qr)
    {
        return sumv[y]-sumv[x];
    }
    int mid=(l+r)>>1;
    int ans=0;
    if(ql<=mid)ans+=query(lc[x],lc[y],l,mid,ql,qr);
    if(qr>mid)ans+=query(rc[x],rc[y],mid+1,r,ql,qr);
    return ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&LS[i],&RS[i],&VA[i]);
        dv[++d]=VA[i];
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        scanf("%d%d",&QL[i],&QR[i]);
        dv[++d]=QL[i];
        dv[++d]=QR[i];
    }
    sort(dv+1,dv+d+1);
    d=unique(dv+1,dv+d+1)-dv-1;
    for(int i=1;i<=n;++i)VA[i]=lower_bound(dv+1,dv+d+1,VA[i])-dv;
    for(int i=1;i<=q;++i)
    {
        QL[i]=lower_bound(dv+1,dv+d+1,QL[i])-dv;
        QR[i]=lower_bound(dv+1,dv+d+1,QR[i])-dv;
    }
    dfs(1);
    for(int i=1;i<=n;++i)g[vmin[i]].push_back(vmax[i]);
    build(T[0],1,d);
    for(int x=1;x<=d;++x)
    {
        T[x]=T[x-1];
        for(int y:g[x])
        {
            update(T[x],T[x],1,d,y);
        }
    }
    for(int i=1;i<=q;++i)
    {
        int l=QL[i],r=QR[i];
        int ans=2*n+1;
        ans-=2*query(T[0],T[d],1,d,1,l-1);
        ans-=2*query(T[r],T[d],1,d,1,d);
        ans-=2*query(T[l-1],T[d],1,d,1,r);
        printf("%d\n",ans);
    }
}
