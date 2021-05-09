#include<bits/stdc++.h>
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
Vector operator * (Vector A,double k)
{
    return Vector(A.x*k,A.y*k);
}
Vector operator / (Vector A,double k)
{
    return Vector(A.x/k,A.y/k);
}
double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
struct Line
{
    Point p;
    Vector v;
    double ang;
    Line(){}
    Line(Point p,Vector v):p(p),v(v)
    {
        ang=atan2(v.y,v.x);
    }
    inline bool operator < (const Line &L)const
    {
        return ang<L.ang;
    }
    inline Point point(double t)
    {
        return p+v*t;
    }
};
Point GetLineIntersection(Point p,Vector v,Point q,Vector w)
{
    return p+v*Cross(w,p-q)/Cross(v,w);
}
inline Point GetLineIntersection(Line a,Line b)
{
    return GetLineIntersection(a.p,a.v,b.p,b.v);
}
bool Onleft(const Line &L,const Point &p)
{
    return dcmp(Cross(L.v,p-L.p))>0;
}
vector<Point> HalfPlaneIntersection(vector<Line> L)
{
    int n=L.size();
    sort(L.begin(),L.end());
    int first,last;
    vector<Point> p(n);
    vector<Line> q(n);
    vector<Point> ans;
    q[first=last=0]=L[0];
    for(int i=1;i<n;++i)
    {
        while(first<last&&!Onleft(L[i],p[last-1]))last--;
        while(first<last&&!Onleft(L[i],p[first]))first++;
        q[++last]=L[i];
        if(fabs(Cross(q[last].v,q[last-1].v))<eps)
        {
            last--;
            if(Onleft(q[last],L[i].p))q[last]=L[i];
        }
        if(first<last)p[last-1]=GetLineIntersection(q[last-1],q[last]);
    }
    while(first<last&&!Onleft(q[first],p[last-1]))last--;
    if(last-first<=1)return ans;
    p[last]=GetLineIntersection(q[last],q[first]);
    for(int i=first;i<=last;++i)ans.push_back(p[i]);
    return ans;
}
double sqr(double x){return x*x;}
double dist(Point A,Point B)
{
    return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}
double getlen(vector<Point> p)
{
    int n=p.size();
    double ans=0;
    for(int i=0;i<n;++i)ans+=dist(p[i],p[(i+1)%n]);
    return ans;
}
int n;
Vector d;
vector<Line> A;
int main()
{
    scanf("%d",&n);
    vector<Point> p(n),q(n);
    for(int i=0;i<n;++i)p[i].read();
    d.read();
    for(int i=0;i<n;++i)q[i]=p[i]+d;
    for(int i=0;i<n;++i)
    {
        A.push_back(Line(p[(i+1)%n],p[i]-p[(i+1)%n]));
        A.push_back(Line(q[(i+1)%n],q[i]-q[(i+1)%n]));
    }
    double ans=getlen(p)+getlen(q)-getlen(HalfPlaneIntersection(A));
    printf("%.10f\n",ans);
}