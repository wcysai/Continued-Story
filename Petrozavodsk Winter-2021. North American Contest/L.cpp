#include<bits/stdc++.h>
using namespace std;
const double g = 9.81;
double m,b1,b2,t1,hf;
double C1,C2;
double X1(double t)
{
	return m*m*g/(b1*b1)*exp(-b1*t/m)+m*g*t/b1-m*m*g/(b1*b1);
}
double V1(double t)
{
	return -m/b1*g*exp(-b1*t/m)+m/b1*g;
}
double A1(double t)
{
	return g*exp(-b1/m*t);
}
double X2(double t)
{
	return C1+C2*exp(-b2*(t-t1)/m)+m*g/b2*(t-t1)+X1(t1);
}
double V2(double t)
{
	return -b2/m*C2*exp(-b2*(t-t1)/m)+m*g/b2;
}
double A2(double t)
{
	return b2*b2/(m*m)*C2*exp(-b2*(t-t1)/m);
}
int main()
{
	scanf("%lf%lf%lf%lf%lf",&m,&b1,&b2,&t1,&hf);
	C2=(m*g/b2-V1(t1))*m/b2;
	C1=-C2;
	int q;
	scanf("%d",&q);
	while(q--)
	{
		double t;
		scanf("%lf",&t);
		if(t<=t1)printf("%.10f\n",X1(t));
		else printf("%.10f\n",X2(t));
	}
	double l=0,r=1e18;
	for(int i=1;i<=300;++i)
	{
		double mid=(l+r)/2;
		if(X2(mid)<=hf)l=mid;
		else r=mid;
	}
	printf("%.10f\n",l);
}