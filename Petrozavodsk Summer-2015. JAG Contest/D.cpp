#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n,m;
struct edge{int to,cost;};
vector<edge> G[MAXN];
int dp[MAXN][MAXN];
int s[MAXN];
int tmp[MAXN];
int root,leaf[MAXN];
int cur[MAXN];
priority_queue<ll> pque;
void add_edge(int u,int v,int c)
{
    G[u].push_back((edge){v,c});
    G[v].push_back((edge){u,c});
}
ll dfs(int v,int p,int mult)
{
    ll maxi=0;
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(to==p) continue;
        ll tmp=dfs(to,v,mult)+1LL*mult*cost;
        pque.push(min(maxi,tmp));
        maxi=max(maxi,tmp);
    }
    return maxi;
}
vector<int> v;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n-1;i++)
    {
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        add_edge(u,v,c);
    }
    for(int i=1;i<=n;i++) scanf("%d",&s[i]);
    for(int i=1;i<=n;i++) pque.push(dfs(i,0,s[i]));
    ll ans=0;
    while(m&&pque.size())
    {
        ll v=pque.top(); pque.pop();
        ans+=v; m--;
    }
    printf("%lld\n",ans);
    return 0;
}