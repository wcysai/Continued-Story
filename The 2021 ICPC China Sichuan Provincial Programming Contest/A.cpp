#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,x,p0;
int s[MAXN],t[MAXN],p[MAXN];
bool check(int speed)
{
    int dist=x;
    bool state=(1LL*p0*speed>=dist?1:0);
    if(state) dist-=1LL*speed*t[1];
    if(dist<=0) return true;
    for(int i=1;i<=k;i++)
    {
        bool state=(1LL*(p[i]-t[i])*speed>=dist?1:0);
        if(state) dist-=1LL*speed*((i==k?p[k]:t[i+1])-t[i]);
        if(dist<=0) return true;
    }
    return false;
}
int main()
{
    scanf("%d%d%d%d",&n,&k,&x,&p0);
    for(int i=1;i<=n;i++) scanf("%d",&s[i]);
    for(int i=1;i<=k;i++) scanf("%d",&t[i]);
    for(int i=1;i<=k;i++) scanf("%d",&p[i]);
    sort(s+1,s+n+1,greater<int>());
    int l=0,r=n+1;
    assert(check(s[2]));
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(check(s[mid])) l=mid; else r=mid;
    }
    printf("%d\n",l);
    return 0;
}