#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long double db;
typedef long long ll;
typedef pair<db,int> P;
const db eps=1e-6;
int n,m;
vector<int> G[MAXN];
db dist[MAXN];
int cnt[MAXN];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for(int i=1;i<=n;i++) dist[i]=1e12;
    dist[n]=0;
    priority_queue<P,vector<P>,greater<P> > pque;
    pque.push(P(0,n));
    while(pque.size())
    {
        P p=pque.top(); pque.pop();
        double d=p.F;
        int v=p.S;
        if(d>dist[v]+eps) continue;
        for(auto to:G[v])
        {
            if(dist[to]>dist[v]+eps)
            {
                cnt[to]++;
                if(cnt[to]==1) dist[to]=m+dist[v]; else dist[to]=(dist[to]*(cnt[to]-1)+dist[v])/cnt[to];
                pque.push(P(dist[to],to));
            }
        }
    }
    printf("%.15Lf\n",dist[1]);
    return 0;
}