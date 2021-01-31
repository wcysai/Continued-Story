#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,ll> P;
int n,m,q;
vector<P> G[MAXN];
ll val[MAXN];
int color[MAXN];
vector<ll> basis;
void dfs(int v,int p)
{
    color[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i].F;
        ll cost=G[v][i].S;
        if(to==p) continue;
        if(color[to]==0)
        {
            val[to]=val[v]^cost;
            dfs(to,v);
        }
        else if(color[to]==1)
        {
            basis.push_back(val[v]^val[to]^cost);
        }
    }
    color[v]=2;
}
ll bas[62];
void add_basis(ll x)
{
    for(int j=60;j>=0;j--)
    {
        if(x&(1ll<<j))
        {
            if(!bas[j])
            {
                bas[j]=x;
                break;
            }
            x^=bas[j];
        }
    }
}
ll query(ll x)
{
    for(int j=60;j>=0;j--)
    {
        if(x&(1ll<<j))
            if(bas[j]) x^=bas[j];
    }
    return x;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<m;i++)
    {
        int u,v;
        ll w;
        scanf("%d%d%lld",&u,&v,&w);
        G[u].push_back(P(v,w)); G[v].push_back(P(u,w));
    }
    dfs(1,0);
    for(auto x:basis) add_basis(x);
    for(int i=0;i<q;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        ll res=val[u]^val[v];
        printf("%lld\n",query(res));
    }
    return 0;
}