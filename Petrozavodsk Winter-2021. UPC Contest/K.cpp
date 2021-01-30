#include<bits/stdc++.h>
#define maxn 1000005
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,tot,t,tt,bcc_cnt,mcnt;
vector<int> G[maxn];
int st[maxn],dfn[maxn],low[maxn];
int U[maxn],V[maxn],sz[maxn];
bool isbridge[maxn];
int bel[maxn];
vector<int> tree[maxn];
void add_edge(int u,int v)
{
    U[++mcnt]=u;V[mcnt]=v;
    G[u].push_back(mcnt);G[v].push_back(mcnt);
}
int adj(int u,int e)
{
    return U[e]==u?V[e]:U[e];
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
            dfs1(to,e);
            low[v]=min(low[v],low[to]);
        }
        low[v]=min(low[v],dfn[to]);
    }
    if(low[v]==dfn[v]&&edge!=-1) isbridge[edge]=true;
}
void dfs2(int v)
{
	bel[v]=bcc_cnt;
    dfn[v]=1;
    sz[bcc_cnt]++;
    for(auto e:G[v])
    {
        int to=adj(v,e);
        if(isbridge[e]) continue;
        if(!dfn[to]) dfs2(to);
    }
}
void tarjan()
{
    bcc_cnt=tot=0;
    memset(dfn,0,sizeof(dfn));
    memset(sz,0,sizeof(sz));
    memset(isbridge,false,sizeof(isbridge));
    for(int i=1;i<=n;i++)if(!dfn[i])dfs1(i,-1);
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            bcc_cnt++;
            dfs2(i);
        }
    }
}
int pre[maxn];
int dis[maxn],pos;
void go(int u,int f)
{
	pre[u]=1;
	dis[u]=dis[f]+1;
	if(dis[u]>dis[pos])pos=u;
	for(int v:tree[u])if(v!=f)
	{
		go(v,u);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)G[i].clear(),tree[i].clear(),sz[i]=0;
    mcnt=0;
    for(int i=1;i<=m;++i)
    {
    	int u,v;
    	scanf("%d%d",&u,&v);
    	++u;++v;
    	add_edge(u,v);
	}
	tarjan();
	for(int i=1;i<=m;++i)
	{
		if(bel[U[i]]!=bel[V[i]])
		{
			tree[bel[U[i]]].push_back(bel[V[i]]);
			tree[bel[V[i]]].push_back(bel[U[i]]);
		}
	}
	int ans=0;
	for(int i=1;i<=bcc_cnt;++i)if(!pre[i])
	{
		++ans;
		pos=0;
		go(i,0);
		go(pos,0);
		ans+=dis[pos]-1;
	}
	ans--;
	printf("%d\n",ans);
}