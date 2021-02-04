#include<bits/stdc++.h>
#define maxn 9000005
using namespace std;
int n,m,P;
int fac[maxn];
int fastpow(int a,int p)
{
	int ans=1;
	while(p)
	{
		if(p&1)ans=1ll*ans*a%P;
		a=1ll*a*a%P;
		p>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&m,&P);
	fac[0]=1;
	for(int i=1;i<=9000000;++i)fac[i]=1ll*fac[i-1]*i%P;
	int ans=1ll*n%P*m%P*fac[n-1]%P*fac[m-1]%P*fac[n*m]%P*fastpow(fac[n+m-1],P-2)%P;
	printf("%d\n",ans);
}