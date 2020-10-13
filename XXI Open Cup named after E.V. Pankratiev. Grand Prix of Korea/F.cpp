#include<bits/stdc++.h>
#define MAXV 500005
#define MAXE 1000005
#define INF 1000000000
#define INF2 1000000000000000000LL
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
struct edge{int to,cap; ll cost; int rev;};
ll dist[MAXV],h[MAXV];
int prevv[MAXV],preve[MAXV];
int n,s[MAXV],e[MAXV];
ll w[MAXV];
int V;
vector<edge> G[MAXV];
void add_edge(int from,int to,int cap,ll cost)
{
    assert(from<to);
    G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1});
}
ll min_cost_flow(int s,int t,int f)
{
    ll res=0;
    fill(h,h+V,INF2);
    h[0]=0;
    for(int i=0;i<V;i++)
    {
        for(auto e:G[i])
        {
            if(e.cap>0) h[e.to]=min(h[e.to],h[i]+e.cost);
        }
    }
    while(f>0)
    {
        priority_queue<P,vector<P>,greater<P> >que;
        fill(dist,dist+V,INF2);
        dist[s]=0;
        que.push(P(0,s));
        while(!que.empty())
        {
            P p=que.top(); que.pop();
            int v=p.second;
            if(dist[v]<p.first) continue;
            for(int i=0;i<G[v].size();i++)
            {
                edge &e=G[v][i];
                if(e.cap>0) assert(e.cost+h[v]-h[e.to]>=0);
                if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to])
                {
                    dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                    prevv[e.to]=v;
                    preve[e.to]=i;
                    que.push(P(dist[e.to],e.to));
                }
            }
        }
        if(dist[t]==INF2)
        {
            return -1;
        }
        for(int v=0;v<V;v++) h[v]+=dist[v];
        int d=f;
        for(int v=t;v!=s;v=prevv[v])
        {
            d=min(d,G[prevv[v]][preve[v]].cap);
        }
        f-=d;
        res+=1LL*d*h[t];
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
        s[i]--; 
        dis.push_back(s[i]); dis.push_back(e[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    int m=(int)dis.size();
    int S=0,T=m+1;
    V=T+1;
    ll res=0;
    add_edge(S,1,2,0);
    add_edge(m,T,2,0);
    for(int i=1;i<m;i++) add_edge(i,i+1,INF,0);
    for(int i=0;i<n;i++)
    {
        int u=lower_bound(dis.begin(),dis.end(),s[i])-dis.begin()+1;
        int v=lower_bound(dis.begin(),dis.end(),e[i])-dis.begin()+1;
        assert(u<v);
        add_edge(u,v,1,-w[i]);
    }
    res+=min_cost_flow(S,T,2);
    printf("%lld\n",-res);
    return 0;
}