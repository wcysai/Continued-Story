#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
const double eps=1e-7;
int N,M,m,n;
struct Point
{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
}a[maxn];
Point operator - (Point A,Point B)
{
    return Point(A.x-B.x,A.y-B.y);
}
bool operator < (Point A,Point B)
{
    return A.x<B.x||(A.x==B.x&&A.y<B.y);
}
double Cross(Point A,Point B)
{
    return A.x*B.y-A.y*B.x;
}
Point ch[maxn];
int cnt;
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)
    {
        double A,B,C;
        scanf("%lf%lf%lf",&C,&A,&B);
        if((A+B)/2<C)continue;
        ++n;
        a[n].x=A/C;a[n].y=(A/C+B/C)/2;
    }
    a[++n]=Point(1,1);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i)
    {
        while(m>1&&Cross(ch[m]-ch[m-1],a[i]-ch[m-1])>0)m--;
        ch[++m]=a[i];
    }
    double mxy=0;
    int mxid=0;
    for(int i=1;i<=M;++i)
    {
        if(ch[i].y>=mxy)
        {
            mxy=ch[i].y;
            mxid=i;
        }
    }
    while(M--)
    {
        double s,l;
        scanf("%lf%lf",&s,&l);
        l/=s;
        if(l<ch[mxid].x)
        {
            printf("%.10f\n",mxy*s);
        }
        else
        {
            int L=mxid,R=m,ans=m;
            while(L<=R)
            {
                int M=(L+R)>>1;
                if(l<=ch[M].x-eps)ans=M,R=M-1;
                else L=M+1;
            }
            int u=ans-1;
            double lamda=(l-ch[u+1].x)/(ch[u].x-ch[u+1].x);
            printf("%.10f\n",(ch[u].y*lamda+ch[u+1].y*(1-lamda))*s);
        }
    }
}
