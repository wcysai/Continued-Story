#include<bits/stdc++.h>
#define maxn 305
using namespace std;
const double eps = 1e-8;
int dcmp(double x)
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
double sqr(double x){return x*x;}
double dist(Point A,Point B)
{
    return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}
double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
double area(Point A,Point B,Point C)
{
    return fabs(Cross(C-A,B-A))/2;
}
bool Onleft(Point A,Point B,Point C)//A is on left of BC
{
    return Cross(A-B,C-B)<0;
}
int n;
Point a[maxn];
double d1[maxn],d2[maxn];
int cnt1,cnt2;
double S,ans;
void solve(int x,int y)
{
    double len=dist(a[x],a[y]);
    double lim=2*S/len;
    cnt1=cnt2=0;
    for(int k=1;k<=n;++k)if(k!=x&&k!=y)
    {
        if(Onleft(a[k],a[x],a[y]))
        {
            double ar=area(a[k],a[x],a[y]);
            d1[++cnt1]=2*ar/len;
        }
        else
        {
            double ar=area(a[k],a[x],a[y]);
            d2[++cnt2]=2*ar/len;
        }
    }
    sort(d1+1,d1+cnt1+1);
    sort(d2+1,d2+cnt2+1);
    int j=cnt2;
    for(int i=1;i<=cnt1;++i)
    {
        while(j>0&&dcmp(d1[i]+d2[j]-lim)>0)--j;
        if(j)ans=max(ans,fabs(len*(d1[i]+d2[j]))/2.0);
    }
}
int main()
{
    scanf("%d%lf",&n,&S);
    for(int i=1;i<=n;++i)a[i].read();
    ans=0;
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)solve(i,j);
    printf("%.10f\n",ans);
}