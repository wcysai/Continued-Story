#include<bits/stdc++.h>
const double eps = 1e-11;
using namespace std;
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
double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
int n;
vector<Point> A;
double L,R,O,G;
Point bcenter(vector<Point> p)
{
    int n=p.size();
    Point tmp,g=Point(0,0);
    double sumArea=0,area;
    for(int i=2;i<n;++i)
    {
        area=Cross(p[i-1]-p[0],p[i]-p[0]);
        sumArea+=area;
        tmp.x=p[0].x+p[i-1].x+p[i].x;
        tmp.y=p[0].y+p[i-1].y+p[i].y;
        g.x+=tmp.x*area;
        g.y+=tmp.y*area;
    }
    g.x/=(sumArea*3.0);
    g.y/=(sumArea*3.0);
    return g;
}
double PolygonArea(vector<Point> p)
{
    int n=p.size();
    double area=0;
    for(int i=1;i<n-1;++i)area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return fabs(area)/2;
}
vector<Point> rev(vector<Point> A)
{
    vector<Point> B;
    B.clear();
    int n=A.size();
    B.push_back(A[0]);
    for(int i=A.size()-1;i>0;--i)B.push_back(A[i]);
    return B;
}
int main()
{
    scanf("%d",&n);
    L=10000;R=-10000;
    for(int i=1;i<=n;++i)
    {
        Point p;
        p.read();
        A.push_back(p);
        if(i==1)O=p.x;
        if(fabs(p.y)<1e-8)
        {
            L=min(L,p.x);
            R=max(R,p.x);
        }
    }
    if(Cross(A[0]-Point(L,0),A[1]-Point(L,0))<0)
    {
        A=rev(A);
    }
    G=bcenter(A).x;
    double s=PolygonArea(A);
    //cerr<<s<<endl;
    if(dcmp(O-L)<0)
    {
        if(dcmp(G-L)<0)
        {
            puts("unstable");
        }
        else if(dcmp(G-L)>=0&&dcmp(G-R)<=0)
        {
            double a=0;
            double b=s*fabs(L-G)/fabs(L-O);
            printf("%d .. %d\n",(int)floor(a),(int)ceil(b));
        }
        else if(dcmp(G-R)>0)
        {
            double a=s*fabs(R-G)/fabs(R-O);
            double b=s*fabs(L-G)/fabs(L-O);
            printf("%d .. %d\n",(int)floor(a),(int)ceil(b));
        }
    }
    else if(dcmp(O-L)==0)
    {
        if(dcmp(G-L)<0)
        {
            puts("unstable");
        }
        else if(dcmp(G-L)>=0&&dcmp(G-R)<=0)
        {
            printf("0 .. inf\n");
        }
        else if(dcmp(G-R)>0)
        {
            double a=s*fabs(R-G)/fabs(R-O);
            printf("%d .. inf\n",(int)floor(a));
        }
    }
    else if(dcmp(O-R)==0)
    {
        if(dcmp(G-L)<0)
        {
            double a=s*fabs(L-G)/fabs(L-O);
            printf("%d .. inf\n",(int)floor(a));
        }
        else if(dcmp(G-L)>=0&&dcmp(G-R)<=0)
        {
            printf("0 .. inf\n");
        }
        else if(dcmp(G-R)>0)
        {
            puts("unstable");
        }
    }
    else if(dcmp(O-L)>0&&dcmp(O-R)<0)
    {
        if(dcmp(G-L)<0)
        {
            double a=s*fabs(L-G)/fabs(L-O);
            printf("%d .. inf\n",(int)floor(a));
        }
        else if(dcmp(G-L)>=0&&dcmp(G-R)<=0)
        {
            printf("0 .. inf\n");
        }
        else if(dcmp(G-R)>0)
        {
            double a=s*fabs(R-G)/fabs(R-O);
            printf("%d .. inf\n",(int)floor(a));
        }
    }
    else
    {
        if(dcmp(G-L)<0)
        {
            double b=s*fabs(R-G)/fabs(R-O);
            double a=s*fabs(L-G)/fabs(L-O);
            printf("%d .. %d\n",(int)floor(a),(int)ceil(b));
        }
        else if(dcmp(G-L)>=0&&dcmp(G-R)<=0)
        {
            double a=0;
            double b=s*fabs(R-G)/fabs(R-O);
            //cerr<<"!!!!!!!!!!!!!!"<<a<<" "<<b<<endl;
            printf("%d .. %d\n",(int)floor(a),(int)ceil(b));
        }
        else if(dcmp(G-R)>0)
        {
            puts("unstable");
        }
    }
}