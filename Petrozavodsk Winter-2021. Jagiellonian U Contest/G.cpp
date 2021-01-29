#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define MAXM 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,tot,t,tt,bcc_cnt,mcnt;
vector<int> G[MAXN];
int st[MAXN],dfn[MAXN],low[MAXN];
int U[MAXM],V[MAXM],sz[MAXN];
bool isbridge[MAXM];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
//bridge tree:
//edge-biconnected components are connected by bridges
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
    dfn[v]=1;
    sz[bcc_cnt]++;
    for(auto e:G[v])
    {
        int to=adj(v,e);
        if(isbridge[e]) continue;
        if(!dfn[to]) dfs2(to);
    }
}
int tarjan()
{
    bcc_cnt=tot=0;
    for(int i=1;i<=n;i++) dfn[i]=0;
    for(int i=1;i<=n;i++) sz[i]=0;
    for(int i=1;i<=m;i++) isbridge[i]=false;
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs1(i,-1);
    for(int i=1;i<=n;i++) dfn[i]=0;
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            bcc_cnt++;
            dfs2(i);
        }
    }
    return bcc_cnt;
}
int calc(int sz)
{
    int res=pow_mod(k-1,sz);
    if(sz&1) dec(res,k-1); else add(res,k-1);
    return res;
}
int main()
{
    scanf("%d",&tt);
    while(tt--)
    {
        scanf("%d%d%d",&n,&m,&k);
        int inv=pow_mod(k,MOD-2);
        for(int i=1;i<=n;i++) G[i].clear();
        mcnt=0;
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add_edge(u,v);
        }
        tarjan();
        int ans=(sz[1]==1?k:calc(sz[1]));
        for(int i=2;i<=bcc_cnt;i++)
        {
            if(sz[i]==1) ans=1LL*ans*(k-1)%MOD;
            else ans=1LL*ans*calc(sz[i])%MOD*inv%MOD*(k-1)%MOD;
        }
        printf("%d\n",ans);
    }
    return 0;
}

