#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int t,n,k;
int dp[MAXN][MAXN][2];
/*
dp[n][k][0/1]:
first n elements/k adjacent pairs/is n and n-1 adjacent
*/

int main()
{
    dp[2][1][1]=2;
    for(int i=2;i<=999;i++)
    {
        for(int j=0;j<=i-1;j++)
        {
            add(dp[i+1][j+1][1],2LL*dp[i][j][0]%MOD);
            if(j) add(dp[i+1][j-1][0],1LL*j*dp[i][j][0]%MOD);
            add(dp[i+1][j][0],1LL*(i-1-j)*dp[i][j][0]%MOD);
            add(dp[i+1][j][1],dp[i][j][1]);
            add(dp[i+1][j+1][1],dp[i][j][1]);
            if(j) add(dp[i+1][j-1][0],1LL*(j-1)*dp[i][j][1]%MOD);
            add(dp[i+1][j][0],1LL*(i-j)*dp[i][j][1]%MOD);
        }
    }

    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        if(n==1) {puts("1"); continue;}
        int ans=dp[n][k][0];
        add(ans,dp[n][k][1]);
        printf("%d\n",ans);
    }
    return 0;
}