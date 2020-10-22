#include<bits/stdc++.h>
using namespace std;
const double PI=acos(-1.0);
const double eps=1e-7;
int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
struct Point
{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    inline void read()
    {
        scanf("%lf%lf",&x,&y);
    }
};
typedef Point Vector;
inline Vector operator + (Vector A,Vector B)
{
    return Vector(A.x+B.x,A.y+B.y);
}
inline Vector operator - (Vector A,Vector B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
inline Vector operator * (Vector A,double k)
{
    return Vector(A.x*k,A.y*k);
}
inline Vector operator / (Vector A,double k)
{
    return Vector(A.x/k,A.y/k);
}
inline double Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
inline double Length(Vector A)
{
    return sqrt(Dot(A,A));
}
inline double Angle(Vector A,Vector B)
{
    return acos(Dot(A,B)/Length(A)/Length(B));
}
inline double angle(Vector v)
{
    return atan2(v.y,v.x);
}
inline double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
inline Vector Unit(Vector x)
{
    return x/Length(x);
}
inline Vector Normal(Vector x)
{
    return Vector(-x.y,x.x)/Length(x);
}
inline Vector Rotate(Vector A,double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
inline bool operator < (Point a,Point b)
{
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
inline bool OnSegment(Point p,Point a1,Point a2)
{
    return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<=0;
}
struct Line
{
    Point p;
    Vector v;
    double ang;
    Line(){}
    Line(Point P,Vector v):p(P),v(v){ang=atan2(v.y,v.x);}
    inline Point point(double t)
    {
        return p+v*t;
    }
};
struct Circle
{
    Point c;
    double r;
    Circle(){}
    Circle(Point c,double r):c(c),r(r){}
    inline Point point(double a)
    {
        return Point(c.x+cos(a)*r,c.y+sin(a)*r);
    }
};
Point GetIntersection(Line a,Line b)
{
    Vector u=a.p-b.p;
    double t=Cross(b.v,u)/Cross(a.v,b.v);
    return a.p+a.v*t;
}
inline bool InCircle(Point x,Circle c)
{
    return dcmp(c.r-Length(c.c-x))>=0;
}
inline bool OnCircle(Point x,Circle c)
{
    return dcmp(c.r-Length(c.c-x))==0;
}
int getSegCircleIntersection(Line L,Circle C,Point *sol)
{
    Vector nor=Normal(L.v);
    Line pl=Line(C.c,nor);
    Point ip=GetIntersection(pl,L);
    double dis=Length(ip-C.c);
    if(dcmp(dis-C.r)>0)return 0;
    Point dxy=Unit(L.v)*sqrt(C.r*C.r-dis*dis);
    int ret=0;
    sol[ret]=ip+dxy;
    if(OnSegment(sol[ret],L.p,L.point(1)))ret++;
    sol[ret]=ip-dxy;
    if(OnSegment(sol[ret],L.p,L.point(1)))ret++;
    return ret;
}
double SegCircleArea(Circle C,Point a,Point b)
{
    double a1=angle(a-C.c);
    double a2=angle(b-C.c);
    double da=fabs(a1-a2);
    if(da>PI)da=2.0*PI-da;
    return dcmp(Cross(b-C.c,a-C.c))*da*C.r*C.r/2.0;
}
double PolyCircleArea(Circle C,Point *p,int n)
{
    double ret=0.0;
    Point sol[2];
    p[n]=p[0];
    for(int i=0;i<n;++i)
    {
        int cnt=getSegCircleIntersection(Line(p[i],p[i+1]-p[i]),C,sol);
        if(cnt==0)
        {
            if(!InCircle(p[i],C)||!InCircle(p[i+1],C))ret+=SegCircleArea(C,p[i],p[i+1]);
            else ret+=Cross(p[i+1]-C.c,p[i]-C.c)/2.0;
        }
        if(cnt==1)
        {
            if(InCircle(p[i],C)&&!InCircle(p[i+1],C))ret+=Cross(sol[0]-C.c,p[i]-C.c)/2.0,ret+=SegCircleArea(C,sol[0],p[i+1]);
            else ret+=SegCircleArea(C,p[i],sol[0]),ret+=Cross(p[i+1]-C.c,sol[0]-C.c)/2.0;
        }
        if(cnt==2)
        {
            if((p[i]<p[i+1])^(sol[0]<sol[1]))swap(sol[0],sol[1]);
            ret+=SegCircleArea(C,p[i],sol[0]);
            ret+=Cross(sol[1]-C.c,sol[0]-C.c)/2.0;
            ret+=SegCircleArea(C,sol[1],p[i+1]);
        }
    }
    return fabs(ret);
}
int n;
double r;
Point a[15];
double lx,rx,ly,ry;
double calc2(double x,double y)
{
    return PolyCircleArea(Circle(Point(x,y),r),a,n);
}
double getmin(double x)
{
    double res=1e9;
    for(int i=0;i<n;++i)
    {
        double Ax=a[i].x,Bx=a[i+1].x,Ay=a[i].y,By=a[i+1].y;
        if(Ax>Bx)swap(Ax,Bx),swap(Ay,By);
        if(dcmp(Ax-x)<=0&&dcmp(Bx-x)>=0)
        {
            if(dcmp(Ax-Bx)==0)res=min(res,Ay);
            else res=min(res,Ay+(By-Ay)/(Bx-Ax)*(x-Ax));
        }
    }
    return res;
}
double getmax(double x)
{
    double res=-1e9;
    for(int i=0;i<n;++i)
    {
        double Ax=a[i].x,Bx=a[i+1].x,Ay=a[i].y,By=a[i+1].y;
        if(Ax>Bx)swap(Ax,Bx),swap(Ay,By);
        if(dcmp(Ax-x)<=0&&dcmp(Bx-x)>=0)
        {
            if(dcmp(Ax-Bx)==0)res=max(res,Ay);
            else res=max(res,Ay+(By-Ay)/(Bx-Ax)*(x-Ax));
        }
    }
    return res;
}
double calc(double x,int tp=0)
{
    int cnt=0;
    double l=getmin(x),r=getmax(x);
    while(++cnt<=200)
    {
        double m1=l+(r-l)/3,m2=r-(r-l)/3;
        if(calc2(x,m1)<calc2(x,m2))l=m1;
        else r=m2;
    }
    if(tp)return l;
    return calc2(x,l);
}
int main()
{
    scanf("%d%lf",&n,&r);
    lx=1e9;ly=1e9;
    rx=-1e9;ry=-1e9;
    for(int i=0;i<n;++i)a[i].read(),lx=min(lx,a[i].x),ly=min(ly,a[i].y),rx=max(rx,a[i].x),ry=max(ry,a[i].y);
    a[n]=a[0];
    int cnt=0;
    //cerr<<lx<<" "<<ly<<" "<<rx<<" "<<ry<<endl;
    double l=lx,r=rx;
    while(++cnt<=200)
    {
        double m1=l+(r-l)/3,m2=r-(r-l)/3;
        if(calc(m1)<calc(m2))l=m1;
        else r=m2;
    }
    //cerr<<calc2(3,3)<<endl;
    //printf("%.6f %.6f\n",l,calc(l,1));
    printf("%.6f\n",calc(l));
}