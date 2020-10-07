#include<bits/stdc++.h>
#define ll long long
#define maxn 1000005
using namespace std;
int T;
int n;
ll a[maxn];
ll b[maxn],c[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%lld",&a[i]),a[i]+=a[i-1];
        ll ans=-(ll)1e18,min1=0,min2=(ll)1e18;
        for(int i=1;i<=n;++i)
        {
            if(i&1)min1=min(min1,a[i-1]);
            else min2=min(min2,a[i-1]);
            if(i&1)ans=max(ans,a[i]-min1);
            else ans=max(ans,a[i]-min2);
        }
        printf("%lld\n",ans);
    }
}
