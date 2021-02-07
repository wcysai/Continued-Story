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
int dp[(1<<20)];
int sum[(1<<20)];
int p2[MAXN];
int ans;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
/*dp[i][j][0/1]:
current length is i
the ith position has highest bit on j
is there any position banned for position i+1
*/
int main()
{
    p2[0]=1;
    for(int i=1;i<=1000000;i++) p2[i]=2LL*p2[i-1]%MOD;
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    dp[1]=1;
    sum[0]+=1;
    int s=1;
    for(int i=2;i<=n;i++)
    {
        dp[i]=s; add(dp[i],1);
        int maxi=0;
        for(int j=0;(1<<j)<=i;j++)
        {
            if(((1<<(j+1))<=i)&&(i&(1<<j))) dec(dp[i],sum[j]);
            maxi=max(maxi,j);
        }
        add(s,dp[i]);
        add(sum[maxi],dp[i]);
    }
    printf("%d\n",s);
}