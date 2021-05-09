#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot;
P v[MAXN];
int sum[MAXN],pre[MAXN];
int last[MAXN],cost[MAXN];
ll s[MAXN];
ll dp[2*MAXN];
ll compute_cost(int l,int r)
{
    int mid=(l+r)/2;//connect [l,mid] with [mid+1,r]
    return s[r]-s[mid]-(s[mid]-s[l-1]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        v[++tot]=P(x,0);
    }
    for(int i=0;i<m;i++)
    {
        int x;
        scanf("%d",&x);
        v[++tot]=P(x,1);
    }
    sort(v+1,v+tot+1);
    for(int i=1;i<=tot;i++) s[i]=s[i-1]+v[i].F;
    for(int i=1;i<=tot;i++) cost[i]=1000000000;
    int lasta=-1,lastb=-1;
    //precompute nearest neighbour
    for(int i=1;i<=tot;i++)
    {
        if(v[i].S==0&&lastb!=-1) cost[i]=min(cost[i],v[i].F-lastb);
        if(v[i].S==1&&lasta!=-1) cost[i]=min(cost[i],v[i].F-lasta);
        if(v[i].S==0) lasta=v[i].F;
        if(v[i].S==1) lastb=v[i].F;
    }
    //go in reverse order
    lasta=lastb=-1;
    for(int i=tot;i>=1;i--)
    {
        if(v[i].S==0&&lastb!=-1) cost[i]=min(cost[i],lastb-v[i].F);
        if(v[i].S==1&&lasta!=-1) cost[i]=min(cost[i],lasta-v[i].F);
        if(v[i].S==0) lasta=v[i].F;
        if(v[i].S==1) lastb=v[i].F;
    }
    memset(last,-1,sizeof(last));
    last[m]=0;
    for(int i=1;i<=tot;i++)
    {
        sum[i]=sum[i-1]+(v[i].S==0?1:-1);
        int x=sum[i]+m;
        if(last[x]!=-1) pre[i]=last[x]; else pre[i]=-1;
        last[x]=i;
    }
    last[n]=0; 
    for(int i=1;i<=tot;i++)
    {
        dp[i]=dp[i-1]+cost[i];
        if(pre[i]!=-1) dp[i]=min(dp[i],dp[pre[i]]+compute_cost(pre[i]+1,i));
    }
    printf("%lld\n",dp[tot]);
    return 0;
}