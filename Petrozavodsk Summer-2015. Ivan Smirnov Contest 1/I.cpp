#include<bits/stdc++.h>
#define maxn 5005
using namespace std;
int n;
double x[maxn],y[maxn],T;
double sqr(double x){return x*x;}
double dist(int a,int b)
{
    return sqrt(sqr(x[a]-x[b])+sqr(y[a]-y[b]));
}
bool used[maxn];
int Ans[maxn];
int main()
{
    srand(time(NULL));
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%lf%lf",&x[i],&y[i]);
    scanf("%lf",&T);
    for(int p=1;;++p)
    {
        for(int i=1;i<=n;++i)used[i]=0;
        int now=rand()%n+1;
        double ans=dist(0,now);
        Ans[1]=now;used[now]=1;
        for(int i=2;i<=(n+1)/2;++i)
        {
            int pos=0;
            double md=1e18;
            for(int j=1;j<=n;++j)if(!used[j]&&dist(now,j)<md)md=dist(now,j),pos=j;
            ans+=md;now=pos;used[now]=1;
            Ans[i]=now;
        }
        if(ans<T)
        {
            for(int i=1;i<=(n+1)/2;++i)printf("%d ",Ans[i]);
            return 0;
        }
    }
    assert(0);
}