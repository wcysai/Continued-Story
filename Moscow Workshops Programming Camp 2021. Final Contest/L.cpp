#include<bits/stdc++.h>
#define MAXN 125
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
ll x[MAXN];
ll dp[MAXN][MAXN][MAXN][4][2];
ll getval(int x)
{
    int y=(int)sqrt(x);
    return 1LL*x*y;
}
ll solve(int l,int r,int hop,int type,int isf)//type=0: no connect, 1: connect to the left, 2: connect to the right, 3: can do both
{
    if(l>r) return 0;
    if(hop<0) return INF;
    if(dp[l][r][hop][type][isf]!=-1) return dp[l][r][hop][type][isf];
    dp[l][r][hop][type][isf]=INF;
    if(type==0)
    {
        for(int i=l;i<=r;i++)
            dp[l][r][hop][type][isf]=min(dp[l][r][hop][type][isf],solve(l,i-1,hop-1,2,1)+solve(i+1,r,hop-1,1,1));
    }
    else if(type==1)
    {
        for(int i=r;i>=l;i--)
            dp[l][r][hop][type][isf]=min(dp[l][r][hop][type][isf],(isf?solve(i+1,r,hop-1,1,1):solve(i+1,r,hop-1,3,1))+min(solve(l,i-1,hop,1,0),solve(l,i-1,hop-1,2,1))+getval(x[i]-x[l-1]));
    }
    else if(type==2)
    {
        for(int i=l;i<=r;i++)
            dp[l][r][hop][type][isf]=min(dp[l][r][hop][type][isf],(isf?solve(l,i-1,hop-1,2,1):solve(l,i-1,hop-1,3,1))+min(solve(i+1,r,hop,2,0),solve(i+1,r,hop-1,1,1))+getval(x[r+1]-x[i]));
    }
    else
    {
        for(int i=l-1;i<=r;i++)
            dp[l][r][hop][type][isf]=min(dp[l][r][hop][type][isf],solve(l,i,hop,1,1)+solve(i+1,r,hop,2,1));
    }
    return dp[l][r][hop][type][isf];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&x[i]);
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=n-1;i++) printf("%lld\n",solve(1,n,i,0,0));
    return 0;
}