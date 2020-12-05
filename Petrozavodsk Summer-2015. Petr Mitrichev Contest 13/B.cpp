#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],k;
ll sum[MAXN],val[2*MAXN];
ll b[2*MAXN];
ll deq[2*MAXN];
void solve()
{
	int s=0,t=0;
	for(int i=1;i<=2*n;i++)
	{
		while(s<t&&val[deq[t-1]]<=val[i]) t--;
		deq[t++]=i;
		if(i>=k)
		{
			b[i-k+1]=val[deq[s]];
			if(deq[s]==i-k+1)
			{
				s++;
			}
		}
	}
}
int main()
{
    scanf("%d",&n);
    int x=(n+1)/2,y=n/2;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    for(int i=y;i<=n;i++) val[i]=sum[i]-sum[i-y];
    for(int i=1;i<=y-1;i++) val[i]=sum[i]+sum[n]-sum[n-y+i];
    for(int i=1;i<=n;i++) val[n+i]=val[i];
    k=x;
    solve();
    ll res=INF;
    for(int i=1;i<=n;i++) res=min(res,b[i]);
    printf("%lld %lld\n",sum[n]-res,res);
    return 0;
}