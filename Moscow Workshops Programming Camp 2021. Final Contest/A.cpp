#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,m;
string s,t;
int dp[MAXN][MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    cin>>s; cin>>t;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            dp[i][j]=-INF;
    dp[0][0]=0;
    int ans=-INF;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
        {
            if(i>0&&j>0) dp[i][j]=max(dp[i][j],max(dp[i-1][j-1],0)-1);
            if(i>0&&j>0&&s[i-1]==t[j-1]) dp[i][j]=max(dp[i][j],max(dp[i-1][j-1],0)+1);
            if(i>0) dp[i][j]=max(dp[i][j],max(dp[i-1][j],0)-1);
            if(j>0) dp[i][j]=max(dp[i][j],max(dp[i][j-1],0)-1);
            if(i>0||j>0) ans=max(ans,dp[i][j]);
        }
    printf("%d\n",ans);
    return 0;
}
