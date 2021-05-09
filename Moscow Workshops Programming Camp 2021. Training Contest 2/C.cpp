#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 2005
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
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=(n-1)/2;i++)
    {
        printf("%d",n);
        int l=i-1,r=i;
        if(l<=0) l+=(n-1);
        for(int j=0;j<(n-1)/2;j++)
        {
            printf(" %d %d",l,r);
            l--; r++;
            if(l<=0) l+=(n-1); 
            if(r>(n-1)) r-=(n-1);
        }
        puts("");
    }
    return 0;
}
