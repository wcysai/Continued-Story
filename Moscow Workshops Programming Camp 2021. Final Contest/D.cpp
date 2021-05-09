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
int n,k,a[MAXN];
int run(int k)
{
    printf("run %d\n",k);
    fflush(stdout);
    int x;
    scanf("%d",&x);
    return x;
}
void answer(int k)
{
    printf("ensure %d\n",k);
    fflush(stdout);
    exit(0);
}
ll cur;
int main()
{
    int l=1,r=INF;
    cur=0;
    while(r>l)
    {
        ll mid=(l+r)/2;//check if <=mid or >mid by asking multiples of mid;
        ll need=mid-(cur%mid);
        ll x=run(need);
        cur+=need;
        ll lap=cur/mid;
        if(x>=lap) r=mid; else l=mid+1;
    }
    answer(l);
    return 0;
}
