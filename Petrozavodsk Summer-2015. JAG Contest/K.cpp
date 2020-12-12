#include<bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
double x,y,phi,omg;
bool check(double r)
{
	double v=omg*r;
	double si=atan2(y,x);
	double ang=acos(r/sqrt(x*x+y*y));
	double l1=si-ang,r1=si+ang;
	double d=sqrt(x*x+y*y-r*r);
	double t=d/v;
	double l2=phi-omg*t,r2=phi+omg*t;
	while(l1<l2)l1+=2*PI,r1+=2*PI;
	if(l2<=l1&&r1<=r2)return 0;
	else return 1;
}
int main()
{
	scanf("%lf%lf%lf%lf",&x,&y,&phi,&omg);
	phi=phi*2*PI/360;
	omg=omg*2*PI/360;
	double L=0,R=sqrt(x*x+y*y);
	for(int c=1;c<=300;++c)
	{
		double M=(L+R)/2;
		if(check(M))R=M;
		else L=M;
	}
	printf("%.10f\n",omg*R);
}