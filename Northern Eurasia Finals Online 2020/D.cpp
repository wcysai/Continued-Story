#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,sg[MAXN];
string str[MAXN];
vector<int> pre[MAXN];
int cnt[MAXN][9];
bool save[10];
int ans[MAXN];
int mask[MAXN];
int dp[MAXN][(1<<8)];
int common_piece(int x,int y)
{
    int cnt=0;
    for(int i=0;i<8;i++) if(str[x][i]==str[y][i]) cnt++;
    return cnt;
}
int solve(int cur,int m)
{
    if(cur==1) return (m&1?1:2);
    if(dp[cur][m]!=-1) return dp[cur][m];
    int state=((~m)&mask[cur-1])?1:0;
    return dp[cur][m]=solve(cur-1,((m<<1)+state)&255);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) cin>>str[i];
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=min(i+8,n);j++)
            if(j-i<=common_piece(i,j)) mask[i]|=(1<<(j-i-1));
    }
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=n;i++) printf("%d",solve(i,254));
    return 0;
}