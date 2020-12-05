#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int t,n,d;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&d);
        ll ans=(d<=1?4:8);
        for(int i=1;i<=n-1;i++) ans=ans*(2*d+1);
        printf("%lld\n",ans);
    }
    return 0;
}