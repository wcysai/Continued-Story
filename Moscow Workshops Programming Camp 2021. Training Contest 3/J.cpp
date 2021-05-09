#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 30
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,m;
int d[MAXN][MAXN],w[MAXN][MAXN];
int deg[MAXN];
void floyd_warshall()
{
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
int km(int n,int m)
{
    vector<int> u(n+1),v(m+1),p(m+1),way(m+1);
    for(int i=1;i<=n;i++)
    {
        p[0]=i;
        int j0=0;
        vector<int> minv(m+1,INF);
        vector<char> used(m+1,false);
        do
        {
            used[j0]=true;
            int i0=p[j0],delta=INF,j1;
            for(int j=1;j<=m;j++)
                if(!used[j])
                {
                    int cur=w[i0][j]-u[i0]-v[j];
                    if(cur<minv[j]) minv[j]=cur,way[j]=j0;
                    if(minv[j]<delta) delta=minv[j],j1=j;
                }
            for(int j=0;j<=m;j++) if(used[j]) u[p[j]]+=delta,v[j]-=delta; else minv[j]-=delta;
            j0=j1;
        }while(p[j0]!=0);
        do
        {
            int j1=way[j0];
            p[j0]=p[j1];
            j0=j1;
        }while(j0);
    }
    ll res=0;
    for(int i=1;i<=m;i++) res+=w[p[i]][i];
    return res;
}
int p[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            d[i][j]=(i==j?0:INF);
    int ans=0;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        if(!w) d[u][v]=d[v][u]=1;
        deg[u]++; deg[v]++;
        ans++;
    }
    floyd_warshall();
    vector<int> v;
    for(int i=1;i<=n;i++) if(deg[i]&1) v.push_back(i);
    assert((int)v.size()%2==0);
    int sz=(int)v.size();
    if(sz==0) {printf("%d\n",ans); return 0;}
    int res=INF;
    for(int iter=0;iter<1000;iter++)
    {
        random_shuffle(v.begin(),v.end());
        for(int i=0;i<sz/2;i++)
            for(int j=sz/2;j<sz;j++)
                w[i+1][j-sz/2+1]=d[v[i]][v[j]];
        res=min(res,km(sz/2,sz/2));
    }
    if(res==INF) puts("-1"); else printf("%d\n",ans-res);
    return 0;
}
