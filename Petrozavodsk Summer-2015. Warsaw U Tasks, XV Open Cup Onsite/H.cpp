#include<bits/stdc++.h>
#define MAXN 50005
#define MAXLOGN 16
#define MAXB 501
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c[MAXN],k[MAXN],t[MAXN];
vector<int> G[MAXN];
const int threshold=500;
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
int pa[MAXLOGN][MAXN];
int fa[MAXB][MAXN],sum[MAXB][MAXN];
int depth[MAXN];
void dfs(int v,int p,int d)
{
    pa[0][v]=fa[1][v]=p;
    depth[v]=d;
    for(int i=0;i<(int)G[v].size();i++)
        if(G[v][i]!=p) dfs(G[v][i],v,d+1);
}
void dfs2(int v,int p)
{
    for(int k=1;k<=threshold;k++) sum[k][v]=sum[k][fa[k][v]]+c[v];
    for(auto to:G[v]) if(to!=p) dfs2(to,v);
}
void init(int V)
{
    dfs(1,0,0);
    for(int k=0;k+1<MAXLOGN;k++)
        for(int v=1;v<=V;v++)
            pa[k+1][v]=pa[k][pa[k][v]];
    for(int k=1;k<threshold;k++)
        for(int v=1;v<=V;v++)
            fa[k+1][v]=fa[1][fa[k][v]];
    dfs2(1,0);
}
int get(int v,int x)
{
    for(int k=0;k<MAXLOGN;k++)
        if((x>>k)&1)
            v=pa[k][v];
    return v;
}
int lca(int u,int v)
{
    if(depth[u]>depth[v]) swap(u,v);
    v=get(v,depth[v]-depth[u]);
    if(u==v) return u;
    for(int k=MAXLOGN-1;k>=0;k--)
    {
        if(pa[k][u]!=pa[k][v])
        {
            u=pa[k][u];
            v=pa[k][v];
        }
    }
    return pa[0][u];
}
int query(int x,int y,int step)
{
    int l=lca(x,y);
    int ans=0;
    if(step>=threshold)
    {
        while(x!=0&&depth[x]>depth[l])
        {
            ans+=c[x];
            x=get(x,step);
        }
        while(y!=0&&depth[y]>=depth[l])
        {
            ans+=c[y];
            y=get(y,step);
        }
    }
    else
    {
        int len,u;
        if(x!=l)
        {
            len=((depth[x]-depth[l]-1)/step)*step;
            u=get(x,len);
            ans+=sum[step][x]-sum[step][u]+c[u];
        }
        len=((depth[y]-depth[l])/step)*step;
        u=get(y,len);
        ans+=sum[step][y]-sum[step][u]+c[u];
    }
    return ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    init(n);
    for(int i=1;i<=n;i++) scanf("%d",&t[i]);
    for(int i=1;i<=n-1;i++) scanf("%d",&k[i]);
    for(int i=1;i<=n-1;i++) printf("%d\n",query(t[i],t[i+1],k[i]));
    return 0;
}