#include<bits/stdc++.h>
#define MAXN 55
#define MAXV 205
#define INF 1000000000
#define INF2 1000000000000LL
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
struct edge{int to,cap; ll cost; int rev;};
int n,m,V,s[MAXV],e[MAXV];
ll w[MAXV];
ll dist[MAXV];
int prevv[MAXV],preve[MAXV];
vector<edge> G[MAXV];
bool inque[MAXV];
int sb[MAXN][MAXN],sw[MAXN][MAXN],l[MAXN],r[MAXN],L[MAXN],R[MAXN];
void add_edge(int from,int to,int cap,ll cost)
{
    G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1});
}
ll min_cost_flow(int s,int t,int f)
{
    ll res=0;
    while(true)
    {
        queue<int>que;
        fill(dist+1,dist+V+1,INF2);
        fill(inque+1,inque+V+1,false);
        dist[s]=0;
        que.push(s);
        while(!que.empty())
        {
            int u=que.front(); que.pop();
            for(int i=0;i<(int)G[u].size();i++)
            {
                if(G[u][i].cap>0&&dist[u]+G[u][i].cost<dist[G[u][i].to])
                {
                    dist[G[u][i].to]=dist[u]+G[u][i].cost;
                    prevv[G[u][i].to]=u;
                    preve[G[u][i].to]=i;
                    if(!inque[G[u][i].to])
                    {
                        inque[G[u][i].to]=true;
                        que.push(G[u][i].to);
                    }
                }
            }
            inque[u]=false;
        }
        if(dist[t]==INF2) return -1;
        if(dist[t]>=0) return res;
        int d=f;
        for(int v=t;v!=s;v=prevv[v]) d=min(d,G[prevv[v]][preve[v]].cap);
        f-=d;
        res+=1LL*d*dist[t];
        for(int v=t;v!=s;v=prevv[v])
        {
            edge &e=G[prevv[v]][preve[v]];
            e.cap-=d;
            G[v][e.rev].cap+=d;
        }
    }
    return res;
}
int cost[2*MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&sb[i][j]);
    ll ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&sw[i][j]);
            ans+=sw[i][j];
        }
    for(int i=1;i<=n;i++) scanf("%d%d",&l[i],&r[i]);
    for(int i=1;i<=m;i++) scanf("%d%d",&L[i],&R[i]);
    V=n+m+4;
    int s=n+m+1,t=n+m+2,S=t+1,T=S+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            add_edge(i,n+j,1,-sw[i][j]);
            add_edge(i,n+j,1,sb[i][j]);
        }
    for(int i=1;i<=n;i++)
    {
        add_edge(s,i,r[i]-l[i],0);//
        add_edge(s,i,n+l[i],-INF);
        ans+=1LL*(n+l[i])*INF;
    }
    for(int i=1;i<=m;i++)
    {
        add_edge(n+i,t,R[i]-L[i],0);
        add_edge(n+i,t,m+L[i],-INF);
        ans+=1LL*(m+L[i])*INF;
    }
    printf("%lld\n",ans+min_cost_flow(s,t,INF));
    return 0;
}