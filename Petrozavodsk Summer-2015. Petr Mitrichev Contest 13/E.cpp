#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;
int n,m;
double a[maxn],b[maxn];
double p[1005];
const int T=100;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%lf",&a[i]);
	for(int i=1;i<=m;++i)scanf("%lf",&b[i]);
	for(int i=1;i<=m;++i)
	{
		double t=1.0/(1.5+b[i]);
		for(int k=0;k<=T;++k)
		{
			p[k]+=t;
			t/=1.5+b[i];
		}
	}
	for(int k=0;k<=T;++k)if(k&1)p[k]=-p[k];
	for(int i=1;i<=n;++i)
	{
		double t=0,o=1;
		for(int k=0;k<=T;++k)
		{
			t+=p[k]*o;
			o*=a[i]-1.5;
		}
		printf("%.10f\n",t*a[i]);
	}
}
