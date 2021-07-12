#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
double px,py,qx,qy,ux,uy,u,v,r;
double sqr(double x){return x*x;}
int n;
double f(double x)
{
    return r/(sqrt(v*v-u*u*cos(x)*cos(x))+u*sin(x));
}
double romberg(double a,double b,double eps=1e-6)
{
    vector<double> t;
    double h=b-a,last,curr;
    int k=1,i=1;
    t.push_back(h*(f(a)+f(b))/2);
    do
    {
        last=t.back();
        curr=0;
        double x=a+h/2;
        for(int j=0;j<k;++j)
        {
            curr+=f(x);
            x+=h;
        }
        curr=(t[0]+h*curr)/2;
        double k1=4.0/3.0,k2=1.0/3.0;
        for(int j=0;j<i;++j)
        {
            double temp=k1*curr-k2*t[j];
            t[j]=curr;
            curr=temp;
            k2/=4*k1-k2;
            k1=k2+1;
        }
        t.push_back(curr);
        k*=2;
        h/=2;
        i++;
    } while (fabs(last-curr)>eps);
    return t.back();
}
int main()
{
    scanf("%lf%lf%lf%lf%lf%lf%lf",&px,&py,&qx,&qy,&ux,&uy,&v);
    r=sqrt(sqr(px-qx)+sqr(py-qy));
    u=sqrt(sqr(ux)+sqr(uy));
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        double t;
        scanf("%lf",&t);
        double l=0,r=1e6;
        for(int cas=1;cas<=80;++cas)
        {
            double mid=(l+r)/2;
            if(romberg(0,mid)<t)l=mid;
            else r=mid;
        }
        double si=l;
        double x=qx-px,y=qy-py;
        double nx=x*cos(si)-y*sin(si),ny=x*sin(si)+y*cos(si);
        nx+=ux*t+px,ny+=uy*t+py;
        printf("%.6f %.6f\n",nx,ny);
    }
}