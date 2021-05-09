#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN],c[MAXN];
int pref[MAXN],suf[MAXN];
int dp[2][MAXN][MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int fact[MAXN],invf[MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int solve(int x,int y)//first k have a[i]+c[i]>=x, the rest have a[i]+c[i]<=y(x>=y)
{
    memset(pref,0,sizeof(pref));
    memset(suf,0,sizeof(suf));
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++)
            if(a[i]+c[j]>=x) pref[i]++;
    for(int i=k+1;i<=n;i++)
        for(int j=n;j>=1;j--)
            if(a[i]+c[j]<=y) suf[i]++;
    int pos=pref[k];
    //dp[0/1][i][j]: right upper/left lower, number of choosing j elements from first i rows
    memset(dp,0,sizeof(dp));
    dp[0][0][0]=dp[1][0][0]=1;
    for(int i=0;i<k;i++)
        for(int j=0;j<=i;j++)
        {
            if(!dp[0][i][j]) continue;
            int x=max(0,pref[k-i]-pos-j);
            add(dp[0][i+1][j],dp[0][i][j]);
            add(dp[0][i+1][j+1],1LL*dp[0][i][j]*x%MOD);
        }
    for(int i=0;i<n-k;i++)
        for(int j=0;j<=i;j++)
        {
            if(!dp[1][i][j]) continue;
            int x=max(0,suf[k+1+i]-(n-pos)-j);
            add(dp[1][i+1][j],dp[1][i][j]);
            add(dp[1][i+1][j+1],1LL*dp[1][i][j]*x%MOD);
        }
    int ans=0;
    for(int x=0;x<=k;x++)
        for(int y=0;y<=n-k;y++)
        {
            if(k-x!=pos-y) continue;
            add(ans,1LL*dp[0][k][x]*dp[1][n-k][y]%MOD*fact[k-x]%MOD*fact[n-k-y]%MOD);
        }
    return ans;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=100;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100]=pow_mod(fact[100],MOD-2);
    for(int i=99;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    sort(a+1,a+n+1,greater<int>());
    sort(c+1,c+n+1,greater<int>());
    int ans=0;
    for(int i=2;i<=2000;i++) 
    {
        add(ans,solve(i,i));
        dec(ans,solve(i+1,i));
    }
    printf("%d\n",ans);
    return 0;
}