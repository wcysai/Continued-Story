#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,a[MAXN],d[MAXN];
struct segtree
{
    ll mini[4*MAXN];
    void pushup(int k)
    {
        mini[k]=min(mini[k*2],mini[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            mini[k]=d[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    int query(int k,int l,int r,int pos,int val)
    {
        if(mini[k]>=val||l-1>pos) return -1;
        if(l==r) return l;
        int mid=(l+r)/2;
        int rans=query(k*2+1,mid+1,r,pos,val);
        if(rans!=-1) return rans; else return query(k*2,l,mid,pos,val);
    }
}seg;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(int i=2;i<=n;i++) d[i]=a[i]-a[i-1];
    seg.build(1,2,n);
    a[n+1]=INF;
    ll ans=-1;
    for(int i=5;i<=n-2;i++)//enumerating a[3]
    {
        ll sum=a[i-1]+a[i-2]+a[i-3]+a[i-4];
        if(sum<a[i]+a[i+1]) continue;
        ll res=sum-a[i];
        int pos=upper_bound(a+i+1,a+n+1,res-1)-a-1;
        int pos2=seg.query(1,2,n,pos,a[i])-1;
        if(pos2<=i) continue;
        assert(sum>a[i]+a[pos2]&&a[i]+a[pos2]>a[pos2+1]);
        ans=max(ans,sum+a[i]+a[pos2]+a[pos2+1]);
        if(pos2==pos)
        {
            ll csum=a[i]+a[pos2];
            int pos=upper_bound(a+pos2+2,a+n+2,csum-1)-a-1;
            ans=max(ans,sum+a[i]+a[pos2]+a[pos]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}