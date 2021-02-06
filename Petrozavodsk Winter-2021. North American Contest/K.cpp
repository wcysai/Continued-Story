#include<bits/stdc++.h>
#define MAXN 305
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
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
int n,k;
int fact[MAXN],invf[MAXN];
int cnt[MAXN];
int pw[MAXN][MAXN];
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
/*number of spanning trees of order n with k partite graphs n1+n2+...nk=n
  is T(n,k)=n^(k-2)\prod (n-ni)^(ni-1)
  number of filling with a full spanning tree n vertices, given a spanning tree of k vertices
  is k*n^(n-1-k)
*/
int dp[MAXN][MAXN];
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=300;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[300]=pow_mod(fact[300],MOD-2);
    for(int i=299;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=0;i<=300;i++)
    {
        pw[i][0]=1;
        for(int j=1;j<=300;j++) pw[i][j]=1LL*pw[i][j-1]*i%MOD;
    }
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        int c;
        scanf("%d",&c);
        cnt[c]++;
    }
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++)
    {
        dp[i][1]=(i>k?0:(i==1?1:1LL*pw[i][i-2]*i%MOD));
        for(int j=2;j<=i;j++)
        {
            for(int sz=1;sz<min(k+1,i);sz++)
            {
                int num=(sz==1?1:pw[sz][sz-2]);
                add(dp[i][j],1LL*sz*dp[i-sz][j-1]%MOD*num%MOD*comb(i-1,sz-1)%MOD);
            }
        }
    }
    int ans=1;
    for(int i=1;i<=n;i++)
    {
        if(!cnt[i]) continue;
        int res=0;
        for(int j=1;j<=cnt[i];j++) add(res,1LL*dp[cnt[i]][j]*pw[n-cnt[i]][j-1]%MOD);
        ans=1LL*ans*n%MOD*res%MOD;
    }
    int invn=pow_mod(n,MOD-2);
    ans=1LL*ans*invn%MOD*invn%MOD;
    printf("%d\n",ans);
    return 0;
}