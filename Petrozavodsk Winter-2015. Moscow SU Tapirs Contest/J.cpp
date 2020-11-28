#include<bits/stdc++.h>
#define maxn 4005
using namespace std;
typedef long long ll;
int m;
int L[maxn],R[maxn],X[maxn];
int a[maxn],n,co[maxn];
vector< pair<int,ll> > g[maxn];
void addedge(int u,int v,ll w)
{
    g[u].push_back(make_pair(v,w));
}
int inq[maxn],CNT[maxn];
ll dis[maxn];
bool spfa()
{
    queue<int> q;
    memset(inq,0,sizeof(inq));
    for(int i=1;i<=n*2;++i)dis[i]=0,inq[i]=1,q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=0;
        for(auto p:g[u])
        {
            int v=p.first;
            ll w=p.second;
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                if(!inq[v])q.push(v),inq[v]=1,++CNT[v];
                if(CNT[v]>n)return 0;
            }
        }
    }
    return 1;
}
void sssp()
{
    queue<int> q;
    memset(inq,0,sizeof(inq));
    for(int i=1;i<=n*2;++i)dis[i]=(ll)1e18;
    q.push(1);inq[1]=0;dis[1]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=0;
        for(auto p:g[u])
        {
            int v=p.first;
            ll w=p.second;
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                if(!inq[v])q.push(v),inq[v]=1;
            }
        }
    }
}
void mindist()
{
    for(int i=1;i<=n*2;++i)g[i].clear();
    for(int i=2;i<=n*2;++i)addedge(i,i-1,0);
    for(int i=1;i<=m;++i)
    {
        addedge(L[i]*2-1,R[i]*2,X[i]);
        addedge(R[i]*2,L[i]*2-1,-X[i]);
    }
    for(int i=1;i<n*2;++i)if(!co[i])addedge(i,i+1,0);
    sssp();
    printf("%lld ",dis[n*2]);
}
void maxdist()
{
    for(int i=1;i<=n*2;++i)g[i].clear();
    for(int i=2;i<=n*2;++i)addedge(i-1,i,0);
    for(int i=1;i<=m;++i)
    {
        addedge(L[i]*2-1,R[i]*2,-X[i]);
        addedge(R[i]*2,L[i]*2-1,X[i]);
    }
    for(int i=1;i<n*2;++i)if(!co[i])addedge(i,i+1,0);
    sssp();
    printf("%lld ",-dis[n*2]);
}
int main()
{
    scanf("%d",&m);
    a[++n]=0;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&L[i],&R[i],&X[i]);
        a[++n]=L[i];
        a[++n]=R[i];
    }
    sort(a+1,a+n+1);
    n=unique(a+1,a+n+1)-a-1;
    for(int i=2;i<=n*2;++i)addedge(i,i-1,0);
    for(int i=1;i<=m;++i)
    {
        L[i]=lower_bound(a+1,a+n+1,L[i])-a;
        R[i]=lower_bound(a+1,a+n+1,R[i])-a;
        co[L[i]*2-1]++;co[R[i]*2]--;
        addedge(L[i]*2-1,R[i]*2,X[i]);
        addedge(R[i]*2,L[i]*2-1,-X[i]);
    }
    for(int i=1;i<=n*2;++i)co[i]+=co[i-1];
    for(int i=1;i<n*2;++i)if(!co[i])addedge(i,i+1,0);
    if(!spfa())
    {
        puts("-1 -1");
    }
    else
    {
        maxdist();
        mindist();
    }
}
