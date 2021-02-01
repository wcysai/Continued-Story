#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MDO 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,f[MAXN],h[MAXN];
bool vis[MAXN];
int color[MAXN];
vector<P> st;
vector<int> G[MAXN],bG[MAXN];
bool dfs(int v,int c)
{
    color[v]=c;
    for(auto to:bG[v])
    {
        if(color[to]==c) return false;
        if(!color[to]&&!dfs(to,-c)) return false;
    }
    return true;
}
void solve(int l,int r)
{
    if(l+1>=r) return;
    if(G[l].size()&&G[l].back()==r) G[l].pop_back();
    if(!G[l].size())
    {
        if(color[r]==1) color[l+1]=2; else color[l+1]=1;
        solve(l+1,r); 
        return;
    }
    int v=G[l].back(); G[l].pop_back();
    assert(l<v&&v<r&&color[l]!=color[r]);
    color[v]=6-color[l]-color[r];
    solve(l,v); solve(v,r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&f[i],&h[i]);
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        while(f[i])
        {
            assert(st.size());
            P p=st.back(); st.pop_back();
            int d=min(p.F,f[i]);
            G[p.S].push_back(i); cnt++;
            bG[p.S].push_back(i); bG[i].push_back(p.S);
            f[i]-=d; p.F-=d;
            if(p.F) st.push_back(p);
        }
        if(h[i]) st.push_back(P(h[i],i));
    }
    if(!cnt)
    {
        puts("1");
        for(int i=1;i<=n;i++) printf("%d ",1);
        puts("");
        return 0;
    }
    memset(color,0,sizeof(color));
    bool f=true;
    for(int i=1;i<=n;i++) if(!color[i]&&!dfs(i,1)) f=false;
    if(f)
    {
        puts("2");
        for(int i=1;i<=n;i++) printf("%d ",(color[i]==1)?1:2);
        puts("");
        return 0;
    }
    puts("3");
    memset(color,0,sizeof(color));
    color[1]=1; color[n]=2;
    if(G[1].size()&&G[1].back()==n) G[1].pop_back();
    solve(1,n);
    for(int i=1;i<=n;i++) printf("%d ",color[i]);
    puts("");
    return 0;
}