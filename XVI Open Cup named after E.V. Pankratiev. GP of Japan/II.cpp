#include<bits/stdc++.h>
#define MAXN 4005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,ll> P;
int N,T;
ll dp[MAXN][MAXN];
struct node
{
    ll t,p,f;
};
bool cmpn(node x,node y)
{
    return x.f<y.f;
}
vector<node> v;
vector<P> st[MAXN];
int pt[MAXN];
void add(int id,ll u,ll v)
{
    P p=P(u,v);
    while(pt[id]>1&&1LL*(st[id][pt[id]-1].F-st[id][pt[id]-2].F)*(p.S-st[id][pt[id]-1].S)>=1LL*(st[id][pt[id]-1].F-p.F)*(st[id][pt[id]-2].S-st[id][pt[id]-1].S)) st[id].pop_back(),pt[id]--;
    pt[id]++;
    st[id].push_back(p);
}
bool cmp(P x,P y)
{
    if(x.S!=y.S) return x.S<y.S;
    return x.F<y.F;
}
ll query(int id,ll x)
{
    ll l=-1,r=pt[id]-1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(st[id][mid].F*x+st[id][mid].S<=st[id][mid+1].F*x+st[id][mid+1].S) l=mid;
        else r=mid;
    }
    return st[id][r].F*x+st[id][r].S;
}
int main()
{
    scanf("%d%d",&N,&T);
    for(int i=0;i<N;i++)
    {
        ll t,p,f;
        scanf("%lld%lld%lld",&t,&p,&f);
        v.push_back((node){t,p,f});
    }
    sort(v.begin(),v.end(),cmpn);
    for(int i=0;i<=N;i++)
        for(int j=0;j<=T;j++)
            dp[i][j]=-INF;
    dp[0][0]=0;
    for(int i=1;i<=N;i++)
    {
        for(int j=0;j<=T;j++)
        {
            if(j==v[i-1].t) dp[i][j]=max(dp[i][j],v[i-1].p);
            if(j>=v[i-1].t&&pt[j-v[i-1].t]>0)
            {
                dp[i][j]=max(dp[i][j],query(j-v[i-1].t,v[i-1].f)-1LL*v[i-1].f*v[i-1].f+v[i-1].p);
            }
        }
        for(int j=0;j<=T;j++) 
            if(dp[i][j]!=-INF)
                add(j,2*v[i-1].f,dp[i][j]-1LL*v[i-1].f*v[i-1].f);
    }
    ll ans=-INF;
    for(int i=0;i<=N;i++)
        for(int j=0;j<=T;j++)
            ans=max(ans,dp[i][j]);
    printf("%lld\n",ans);
    return 0;
}