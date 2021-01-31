#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,w,root;
int f[MAXN],c[MAXN],u[MAXN];
int need[MAXN],ans;
vector<int> G[MAXN];
void dfs(int v,int p)
{
    if(!v) need[v]=w; else need[v]=max(need[p]-u[v],c[v]-u[v]);
    ans=min(ans,need[v]);
    for(auto to:G[v]) dfs(to,v);
}
int main()
{
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d%d",&f[i],&c[i],&u[i]);
        G[f[i]].push_back(i);
    }
    ans=w;
    dfs(0,-1);
    printf("%d\n",ans);
    return 0;
}