#include<bits/stdc++.h>
#define maxn 1005
using namespace std;
const double eps = 1e-8;
int T,n;
double Y[maxn],X[maxn];
double sqr(double x){return x*x;}
double calc(double x,double y)
{
    double ans=0;
    for(int i=1;i<=n;++i)ans+=sqrt(sqr(x-X[i])+sqr(y-Y[i]));
    return ans;
}
double check(double x,int tp=0)
{
    double l=-1e6,r=1e6;
    while(r-l>eps)
    {
        double m1=l+(r-l)/3,m2=r-(r-l)/3;
        if(calc(x,m1)<calc(x,m2))r=m2;
        else l=m1;
    }
    if(tp)return l;
    return calc(x,l);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lf%lf",&X[i],&Y[i]);
        }
        //cerr<<calc(-3,0)<<" "<<calc(0,0)<<" "<<calc(0,1.732)<<endl;
        double l=-1e6,r=1e6;
        while(r-l>eps)
        {
            double m1=l+(r-l)/3,m2=r-(r-l)/3;
            //cerr<<m1<<" "<<m2<<" "<<check(m1)<<" "<<check(m2)<<endl;
            if(check(m1)<check(m2))r=m2;
            else l=m1;
        }
        double ansx=l,ansy=check(l,1);
        printf("%.6f %.6f\n",ansx,ansy);
    }
}
