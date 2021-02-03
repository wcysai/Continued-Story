#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000000000000031LL
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll ans[MAXN];
ll mul_mod(ll a,ll b)
{
    if(a>b) swap(a,b);
    ll s=0;
    while(a)
    {
        if(a&1) s=(s+b)%MOD;
        b=(b+b)%MOD;
        a>>=1;
    }
    return s;
}
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=mul_mod(s,a);
        a=mul_mod(a,a);
        i>>=1;
    }
    return s;
}
int main()
{
    ans[1000000]=300;
    for(int i=999999;i>=0;i--) ans[i]=pow_mod(42LL,ans[i+1]);
    int n;
    scanf("%d",&n);
    printf("%lld\n",ans[n]);
    return 0;
}