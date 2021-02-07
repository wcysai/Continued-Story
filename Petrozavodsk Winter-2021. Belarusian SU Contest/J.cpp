#include<bits/stdc++.h>
#define MAXN 300005
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
vector<int> c1,c2,ans;
bool dfs(int v,int c)
{
    if(c==1) c1.push_back(v); else c2.push_back(v);
    color[v]=c;
    for(auto to:G[v])
    {
        if(color[to]==c) return false;
        if(!color[to]&&!dfs(to,-c)) return false;
    }
    return true;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    bool f=true;
    for(int i=1;i<=n;i++)
    {
        if(!color[i])
        {
            c1.clear(); c2.clear();
            if(dfs(i,1))
            {
                if(c1.size()<c2.size()) for(auto x:c1) ans.push_back(x);
                else for(auto x:c2) ans.push_back(x);
            }
            else {f=false; break;}
        }
    }
    if(!f) puts("-1");
    else
    {
        printf("%d\n",(int)ans.size());
    }
    return 0;
}