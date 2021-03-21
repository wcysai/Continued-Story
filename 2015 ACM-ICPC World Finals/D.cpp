#include<bits/stdc++.h>
#define maxn 10005
using namespace std;
const double eps = 1e-9;
const double PI = acos(-1.0);
int n,s;
double Ans[maxn];
int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
struct Ball
{
    double x,y,z,r;
    Ball(double x=0,double y=0,double z=0,double r=0):x(x),y(y),z(z),r(r){}
};
double under(Ball O,double z)
{
    if(dcmp(O.z-O.r-z)>0)return 0;
    if(dcmp(O.z+O.r-z)<0)return 4.0*PI*O.r*O.r*O.r/3.0;
    double r=O.r;
    z-=O.z;
    return 2.0*PI*r*r*r/3.0+PI*r*r*z-1.0/3.0*PI*z*z*z;
}
Ball a[maxn];
double check(double z)
{
    double ans=(double)100000*(double)100000*z;
    for(int i=1;i<=n;++i)ans-=under(a[i],z);
    return ans;
}
int main()
{
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;++i)
    {
        scanf("%lf%lf%lf%lf",&a[i].r,&a[i].x,&a[i].y,&a[i].z);
    }
    double tot=(double)100000*(double)100000*(double)100000;
    for(int i=1;i<=n;++i)tot-=under(a[i],100000);
    for(int k=1;k<=s;++k)
    {
        double l=Ans[k-1],r=100000;
        double goal=(double)(tot/(double)s*k);
        for(int cnt=1;cnt<=80;++cnt)
        {
            double mid=(l+r)/2;
            if(check(mid)<=goal)l=mid;
            else r=mid;
        }
        Ans[k]=l;
    }
    for(int i=1;i<=s;++i)printf("%.10f\n",(Ans[i]-Ans[i-1])/1000);
}