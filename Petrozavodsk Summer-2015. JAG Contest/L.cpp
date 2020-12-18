#include<bits/stdc++.h>
#define MAXN 25
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,dp[MAXN][MAXN][MAXN][MAXN];
char str[MAXN][MAXN];
int solve(int l,int r,int x,int y)
{
    if(l>r||x>y) return 0;
    if(dp[l][r][x][y]!=-1) return dp[l][r][x][y];
    vector<int> v; v.clear();
    for(int i=l;i<=r;i++)
    {
        for(int j=x;j<=y;j++)
        {
            if(str[i][j]=='X') continue;
            int sg=solve(l,i-1,x,j-1)^solve(l,i-1,j+1,y)^solve(i+1,r,x,j-1)^solve(i+1,r,j+1,y);
            v.push_back(sg);
        }
    }
    if(!v.size()) return dp[l][r][x][y]=0;  
    sort(v.begin(),v.end());
    if(v[0]!=0) return dp[l][r][x][y]=0;
    for(int i=1;i<(int)v.size();i++) if(v[i-1]+1<v[i]) return dp[l][r][x][y]=v[i-1]+1;
    return dp[l][r][x][y]=v.back()+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",str[i]);
    memset(dp,-1,sizeof(dp));
    if(solve(0,n-1,0,m-1)) puts("First"); else puts("Second");
    return 0;
}