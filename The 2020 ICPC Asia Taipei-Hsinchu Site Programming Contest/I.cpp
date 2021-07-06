#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,mcnt,bcc_cnt;
bool art[MAXN];
int dfn[MAXN],low[MAXN],st[MAXN],bccno[MAXN];
vector<int> G[MAXN];
int U[MAXM],V[MAXM];
bool isbridge[MAXM];
int ecnt[MAXM];
int t,l,tot;
void dfs(int v,int p,int &tot)
{
    dfn[v]=low[v]=++tot;
    for(auto to:G[v])
    {
        if(to==p) continue;
        if(!dfn[to])
        {
            dfs(to,v,tot);
            low[v]=min(low[v],low[to]);
            if(low[to]>=dfn[v])
            art[v]=(dfn[v]>1||dfn[to]>2);
        }
        else low[v]=min(low[v],dfn[to]);
    }
}
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
    st[t++]=v;
    for(auto e:G[v])
    {
        if(e==edge) continue;
        int to=adj(v,e);
        if(!dfn[to])
        {
            dfs1(to,e);
            low[v]=min(low[v],low[to]);
        }
        else low[v]=min(low[v],dfn[to]);
    }
    if(low[v]==dfn[v]&&edge!=-1) isbridge[edge]=true;
}
void dfs2(int v)
{
    dfn[v]=1;
    bccno[v]=bcc_cnt;
    for(auto e:G[v])
    {
        int to=adj(v,e);
        if(isbridge[e]) continue;
        if(!dfn[to]) dfs2(to);
    }
}
void tarjan_vertex()
{
    bcc_cnt=t=0;
    memset(dfn,0,sizeof(dfn));
    memset(art,false,sizeof(art));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,-1,tot=0);
    int art_cnt=0;
    for(int i=1;i<=n;i++) if(art[i]) art_cnt++;
    printf("%d ", art_cnt);
}
void tarjan_edge()
{
    mcnt=0;
    for(int i=1;i<=n;i++) G[i].clear();
    for(int i=1;i<=m;i++) add_edge(U[i],V[i]);
    bcc_cnt=tot=t=0;
    memset(dfn,0,sizeof(dfn));
    memset(isbridge,false,sizeof(isbridge));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs1(i,-1);
    memset(dfn,0,sizeof(dfn));
    int s=0;
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            bool f=false;
            for(auto e:G[i])
            {
                if(isbridge[e]) continue;
                f=true;
            }
            if(f) s++;
            bcc_cnt++;
            dfs2(i);
        }
    }
    int bridge_cnt=0;
    for(int i=1;i<=m;i++) if(isbridge[i]) bridge_cnt++;
    printf("%d ", bridge_cnt);
    memset(ecnt,0,sizeof(ecnt));
    for(int i=1;i<=m;i++)
        if(bccno[U[i]]==bccno[V[i]])
            ecnt[bccno[U[i]]]++;
    int maxi=1;
    for(int i=1;i<=bcc_cnt;i++) maxi=max(maxi,ecnt[i]);
    s+=bridge_cnt;
    int g=__gcd(s,maxi);
    s/=g; maxi/=g; 
    printf("%d %d\n",s,maxi);
}
int main()
{
    scanf("%d",&l);
    while(l--)
    {
        scanf("%d%d",&n,&m); mcnt=0;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&U[i],&V[i]);
            G[U[i]].push_back(V[i]); G[V[i]].push_back(U[i]);
        }
        tarjan_vertex(); tarjan_edge();
    }
    return 0;
}