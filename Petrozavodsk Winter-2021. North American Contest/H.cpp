#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
ll a[MAXN],b[MAXN],d[MAXN];
ll st[MAXN][18];
int pre[MAXN];
void init(int n,ll *arr)
{
    pre[1]=0;
    for(int i=2;i<=n;i++)
    {
        pre[i]=pre[i-1];
        if ((1<<pre[i]+1)==i) ++pre[i];
    }
    for(int i=n;i>=1;--i)
    {
        st[i][0]=arr[i];
        for(int j=1;(i+(1<<j)-1)<=n;++j)
            st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
    }
}
ll query(int l,int r)
{
    int len=r-l+1,k=pre[len];
    return max(st[l][k],st[r-(1<<k)+1][k]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) b[i]=a[i];
    sort(b+1,b+n+1);
    for(int i=1;i<=n-1;i++) d[i]=b[i+1]-b[i];
    init(n-1,d);
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=b[i])
        {
            int l=lower_bound(b+1,b+n+1,a[i])-b;
            int r=lower_bound(b+1,b+n+1,b[i])-b;
            if(l>r) swap(l,r);
            ans=max(ans,query(l,r-1));
        }
    }
    printf("%lld\n",ans);
    return 0;
}