#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 16
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
int n,k,a[MAXN];
string str[MAXN];
int dp[(1<<16)],lson[(1<<16)],rson[(1<<16)],opt[(1<<16)];
void solve(int mask)
{
    if(__builtin_popcount(mask)==0) return;
    if(__builtin_popcount(mask)==1)
    {
        for(int i=0;i<n;i++) if(mask&(1<<i)) {printf("= %d\n",i); return;}
        assert(0);
    }
    printf("> %d\n",opt[mask]);
    solve(lson[mask]); solve(rson[mask]);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) cin>>str[i];
    int sz=(int)str[0].size();
    for(int i=0;i<(1<<n);i++)
    {
        if(__builtin_popcount(i)<=1)
        {
            dp[i]=0;
            opt[i]=0;
        }
        else
        {
            dp[i]=INF;
            for(int j=0;j<sz;j++)
            {
                int mask0=0,mask1=0;
                for(int k=0;k<n;k++)
                {
                    if(!(i&(1<<k))) continue;
                    if(str[k][j]=='0') mask0|=(1<<k); else mask1|=(1<<k);
                }
                if(max(dp[mask0],dp[mask1])+1<dp[i])
                {
                    dp[i]=max(dp[mask0],dp[mask1])+1;
                    opt[i]=j; lson[i]=mask0; rson[i]=mask1;
                }
            }
        }
    }
    solve((1<<n)-1);
    return 0;
}
