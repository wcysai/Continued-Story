#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<int> G[MAXN];
int color[MAXN];
bool flag;
void dfs(int v)
{
    color[v]=1;
    for(auto to:G[v])
    {
        if(!color[to]) dfs(to);
        else if(color[to]==1) flag=true;
    }
    color[v]=2;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
    }
    if(n==1) {puts("-1"); return 0;}
    else if(m==0) {puts("2"); return 0;}
    else
    {
        flag=false;
        for(int i=1;i<=n;i++)
            if(!color[i])
                dfs(i);
        if(flag) puts("0"); else puts("1");
    }
    return 0;
}