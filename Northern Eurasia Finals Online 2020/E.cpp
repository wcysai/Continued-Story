#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll b,d;
ll gcd(ll a,ll b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&b,&d);
        ll ans=0;
        ll t=d/gcd(b,d);
        if(b%t==0)ans=b/t-1;
        else ans=b/t;
        printf("%lld\n",ans);
    }
}
