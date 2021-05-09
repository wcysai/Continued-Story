//team continued story
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
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
int t;
ll z;
vector<int> v;
int ways[20];
ll p10[20];
int get_ways(int sum,bool lead)
{
    if(sum>18) return 0;
    if(lead) return ways[sum]-(sum<=9?1:0);
    return ways[sum];
}
ll dfs(int x,int y,ll rem)
{
    ll mod=p10[x]+p10[y];
    if(x>y) return (rem==0?1:0);
    if(x==y)
    {
        if(rem%mod==0&&rem/mod>=0&&rem/mod<=9) return 1;
        else return 0;
    }
    ll m=(rem/mod);
    ll ans=0;
    if(get_ways(m,(x==0))) ans+=get_ways(m,(x==0))*dfs(x+1,y-1,rem-m*mod);
    if(m>0&&get_ways(m-1,(x==0))) ans+=get_ways(m-1,(x==0))*dfs(x+1,y-1,rem-(m-1)*mod);
    return ans;
}
ll solve(int len)
{
    return dfs(0,len-1,z);
}
int main()
{
    p10[0]=1;
    for(int i=1;i<=18;i++) p10[i]=10LL*p10[i-1];
    for(int i=0;i<=9;i++)
        for(int j=0;j<=9;j++)
            ways[i+j]++;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld",&z);
        ll tmp=z;
        v.clear();
        while(tmp)
        {
            v.push_back(tmp%10);
            tmp/=10;
        }
        int len=(int)v.size();
        ll ans=solve(len); ans+=solve(len-1);
        printf("%lld\n",ans);
    }
    return 0;
}
