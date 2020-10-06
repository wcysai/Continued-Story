#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,d[MAXN];
int calc(int mask)
{
    int cnt=0;
    for(int i=0;i<k-1;i++) if(((mask>>i)&1)!=((mask>>(i+1))&1)) cnt++;
    return cnt;
}
int dp[105][(1<<10)][31];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n-1;i++) scanf("%d",&d[i]);
    dp[0][0][0]=1;
    for(int i=0;i<n;i++)
    {
        for(int mask=0;mask<(1<<k);mask++)
        {
            int coef=calc(mask);
            for(int j=0;j<m;j++)
            {
                if(!dp[i][mask][j]) continue;
                int nxtj=(j+coef*d[i])%m;
                add(dp[i+1][mask][nxtj],dp[i][mask][j]);
                for(int l=0;l<k;l++)
                {
                    if(mask&(1<<l)) continue;
                    add(dp[i+1][mask|(1<<l)][nxtj],dp[i][mask][j]);
                }
            }
        }
    }
    printf("%d\n",dp[n][(1<<k)-1][0]);
}
