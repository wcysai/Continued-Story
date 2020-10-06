#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,cnt,mcnt,num,x[MAXN],y[MAXN],dfn[MAXN],low[MAXN],U[MAXN],V[MAXN],sz[MAXN],tot;
vector<int> G[MAXN];
bool isodd[MAXN];
bool ans[MAXN];
void add_edge(int u,int v)
{
    U[++mcnt]=u;V[mcnt]=v;
    G[u].push_back(mcnt);G[v].push_back(mcnt);
}
int adj(int u,int e)
{
    return U[e]==u?V[e]:U[e];
}
void dfs(int v,int edge)
{
    dfn[v]=++tot;
    for(auto e:G[v])
    {
        if(e==edge) continue;
        int to=adj(v,e);
        if(dfn[to]) {if(dfn[to]<dfn[v]) cnt++;}
        else {cnt++; dfs(to,e);}
    }
}
void dfs1(int v,int edge)
{
    dfn[v]=low[v]=++tot;
    for(auto e:G[v])
    {
        if(e==edge) continue;
        int to=adj(v,e);
        if(!dfn[to])
        {
            ans[e]=true;
            dfs1(to,e);
            low[v]=min(low[v],low[to]);
            sz[v]+=sz[to]+1;
        }
        else
        {
            if(dfn[to]<dfn[v]) {ans[e]=true; sz[v]++;}
            low[v]=min(low[v],dfn[to]);
        }
    }
    if(low[v]==dfn[v]&&edge!=-1)
    {
        if(sz[v]&1) ans[edge]=false; else ans[edge]=true;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=2*n+1;i++)
    {
        scanf("%d%d",&x[i],&y[i]);
        add_edge(x[i],2*n+1+y[i]);
    }
    memset(isodd,false,sizeof(isodd));
    for(int i=1;i<=4*n+2;i++)
    {
        if(!dfn[i])
        {
            cnt=0;
            dfs(i,-1);
            if(cnt&1) {num++; isodd[i]=true;}
        }
    }
    if(num>1)
    {
        for(int i=1;i<=2*n+1;i++) puts("NG");
        return 0;
    }
    memset(ans,false,sizeof(ans));
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=4*n+2;i++)
    {
        if(isodd[i])
        {
            tot=0;
            dfs1(i,-1);
        }
    }
    for(int i=1;i<=2*n+1;i++)
    {
        if(ans[i]) puts("OK"); else puts("NG");
    }
    return 0;
}
