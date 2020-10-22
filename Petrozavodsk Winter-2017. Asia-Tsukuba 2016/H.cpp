#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,dfn[MAXN],low[MAXN],st[MAXN],vis[MAXN],cmp[MAXN],color[MAXN],cnt,tot,t;
vector<P> G[MAXN];
vector<int> GG[MAXN];
vector<int> H[MAXN];
vector<int> order;
int dist[MAXN];
int f[MAXN],g[MAXN],h[MAXN];
void add_edge(int u,int v,int type)
{
    G[u].push_back(P(v,type));
    if(type==2) G[v].push_back(P(u,type));
}
void dfs(int v)
{
    dfn[v]=low[v]=++tot;
    vis[v]=1;
    st[t++]=v;
    for(auto e:G[v])
    {
        int to=e.F;
        if(!vis[to])
        {
            dfs(to);
            low[v]=min(low[v],low[to]);
        }
        else if(vis[to]==1) low[v]=min(low[v],dfn[to]);
    }
    if(dfn[v]==low[v])
    {
        int u;
        ++cnt;
        do
        {
            u=st[t-1]; t--;
            cmp[u]=cnt;
            vis[u]=2;
        }while(u!=v);
    }
}
bool flag;
vector<int> comp[MAXN];
void check_comp(int id)
{
    int s=0;
    for(auto v:comp[id])
    {
        for(auto e:G[v])
        {
            int to=e.F;
            if(cmp[to]==id)
            {
                if(e.S==1) flag=false;
                else s++;
            }
        }
    }
    assert(s%2==0);
    if(s/2!=(int)comp[id].size()-1) flag=false;
}
void dfs_visit(int v)
{
    color[v]=1;
    for(auto to:GG[v])
        if(color[to]==0) dfs_visit(to);
    color[v]=2;
    order.push_back(v);
}
void toposort()
{
    memset(color,0,sizeof(color));
    for(int i=1;i<=cnt;i++) if(color[i]==0) dfs_visit(i);
}
void dfs2(int v,int p)
{
    h[v]=f[v];
    for(auto to:H[v])
    {
        if(to==p) continue;
        dfs2(to,v);
        h[v]=max(h[v],h[to]+1);
    }
}
void dfs3(int v,int p)
{
    int max1=-1,max2=-1;
    for(auto to:H[v])
    {
        if(to==p) continue;
        if(h[to]+1>max1)
        {
            max2=max1;
            max1=h[to]+1;
        }
        else if(h[to]+1>max2) max2=h[to]+1;
    }
    for(auto to:H[v])
    {
        if(to==p) continue;
        if(h[to]+1==max1) g[to]=max(f[to],max(max2+1,g[v]+1));
        else g[to]=max(f[to],max(max1+1,g[v]+1));
    }
    for(auto to:H[v])
    {
        if(to==p) continue;
        dfs3(to,v);
    }
}
void solve(int comp_id)
{
    int rt=comp[comp_id][0];
    dfs2(rt,0);
    g[rt]=f[rt];
    dfs3(rt,0);
    for(auto v:comp[comp_id])
    {
        for(auto e:G[v])
        {
            int to=e.F;
            if(e.S==1) f[to]=max(f[to],max(g[v],h[v])+1);
        }
    }   
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v,type;
        scanf("%d%d%d",&u,&v,&type);
        add_edge(u,v,type);
        if(type==2) {H[v].push_back(u); H[u].push_back(v);}
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
    for(int i=1;i<=n;i++) comp[cmp[i]].push_back(i);
    flag=true;
    for(int i=1;i<=cnt;i++) check_comp(i);
    if(!flag) {puts("Infinite"); return 0;}
    for(int i=1;i<=n;i++)
    {
        for(auto e:G[i])
        {
            int to=e.F;
            if(e.S==1) GG[cmp[i]].push_back(cmp[to]);
        }
    }
    toposort();
    reverse(order.begin(),order.end());
    for(auto x:order) 
    {
        solve(x);
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,max(g[i],h[i]));
    printf("%d\n",ans);
}