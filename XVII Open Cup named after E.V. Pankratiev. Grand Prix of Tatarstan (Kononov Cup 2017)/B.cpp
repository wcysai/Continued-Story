#include<bits/stdc++.h>
const double eps = 1e-2;
const double PI = acos(-1.0);
using namespace std;
int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
double sqr(double x){return x*x;}
struct Point
{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    void read()
    {
        scanf("%lf%lf",&x,&y);
    }
    void print()
    {
        printf("%.10f %.10f\n",x,y);
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
Vector Normal(Vector x)
{
    return Vector(-x.y,x.x)/Length(x);
}
double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
Point GetLineIntersection(Point p,Vector v,Point q,Vector w)
{
    Vector u=p-q;
    double t=Cross(w,p-q)/Cross(v,w);
    return p+v*t;
}
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
int getTangents(Circle A,Circle B,Point *a,Point *b)
{
    int cnt=0;
    if(dcmp(A.r-B.r)<0)swap(A,B),swap(a,b);
    double d2=sqr(A.c.x-B.c.x)+sqr(A.c.y-B.c.y);
    double rdiff=A.r-B.r,rsum=A.r+B.r;
    if(dcmp(d2-rdiff*rdiff)<0)return 0;
    double base=atan2(B.c.y-A.c.y,B.c.x-A.c.x);
    if(dcmp(d2)==0&&dcmp(A.r-B.r)==0)return -1;
    if(dcmp(d2-rdiff*rdiff)==0)
    {
        a[cnt]=A.point(base);
        b[cnt]=a[cnt]+Normal(B.c-A.c);
        cnt++;
        return 1;
    }
    double ang=acos((A.r-B.r)/sqrt(d2*1.0));
    a[cnt]=A.point(base+ang);b[cnt]=B.point(base+ang);cnt++;
    a[cnt]=A.point(base-ang);b[cnt]=B.point(base-ang);cnt++;
    if(dcmp(d2-rsum*rsum)==0)
    {
        a[cnt]=A.point(base);b[cnt]=a[cnt]+Normal(B.c-A.c);cnt++;
    }
    else if(dcmp(d2-rsum*rsum)>0)
    {
        double ang=acos((A.r+B.r)/sqrt(d2*1.0));
        a[cnt]=A.point(base+ang);b[cnt]=B.point(PI+base+ang);cnt++;
        a[cnt]=A.point(base-ang);b[cnt]=B.point(PI+base-ang);cnt++;
    }
    return cnt;
}
Point A,B;
double a1,a2,a3,b1,b2,b3;
Point U1[10],V1[10],U2[10],V2[10],U3[10],V3[10];
int N1,N2,N3;
int main()
{
    A.read();
    scanf("%lf%lf%lf",&a1,&a2,&a3);
    B.read();
    scanf("%lf%lf%lf",&b1,&b2,&b3);
    N1=getTangents(Circle(A,abs(a1)),Circle(B,abs(b1)),U1,V1);
    N2=getTangents(Circle(A,abs(a2)),Circle(B,abs(b2)),U2,V2);
    N3=getTangents(Circle(A,abs(a3)),Circle(B,abs(b3)),U3,V3);
    //cerr<<N1<<" "<<N2<<" "<<N3<<endl;
    /*for(int i=0;i<N1;++i)
    {
        U1[i].print();V1[i].print();
        puts("!!!!!!!!!!!!!!!!");
    }*/
    //if(dcmp(A.x-B.x)==0&&dcmp(A.y-B.y)==0)assert(0);
    for(int i=0;i<N1;++i)
        for(int j=0;j<N2;++j)
            for(int k=0;k<N3;++k)
            {
                /*U1[i].print();V1[i].print();
                U2[i].print();V2[i].print();
                U3[i].print();V3[i].print();
                puts("!!!!!!!!!!!!!!!!!!!!!");*/
                if(dcmp(Cross(U1[i]-V1[i],U2[j]-V2[j]))==0)continue;
                if(dcmp(Cross(U2[j]-V2[j],U3[k]-V3[k]))==0)continue;
                if(dcmp(Cross(U3[k]-V3[k],U1[i]-V1[i]))==0)continue;
                Point X=GetLineIntersection(U1[i],V1[i]-U1[i],U2[j],V2[j]-U2[j]);
                Point Y=GetLineIntersection(U2[j],V2[j]-U2[j],U3[k],V3[k]-U3[k]);
                Point Z=GetLineIntersection(U3[k],V3[k]-U3[k],U1[i],V1[i]-U1[i]);
                //cerr<<X.x<<" "<<X.y<<" "<<Y.x<<" "<<Y.y<<" "<<Z.x<<" "<<Z.y<<endl;
                int t1=0,t2=0;
                if(dcmp(Cross(A-X,Y-X))<0)t1--;else t1++;
                if(dcmp(Cross(A-Y,Z-Y))<0)t1--;else t1++;
                if(dcmp(Cross(A-Z,X-Z))<0)t1--;else t1++;
                if(dcmp(Cross(B-X,Y-X))<0)t2--;else t2++;
                if(dcmp(Cross(B-Y,Z-Y))<0)t2--;else t2++;
                if(dcmp(Cross(B-Z,X-Z))<0)t2--;else t2++;
                if(abs(t1)==3&&a1<0)continue;
                if(abs(t1)!=3&&a1>0)continue;
                if(abs(t2)==3&&b1<0)continue;
                if(abs(t2)!=3&&b1>0)continue;
                Z.print();
				X.print();
				Y.print();;
                return 0;
            }
}