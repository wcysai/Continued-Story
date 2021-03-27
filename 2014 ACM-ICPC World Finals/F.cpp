#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
const double eps = 1e-8;
double dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
struct Point
{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    void read()
    {
        scanf("%lf%lf",&x,&y);
    }
};
typedef Point Vector;
Vector operator + (Vector A,Vector B)
{
    return Vector(A.x+B.x,A.y+B.y);
}
Vector operator - (Vector A,Vector B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator * (Vector A,double k)
{
    return Vector(A.x*k,A.y*k);
}
Vector operator / (Vector A,double k)
{
    return Vector(A.x/k,A.y/k);
}
double Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
double Length(Vector A)
{
    return sqrt(Dot(A,A));
}
double sqr(double x){return x*x;}
double dist(Point A,Point B)
{
    return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}
int n,m;
Point a[maxn],b[maxn];
double at[maxn],bt[maxn];
double tim[maxn];
bool check(double r)
{
    int cnt=0;
    for(int i=1;i<=n;++i)tim[++cnt]=at[i];
    for(int i=1;i<=m;++i)if(dcmp(bt[i]-r)>0)tim[++cnt]=bt[i]-r;
    sort(tim+1,tim+cnt+1);
    int posa=1,posb=1;
    for(int i=1;i<cnt;++i)
    {
        double t1=tim[i],t2=tim[i+1];
        while(posa<n&&dcmp(t1-at[posa+1])>=0)posa++;
        while(posb<m&&dcmp(t1+r-bt[posb+1])>=0)posb++;
        if(posa>=n||posb>=m)return 0;
        Vector v1=(a[posa+1]-a[posa])/Length(a[posa+1]-a[posa]);
        Vector v2=(b[posb+1]-b[posb])/Length(b[posb+1]-b[posb]);
        Point s1=a[posa]+v1*(t1-at[posa]);
        Point s2=b[posb]+v2*(t1+r-bt[posb]);
        //cerr<<s1.x<<" "<<s1.y<<" "<<s2.x<<" "<<s2.y<<endl;
        double A=sqr(v1.x-v2.x)+sqr(v1.y-v2.y);
        double B=2*((v1.x-v2.x)*(s1.x-s2.x)+(v1.y-v2.y)*(s1.y-s2.y));
        double C=sqr(s1.x-s2.x)+sqr(s1.y-s2.y)-sqr(r);
        double delta=B*B-4*A*C;
        if(dcmp(delta)>=0)
        {
            delta=max(delta,0.0);
            double k1=(-B-sqrt(delta))/(2*A);
            double k2=(-B+sqrt(delta))/(2*A);
            if(k1>k2)swap(k1,k2);
            if(dcmp(k1)>=0&&dcmp(k1)<=t2-t1)return 1;
            if(dcmp(k2)>=0&&dcmp(k2)<=t2-t1)return 1;
            if(dcmp(k1)<=0&&dcmp(k2)>=t2-t1)return 1;
        }
    }
    return 0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)a[i].read();
    scanf("%d",&m);
    for(int i=1;i<=m;++i)b[i].read();
    for(int i=2;i<=n;++i)at[i]=at[i-1]+dist(a[i-1],a[i]);
    for(int i=2;i<=m;++i)bt[i]=bt[i-1]+dist(b[i-1],b[i]);
    double l=0,r=bt[m];
    //cerr<<check(1.5)<<endl;
    for(int cnt=1;cnt<=200;++cnt)
    {
        double mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid;
    }
    if(dcmp(l-bt[m])==0)puts("impossible");
    else printf("%.10f\n",l);
}