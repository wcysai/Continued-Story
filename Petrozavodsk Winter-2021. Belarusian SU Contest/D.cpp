#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
ll f[MAXN];
ll dp[MAXN];
int last[41];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&f[i]);
    ll maxi=0;
    for(int i=1;i<=n;i++)
    {
        dp[i]=maxi;
        for(int j=0;j<=40;j++) if(last[j]) dp[i]=max(dp[i],dp[last[j]]+(f[i]&f[last[j]]));
        for(int j=0;j<=40;j++)
            if(f[i]&(1LL<<j)) last[j]=i;
        maxi=max(maxi,dp[i]);
    }
    printf("%lld\n",maxi);
    return 0;
}