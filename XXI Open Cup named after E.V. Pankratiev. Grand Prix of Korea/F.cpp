#include<bits/stdc++.h>
#define MAXV 500005
#define MAXE 1000005
#define INF 1000000000
#define INF2 1000000000000000000LL
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
void add_edge(int from,int to,int cap,ll cost)
{
    G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1});
}
ll min_cost_flow(int s,int t,int f)
{
    ll res=0;
    while(f>0)
    {
        queue<int>que;
        fill(dist,dist+V,INF2);
        fill(inque,inque+V,false);
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
int main()
{
    scanf("%d",&n);
    vector<int> dis;
    for(int i=0;i<n;i++) 
    {
        scanf("%d%d%lld",&s[i],&e[i],&w[i]);
        s[i]--; e[i]++;
        dis.push_back(s[i]); dis.push_back(e[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    int m=(int)dis.size();
    int S=m,T=S+1;
    V=T+1;  
    ll res=0;
    add_edge(S,0,2,0);
    add_edge(m-1,T,2,0);
    for(int i=0;i+1<m;i++) add_edge(i,i+1,INF,0);
    for(int i=0;i<n;i++)
    {
        int u=lower_bound(dis.begin(),dis.end(),s[i])-dis.begin();
        int v=lower_bound(dis.begin(),dis.end(),e[i])-dis.begin();
        add_edge(u,v,1,-w[i]);
        add_edge(S,v,1,0);
        add_edge(u,T,1,0);
    }
    printf("%lld\n",-min_cost_flow(S,T,2));
    return 0;
}
