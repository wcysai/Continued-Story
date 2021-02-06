#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> G[MAXN];
int has[MAXN];
vector<P> ans;
vector<int> sons[MAXN];
void dfs(int v,int p)
{
    has[v]=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        if(has[to]==0) sons[v].push_back(to);
        else
        {
            ans.push_back(P(v,has[to]));
        }
    }
    while(sons[v].size()>=2)
    {
        int u=sons[v].back(); sons[v].pop_back();
        int uu=sons[v].back(); sons[v].pop_back();
        ans.push_back(P(u,uu));
    }
    if(sons[v].size()) has[v]=sons[v].back();
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
    dfs(1,0);
    assert((int)ans.size()==(n-1)/2);
    printf("%d\n",(int)ans.size());
    for(auto p:ans) printf("%d %d\n",p.F,p.S);
    return 0;
}