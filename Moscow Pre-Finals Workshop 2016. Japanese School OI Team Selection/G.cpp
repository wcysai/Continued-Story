#include<bits/stdc++.h>
#define maxn 1000005
typedef long long ll;
using namespace std;
ll ans;
int n;
struct edge
{
    int to,val;
    edge(int to=0,int val=0):to(to),val(val){}
};
bool operator < (edge A,edge B)
{
    return A.val>B.val;
}
bool vis[maxn];
vector<edge> g[maxn];
int stk[maxn],top;
void dfs(int u,int r)
{
    vis[u]=1;
    stk[++top]=u;
    if(g[u].size()>0)
    {
        if(g[u][0].to==r)
        {
            ll minv=(ll)1e9+7;
            for(int i=1;i<=top;++i)
            {
                int x=stk[i];
                if(g[x].size()>1)minv=min(minv,1ll*g[x][0].val-1ll*g[x][1].val);
                else minv=min(minv,1ll*g[x][0].val);
            }
            ans+=minv;
            if(top==n)ans=0;
            --top;
            return;
        }
        if(!vis[g[u][0].to])dfs(g[u][0].to,r);
    }
    --top;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(edge(i,y));
    }
    for(int i=1;i<=n;++i)sort(g[i].begin(),g[i].end());
    for(int i=1;i<=n;++i)
        for(int j=1;j<g[i].size();++j)ans+=g[i][j].val;
    for(int i=1;i<=n;++i)if(!vis[i])dfs(i,i);
    cout<<ans<<endl;
    return 0;
}
