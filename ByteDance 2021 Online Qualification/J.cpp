#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN];
//ans is min(asum,s+bsum/2)
int dp[MAXN][MAXM],ndp[MAXN][MAXM];
//dp[i][j][k]: maximum bsum if choose j from first i with asum equal to k
int main()
{
    scanf("%d",&n);
    double ss=0.0;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d",&a[i],&b[i]);
        ss+=b[i];
    }
    ss/=2.0;
    int s=0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=10000;j++) 
            dp[i][j]=-INF;
    dp[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        s+=a[i];
        for(int j=0;j<=n;j++)
            for(int k=0;k<=10000;k++) 
                ndp[j][k]=-INF;
        for(int j=0;j<=i;j++)
        {
            for(int k=0;k<=s;k++)
            {
                ndp[j][k]=dp[j][k];
                if(k>=a[i]&&j>0) ndp[j][k]=max(ndp[j][k],dp[j-1][k-a[i]]+b[i]);
            }
        }
        swap(dp,ndp);
    }
    for(int i=1;i<=n;i++)
    {
        double ans=0.0;
        for(int j=0;j<=s;j++)
        {
            ans=max(ans,min((double)j,ss+(double)dp[i][j]/2.0));
        }
        printf("%.10f ",ans);
    }
    return 0;
}