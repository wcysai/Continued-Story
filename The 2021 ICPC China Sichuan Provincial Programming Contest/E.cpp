#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,m,a[MAXN],h[MAXN],tmp[MAXN];
int s[MAXN],cnt[3][MAXN];
ll sum;
bool check(ll turns)
{
    ll rounds=turns/n,rem=turns%n;
    ll res=rounds*s[n]+s[rem];
    if(res<sum) return false;
    if(res>=sum+2*m) return true;
    ll cnt1,cnt2,cnt3;
    cnt1=rounds*cnt[0][n]+cnt[0][rem];
    cnt2=rounds*cnt[1][n]+cnt[1][rem];
    cnt3=rounds*cnt[2][n]+cnt[2][rem];
    for(int i=1;i<=m;i++) 
    {
        tmp[i]=h[i];
        if(tmp[i]>=3&&(tmp[i]&1)&&cnt3) {tmp[i]-=3; cnt3--;}
    }
    for(int i=1;i<=m;i++)
    {
        if(!cnt3) break;
        ll mini=min(cnt3/2,1LL*tmp[i]/6);
        cnt3-=2*mini; tmp[i]-=6*mini;
    }
    for(int i=1;i<=m;i++)
        if(tmp[i]>=3&&cnt3) {tmp[i]-=3; cnt3--;}
    cnt2+=cnt3;
    for(int i=1;i<=m;i++)
    {
        if(!cnt2) break;
        ll mini=min(cnt2,1LL*tmp[i]/2);
        cnt2-=mini; tmp[i]-=2*mini;
    }
    for(int i=1;i<=m;i++)
        if(tmp[i]==1&&cnt2) {tmp[i]-=2; cnt2--;}
    ll need=0;
    for(int i=1;i<=m;i++)
        if(tmp[i]>=1) need+=tmp[i];
    return cnt1>=need;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        scanf("%d",&m);
        sum=0;
        for(int i=1;i<=m;i++) 
        {
            scanf("%d",&h[i]);
            sum+=h[i];
        }
        for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<3;j++) cnt[j][i]=cnt[j][i-1];
            cnt[a[i]-1][i]++;
        }
        ll l=0,r=INF;
        while(r-l>1)
        {
            ll mid=(l+r)/2;
            if(check(mid)) r=mid; else l=mid;
        }
        printf("%lld\n",r);
    }
}