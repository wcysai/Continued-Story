#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
const double g = 10;
int T;
double v0;
int n;
double x[maxn],y[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf",&v0);
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%lf%lf",&x[i],&y[i]);
		double ans=1e18;
		for(int i=1;i<=n;++i)
		{
			double A=-g/(2*v0*v0)*x[i]*x[i];
			double B=x[i];
			double C=A-y[i];
			double D=B*B-4*A*C;
			double t=max((-B-sqrt(D))/(2*A),(-B+sqrt(D))/(2*A));
			ans=min(ans,t);
		}
		printf("%.3f\n",ans);
	}
}