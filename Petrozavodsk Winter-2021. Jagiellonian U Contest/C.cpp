#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n;
vector<int> G[MAXN];
int fa[MAXN];
int color[MAXN];
vector<int> cyc;
void dfs(int v,int p)
{
    color[v]=1;
    fa[v]=p;
    for(auto to:G[v])
    {
        if(to==p) continue;
        if(!color[to]) dfs(to,v); 
        else if(color[to]==1)
        {
            int now=v;
            cyc.push_back(now);
            while(true)
            {
                now=fa[now];
                cyc.push_back(now);
                if(now==to) break;
            }
        }
    }
    color[v]=2;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear(),color[i]=0;
        for(int i=0;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v); G[v].push_back(u);
        }
        cyc.clear();
        dfs(1,0);
        int ans=3;
        int res=0;
        for(int i=1;i<=n;i++) if((int)G[i].size()==1) res++;
        for(int i=0;i<(int)cyc.size();i++)
        {
            int x=i,y=i+1;
            if(y==(int)cyc.size()) y=0;
            x=(G[cyc[x]].size()==2?1:0);
            y=(G[cyc[y]].size()==2?1:0);
            ans=max(ans,res+x+y);
        }
        printf("%d\n",ans);
    }
    return 0;
}