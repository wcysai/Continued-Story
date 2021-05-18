#include<bits/stdc++.h>
#define maxn 1005
typedef long double db;
using namespace std;
const db eps = 1e-10;
int dcmp(db x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
struct Point
{
    db x,y;
    Point(db x=0,db y=0):x(x),y(y){}
    void read()
    {
        double X,Y;
        scanf("%lf%lf",&X,&Y);
        x=X;y=Y;
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
db Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
db Length(Vector A)
{
    return sqrt(Dot(A,A));
}
db Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
Point GetLineIntersection(Point p,Vector v,Point q,Vector w)
{
    return p+v*Cross(w,p-q)/Cross(v,w);
}
bool Onsegment(Point p,Point a1,Point a2)
{
    return dcmp(Dot(a1-p,a2-p))<0;
}
int n,m;
Point a[maxn],S,T;
vector<Point> A[maxn];
bool operator < (Point A,Point B)
{
    db la=Length(A-S);
    db lb=Length(B-S);
    return la<lb;
}
int main()
{
    scanf("%d%d",&n,&m);
    S.read();T.read();
    for(int i=1;i<=n;++i)a[i].read();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<i;++j)
        {
            if(dcmp(Cross(a[i]-a[j],S-T))==0)continue;
            Point u=GetLineIntersection(a[i],a[j]-a[i],S,T-S);
            if(Onsegment(u,S,T))
            {
                A[i].push_back(u);
                A[j].push_back(u);
            }
        }
    }
    for(int i=1;i<=n;++i)sort(A[i].begin(),A[i].end());
    while(m--)
    {
        int h,k;
        scanf("%d%d",&h,&k);
        if((int)(A[h].size())<k)
        {
            puts("-1");
        }
        else
        {
            printf("%.10f %.10f\n",(double)A[h][k-1].x,(double)A[h][k-1].y);
        }
    }
    return 0;
}