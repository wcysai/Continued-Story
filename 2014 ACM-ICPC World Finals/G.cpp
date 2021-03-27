#include<bits/stdc++.h>
#define MAXN 405
#define MAXM 1000005
#define INF 2000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,d[MAXN][MAXN];
vector<int> v;
int dfn[MAXN],low[MAXN],st[MAXN],vis[MAXN],cmp[MAXN];
int cnt,tot,t;
vector<int> G[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
}
void dfs(int v)
{
    dfn[v]=low[v]=++tot;
    vis[v]=1;
    st[t++]=v;
    for(auto to:G[v])
    {
        if(!vis[to])
        {
            dfs(to);
            low[v]=min(low[v],low[to]);
        }
        else if(vis[to]==1) low[v]=min(low[v],dfn[to]);
    }
    if(dfn[v]==low[v])
    {
        int u;
        do
        {
            u=st[t-1]; t--;
            cmp[u]=cnt;
            vis[u]=2;
        } while (u!=v);
        cnt++;
    }
}
int tarjan()
{
    t=tot=cnt=0;
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=2*n;i++) if(!dfn[i]) dfs(i);
    return cnt;
}
bool check(int x,int y)
{
    for(int i=1;i<=2*n;i++) G[i].clear();
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            if(d[i][j]>x)
            {
                add_edge(i,n+j);
                add_edge(j,n+i);
            }
            if(d[i][j]>y)
            {
                add_edge(n+i,j);
                add_edge(n+j,i);
            }
        }
    tarjan();
    for(int i=1;i<=n;i++) if(cmp[i]==cmp[n+i]) return false;
    return true;
}
int main()
{
    scanf("%d",&n);
    int ans=INF;
    for(int i=1;i<=n-1;i++)
        for(int j=1;j<=n-i;j++)
        {
            int x;
            scanf("%d",&x);
            d[i][i+j]=d[i+j][i]=x;
            v.push_back(x);
            ans=max(ans,x);
        }
    v.push_back(0);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    int l=-1,r=(int)v.size()-1;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(check(v[0],v[mid])) r=mid; else l=mid;
    }
    ans=min(ans,v[0]+v[r]);
    for(int i=1;i<(int)v.size();i++)
    {
        while(r>i&&check(v[i],v[r-1])) r--;
        if(r<i) break; else ans=min(ans,v[i]+v[r]);
    }
    assert(ans!=INF);
    printf("%d\n",ans);
    return 0;
}