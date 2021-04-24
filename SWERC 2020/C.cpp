#include<bits/stdc++.h>
#define maxn 1005
using namespace std;
const double eps = 1e-9;
int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
double sqr(double x){return x*x;}
double X,Y;
int n;
struct Point
{
    double x,y;
}a[maxn];
int e[maxn][maxn];
bool vis[maxn];
void dfs(int u,int t)
{
    vis[u]=1;
    for(int i=1;i<=n+2;++i)if(!vis[i]&&e[u][i])
    {
        dfs(i,t);
    }
}
bool check(double r)
{
    memset(e,0,sizeof(e));
    memset(vis,0,sizeof(vis));
    int S=n+1,T=n+2;
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)if(dcmp(sqr(a[i].x-a[j].x)+sqr(a[i].y-a[j].y)-4*r*r)<=0)e[i][j]=e[j][i]=1;
    for(int i=1;i<=n;++i)
    {
        if(dcmp(a[i].x-r)<0||dcmp(a[i].y+r-Y)>0)e[i][S]=e[S][i]=1;
        if(dcmp(a[i].y-r)<0||dcmp(a[i].x+r-X)>0)e[i][T]=e[T][i]=1;
    }
    dfs(S,T);
    if(vis[T])return 1;
    else return 0;
}
int main()
{
    scanf("%lf%lf",&X,&Y);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%lf%lf",&a[i].x,&a[i].y);
    double l=0,r=2000000;
    for(int cnt=1;cnt<=60;++cnt)
    {
        double mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid;
    }
    printf("%.10f\n",l);
}