#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
vector<int> save[MAXN];
vector<int> pre[MAXN];
int dp[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&k);
        for(int j=1;j<=k;j++) 
        {
            int x;
            scanf("%d",&x);
            save[x].push_back(i);
        }
    }
    for(int i=0;i<=100000;i++) 
        for(int j=1;j<(int)save[i].size();j++) 
            pre[save[i][j]].push_back(save[i][j-1]);
    int ans=0;
    for(int i=0;i<=100000;i++)
    {
        dp[i]=1;
        for(auto x:pre[i]) dp[i]=max(dp[i],dp[x]+1);
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}