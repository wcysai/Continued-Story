#include<bits/stdc++.h>
#define MAXN 1005
#define MAXK 15
#define MAXV 1055
#define INF 1000000000000LL
#define INF2 10000000000000000LL
#define MOD 1000000007
#define F first
#define S second
#define source daskodas
#define sink daksoa
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
struct edge{int to,cap;ll cost; int rev;};
ll dist[MAXV],h[MAXV];
int prevv[MAXV],preve[MAXV];
int V,n,k,t;
int c[MAXN][MAXK];
int cnt[MAXK];
int choice[MAXN];
vector<edge> G[MAXV];
void add_edge(int from,int to,int cap,ll cost)
{
    G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1});
}
ll min_cost_flow(int s,int t,int f)
{
    ll res=0;
    fill(h+1,h+V+1,0);
    while(f>0)
    {
        priority_queue<P,vector<P>,greater<P> > que;
        fill(dist+1,dist+V+1,INF2);
        dist[s]=0;
        que.push(P(0,s));
        while(!que.empty())
        {
            P p=que.top(); que.pop();
            int v=p.second;
            if(dist[v]<p.first) continue;
            for(int i=0;i<(int)G[v].size();i++)
            {
                edge &e=G[v][i];
                if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to])
                {
                    dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                    prevv[e.to]=v;
                    preve[e.to]=i;
                    que.push(P(dist[e.to],e.to));
                }
            }
        }
        if(dist[t]==INF2) return -1;
        for(int v=1;v<=V;v++) h[v]+=dist[v];
        int d=f;
        for(int v=t;v!=s;v=prevv[v]) d=min(d,G[prevv[v]][preve[v]].cap);
        f-=d;
        res+=d*h[t];
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
    //freopen("5.in","r",stdin);
    scanf("%d%d%d",&n,&k,&t);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=k+1;j++)
            scanf("%d",&c[i][j]);
    ll ans=INF;
    for(int num=1;num<=n;num++) //enumerate on the number of candidates that vote for t
    {
        for(int i=1;i<=1000;i++) G[i].clear();
        memset(prevv,0,sizeof(prevv)); memset(preve,0,sizeof(preve));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=k+1;j++)
                add_edge(i,n+j,1,c[i][j]);
        V=n+k+3;
        int source=V-1,sink=V;
        for(int i=1;i<=n;i++) add_edge(source,i,1,0);
        for(int j=1;j<=k+1;j++)
        {
            if(j==t) add_edge(n+j,sink,num,0);
            else if(j==k+1) add_edge(n+j,sink,n,INF);
            else add_edge(n+j,sink,num-1,INF);
        }
        ll res=min_cost_flow(source,sink,n);
        assert(res!=-1);
        res-=INF*(n-num);
        if(res<ans)
        {
            ans=res;
            for(int i=1;i<=n;i++)
                for(auto e:G[i])
                {
                    if(e.to<n+1||e.to>n+k+1) continue;
                    if(e.cap==0) {choice[i]=e.to-n; break;}
                }
        }
    }
    printf("%lld\n",ans); 
    ll s=0;
    for(int i=1;i<=n;i++) 
    {
        assert(choice[i]>=1&&choice[i]<=k+1);
        s+=c[i][choice[i]];
        cnt[choice[i]]++;
        printf("%d%c",choice[i],i==n?'\n':' ');
    }
    for(int i=1;i<=k;i++) 
    {
        //printf("i=%d cnt=%d\n",i,cnt[i]);
        if(i!=t) assert(cnt[i]<cnt[t]);
    }
    return 0;
}