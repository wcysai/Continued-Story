#include<bits/stdc++.h>
#define MAXN 305
#define INF 1e15
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
int n;
db w[MAXN][MAXN];
P init;
db get_dist(P p,P q)
{
    return sqrt((p.F-q.F)*(p.F-q.F)+(p.S-q.S)*(p.S-q.S));
}
P s[MAXN],t[MAXN];
db km(int n,int m)
{
    vector<db> u(n+1),v(m+1);
    vector<int> p(m+1),way(m+1);
    for(int i=1;i<=n;i++)
    {
        p[0]=i;
        int j0=0;
        vector<db> minv(m+1,INF);
        vector<char> used(m+1,false);
        do
        {
            used[j0]=true;
            int i0=p[j0],j1;
            db delta=INF;
            for(int j=1;j<=m;j++)
                if(!used[j])
                {
                    db cur=w[i0][j]-u[i0]-v[j];
                    if(cur<minv[j]) minv[j]=cur,way[j]=j0;
                    if(minv[j]<delta) delta=minv[j],j1=j;
                }
            for(int j=0;j<=m;j++) if(used[j]) u[p[j]]+=delta,v[j]-=delta; else minv[j]-=delta;
            j0=j1;
        } while (p[j0]!=0);
        do
        {
            int j1=way[j0];
            p[j0]=p[j1];
            j0=j1;
        } while (j0);
    }
    db res=0;
    for(int i=1;i<=m;i++) res+=w[p[i]][i];
    return res;
}
int main()
{
    scanf("%d",&n);
    scanf("%d%d",&init.F,&init.S);
    for(int i=1;i<=n;i++) scanf("%d%d%d%d",&s[i].F,&s[i].S,&t[i].F,&t[i].S);
    double ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            double cost=get_dist(s[i],t[j]);
            w[i][j]=cost;
            if(i==j) ans+=cost;
        }
    }
    printf("%.15Lf\n",ans+km(n,n));
    return 0;
}