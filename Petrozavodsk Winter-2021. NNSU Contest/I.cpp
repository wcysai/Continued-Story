#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,s;
P p[MAXN];
int dp[2005],ndp[2005];
int main()
{
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;i++) scanf("%d",&p[i].S);
    for(int i=1;i<=n;i++) scanf("%d",&p[i].F);
    sort(p+1,p+n+1,greater<P>());
    memset(dp,-1,sizeof(dp));
    dp[0]=s;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        memset(ndp,-1,sizeof(ndp));
        for(int j=0;j<2000;j++)
        {
            if(dp[j]==-1) continue;
            ans=max(ans,j);
            ndp[j]=max(ndp[j],dp[j]);
            if(dp[j]>=p[i].S+1LL*p[i].F*j) ndp[j+1]=max(ndp[j+1],dp[j]-p[i].S-p[i].F*j);
        }
        swap(dp,ndp);
    }
    for(int j=0;j<2000;j++) if(dp[j]!=-1) ans=max(ans,j);
    printf("%d\n",ans);
    return 0;
}