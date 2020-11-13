#include<bits/stdc++.h>
#define mp(a,b) make_pair(a,b)
#define maxn 205
using namespace std;
const int inf = (int)(1e9+7);
int n,m,P;
int S[maxn*maxn],T[maxn*maxn],D[maxn*maxn],V[maxn*maxn];
struct edge
{
    int to,d,v;
    edge(int to=0,int d=0,int v=0):to(to),d(d),v(v){}
};
vector<edge> g[maxn];
int dis[2005][maxn];
int main()
{
    scanf("%d%d%d",&n,&m,&P);
    for(int i=0;i<=P;++i)
        for(int u=1;u<=n;++u)dis[i][u]=-inf;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d%d",&S[i],&T[i],&D[i],&V[i]);
        g[S[i]].push_back(edge(T[i],D[i],V[i]));
        g[T[i]].push_back(edge(S[i],D[i],V[i]));
    }
    dis[0][1]=0;
    for(int i=0;i<=P;++i)
    {
        for(int u=1;u<=n;++u)
        {
            for(edge e:g[u])
            {
                int to=e.to,d=e.d,v=e.v;
                dis[i+d][to]=max(dis[i+d][to],dis[i][u]+v);
            }
        }
    }
    double ans=0;
    for(int i=1;i<=m;++i)
    {
        for(int t=0;t<=P/2;++t)
        {
            int x=S[i],y=T[i],v=V[i],d=D[i];
            double k=2*max(dis[t][x],dis[t][y]);
            ans=max(ans,k+1.0*(P-2*t)*v/(1.0*d));
        }
    }
    printf("%.10f\n",ans);
}
