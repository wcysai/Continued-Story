#include<bits/stdc++.h>
using namespace std;
int n;
double ans;
int main()
{
	scanf("%d",&n);
	ans=0;
	for(int i=1;i<=n;++i)
	{
		double x;
		scanf("%lf",&x);
		ans+=x*x;
	}
	ans/=2;
	printf("%.10f\n",ans);
}