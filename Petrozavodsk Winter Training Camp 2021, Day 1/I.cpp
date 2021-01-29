#include<bits/stdc++.h>
#define MAXN 2000005
#define MAXM 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a[MAXN];
int cnt[MAXM];
vector<int> p[MAXM];
int main()
{
    scanf("%d",&t);
    for(int g=1;g<=1000000;g++)
    {
        for(int i=2*g;i<=1000000;i+=g)
        {
            if((i^(i-g))==g)
            {
                p[i].push_back(i-g);
            }
        }
    }
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        memset(cnt,0,sizeof(cnt));
        sort(a+1,a+n+1);
        ll ans=0;
        for(int i=1;i<=n;i++)
        {
            for(auto x:p[a[i]]) ans+=cnt[x];
            cnt[a[i]]++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}