#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int c[12][12];
int n,a[MAXN],p10[MAXN];
P p[MAXN];
int main()
{
    p10[0]=1;
    for(int i=1;i<=10;i++) p10[i]=10LL*p10[i-1]%7;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        int mod=a[i]%7;
        int cnt=0,tmp=a[i];
        while(tmp)
        {
            tmp/=10;
            cnt++;
        }
        p[i]=P(mod,cnt);
        c[mod][cnt]++;
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
    {   
        for(int mod=0;mod<7;mod++)
        {
            for(int cnt=0;cnt<=10;cnt++)
            {
                if((1LL*a[i]*p10[cnt]+mod)%7==0)
                {
                    ans+=c[mod][cnt];
                    if(p[i]==P(mod,cnt)) ans--;
                }
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}