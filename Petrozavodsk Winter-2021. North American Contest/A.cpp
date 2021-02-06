#include<bits/stdc++.h>
using namespace std;
int n;
double p,c;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%lf%lf",&p,&c);
		c/=100;
		printf("%.10f\n",p/(c+1));
	}
}