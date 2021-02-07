#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[10];
bool isprime(ll x)
{
	for(ll i=2;i*i<=x;++i)if(x%i==0)return 0;
	return 1;
}
int main()
{
	scanf("%d",&n);
	if(n>5)
	{
		puts("Yes");
	}
	else
	{
		for(int i=0;i<n;++i)scanf("%lld",&a[i]);
		bool yes=0;
		for(int S=0;S<(1<<n);++S)
		{
			ll sum=0;
			for(int i=0;i<n;++i)if(S&(1<<i))sum+=a[i];
			if(!isprime(sum))yes=1;
		}
		if(yes)puts("Yes");
		else puts("No");
	}
}