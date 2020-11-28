#include<bits/stdc++.h>
#define MAXN 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> G[MAXN];
int fa[MAXN],dep[MAXN];
bool valid[MAXN];
void dfs(int v,int p,int d)
{
    fa[v]=p; dep[v]=d;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v,d+1);
    }
}
void solve(int k)//maximum number of alert groups with answer k
{
    for(int )
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1,0,0);
}