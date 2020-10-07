#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<P> G[MAXN];
bool vis[MAXN][2];
char str[3];
int u[MAXN],v[MAXN],x[MAXN];
void add_edge(int u,int v,int x)
{
    G[u].push_back(P(v,x));
    G[v].push_back(P(u,x));
}
void dfs(int v,int c)
{
    vis[v][c]=true;
    for(auto e:G[v])
    {
        int to=e.F,cc=e.S;
        if(c==cc&&!vis[to][!c]) dfs(to,!c);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%s",&u[i],&v[i],str);
        x[i]=(str[0]=='r');
        add_edge(u[i],v[i],x[i]);
    }
    bool flag=false;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<2;j++)
        {
            memset(vis,false,sizeof(vis));
            dfs(i,j);
            bool f=true;
            for(int k=0;k<m;k++) if(!vis[u[k]][x[k]]&&!vis[v[k]][x[k]]) f=false;
            for(int k=1;k<=n;k++) if(vis[k][0]&&vis[k][1]) f=true;
            if(f) flag=true;
        }
    }
    if(flag) puts("Yes"); else puts("No");
}
