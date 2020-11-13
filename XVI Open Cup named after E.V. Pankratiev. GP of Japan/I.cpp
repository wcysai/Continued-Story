#include<bits/stdc++.h>
#define ll long long
#define maxn 4005
using namespace std;
int n,T;
struct DT
{
    ll t,p,f;
}a[maxn];
ll sqr(ll x){return x*x;}
bool operator < (DT A,DT B)
{
    return A.f<B.f;
}
struct node
{
    int x,l,r;
    node(int x=0,int l=0,int r=0):x(x),l(l),r(r){}
}q[maxn][maxn/2];
int head[maxn],tail[maxn];
ll dp[maxn][maxn];
ll calc(int k,int x,int y)
{
    return dp[x][k]+a[y].p-sqr(a[y].f-a[x].f);
}
void add(int k,int x)
{
    if(calc(k,x,n)<=calc(k,q[k][tail[k]].x,n))return;
    while(head[k]<=tail[k]&&calc(k,x,q[k][tail[k]].l)>=calc(k,q[k][tail[k]].x,q[k][tail[k]].l))tail[k]--;
    if(head[k]>tail[k])
    {
        q[k][head[k]=tail[k]=1]=node(x,x+1,n);
        return;
    }
    int l=q[k][tail[k]].l,r=q[k][tail[k]].r;
    int ans=l;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(calc(k,x,mid)<=calc(k,q[k][tail[k]].x,mid))ans=mid,l=mid+1;
        else r=mid-1;
    }
    q[k][tail[k]].r=ans-1;
    ++tail[k];
    q[k][tail[k]]=node(x,ans,n);
}
int main()
{
    scanf("%d%d",&n,&T);
    for(int i=1;i<=n;++i)scanf("%lld%lld%lld",&a[i].t,&a[i].p,&a[i].f);
    sort(a+1,a+n+1);
    ll ans=0;
    for(int k=0;k<=T;++k)
        for(int i=0;i<=n;++i)dp[k][i]=-(ll)(1e18);
    dp[0][0]=0;
    for(int i=1;i<=T;++i)head[i]=1,tail[i]=0;
    q[0][head[0]=tail[0]=0]=node(0,1,n);
    for(int i=1;i<=n;++i)
    {
        for(int k=T;k>=1;--k)if(k-a[i].t>=0)
        {
            if(head[k-a[i].t]>tail[k-a[i].t])continue;
            while(q[k-a[i].t][head[k-a[i].t]].r<i)++head[k-a[i].t];
            //cerr<<k-a[i].t<<" "<<q[k-a[i].t][head[k-a[i].t]].x<<" "<<q[k-a[i].t][head[k-a[i].t]].l<<" "<<q[k-a[i].t][head[k-a[i].t]].r<<endl;
            dp[i][k]=calc(k-a[i].t,q[k-a[i].t][head[k-a[i].t]].x,i);
            if(k==a[i].t)dp[i][k]+=sqr(a[i].f);
            //cerr<<i<<" "<<k<<" "<<dp[i][k]<<endl;
            add(k,i);
            ans=max(ans,dp[i][k]);
        }
    }
    cout<<ans<<endl;
}
