#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 20
#define INF 2000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q;
struct edge{int to,cost;};
vector<edge> G[MAXN];
int pa[MAXLOGN][MAXN],depth[MAXN],pacost[MAXN];
int mineven[MAXLOGN][MAXN],cnteven[MAXLOGN][MAXN];
void add_edge(int u,int v,int c)
{
    G[u].push_back((edge){v,c});
    G[v].push_back((edge){u,c});
}
void dfs(int v,int p,int d,int c)
{
    pa[0][v]=p;
    pacost[v]=c;
    if(c%2==0) {mineven[0][v]=c; cnteven[0][v]=1;} else {mineven[0][v]=INF; cnteven[0][v]=0;} 
    depth[v]=d;
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(to!=p) dfs(to,v,d+1,cost);
    }
}
void init(int V)
{
    dfs(1,0,0,0);
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=V;v++)
        {
            if(pa[k][v]<0) {pa[k+1][v]=-1; mineven[k+1][v]=INF; cnteven[k+1][v]=0;}
            else 
            {
                pa[k+1][v]=pa[k][pa[k][v]];
                mineven[k+1][v]=min(mineven[k][v],mineven[k][pa[k][v]]);
                cnteven[k+1][v]=cnteven[k][v]+cnteven[k][pa[k][v]];
            }
        }
    }
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
int dis(int u,int v)
{
    return depth[u]+depth[v]-2*depth[lca(u,v)];
}
int get_mineven(int u,int v)
{
    int l=lca(u,v);
    int ans=INF;
    int delta=depth[v]-depth[l];
    for(int k=0;k<MAXLOGN;k++)
        if((delta>>k)&1)
        {
            ans=min(ans,mineven[k][v]);
            v=pa[k][v];
        }
    delta=depth[u]-depth[l];
    for(int k=0;k<MAXLOGN;k++)
        if((delta>>k)&1)
        {
            ans=min(ans,mineven[k][u]);
            u=pa[k][u];
        }
    return ans;
}
int get_cnteven(int u,int v)
{
    int l=lca(u,v);
    int ans=0;
    int delta=depth[v]-depth[l];
    for(int k=0;k<MAXLOGN;k++)
        if((delta>>k)&1)
        {
            ans+=cnteven[k][v];
            v=pa[k][v];
        }
    delta=depth[u]-depth[l];
    for(int k=0;k<MAXLOGN;k++)
        if((delta>>k)&1)
        {
            ans+=cnteven[k][u];
            u=pa[k][u];
        }
    return ans;
}
int main()
{
    scanf("%d%d",&n,&q);
    int s=0;
    for(int i=0;i<n-1;i++)
    {
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        add_edge(u,v,c);
        if(c&1) s^=1;
    }
    init(n);
    for(int i=0;i<q;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        int dist=dis(u,v),x=get_mineven(u,v),cnt=get_cnteven(u,v);
        if(cnt==0) puts("1"); 
        else if(cnt>=3) puts("2");
        else if(cnt==2)
        {
            if(s==0) puts("2"); else {if(x>=dist-1) puts("1"); else puts("2");}
        } 
        else {if(x>=dist-1) puts("1"); else puts("2");}
    }
    return 0;
}