#include<bits/stdc++.h>
#define maxn 305
#define mp(a,b) make_pair(a,b)
#define INF 1000000000000000000LL
#define F first
#define S second
using namespace std;
typedef long long ll;
int n;
int Q[maxn][maxn];
int s[maxn][maxn];
ll dp[maxn][maxn];
vector< pair<ll,ll> > g[maxn];
vector<pair<ll,ll> > st[maxn];
int t[maxn];
void add(int id,ll u,ll v)
{
    pair<ll,ll> p=make_pair(u,v);
    while(t[id]>1) 
    {
        __int128 x=(st[id][t[id]-1].F-st[id][t[id]-2].F);
        x=x*(p.S-st[id][t[id]-1].S);
        __int128 y=(st[id][t[id]-1].F-p.F);
        y=y*(st[id][t[id]-2].S-st[id][t[id]-1].S);
        if(x>=y)
        {
            st[id].pop_back();
            t[id]--;
        }
        else break;
    }
    st[id].push_back(p);
    t[id]++;
}
ll query(int id,ll x)
{
    ll l=-1,r=t[id]-1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(st[id][mid].F*x+st[id][mid].S<=st[id][mid+1].F*x+st[id][mid+1].S) l=mid;
        else r=mid;
    }
    return st[id][r].F*x+st[id][r].S;
}
int get(int k,int l,int r)//[l,k] [k,r]
{
	return s[k][r]-s[k][k-1]-s[l-1][r]+s[l-1][k-1];
}
ll dfs(int l,int r)
{
	if(l>r)return 0;
	if(dp[l][r]!=-INF) return dp[l][r];
	for(int k=l;k<=r;++k)
	{
		dp[l][r]=max(dp[l][r],dfs(l,k-1)+dfs(k+1,r)+query(k,get(k,l,r)));
	}
	return dp[l][r];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)scanf("%d",&Q[i][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)s[i][j]=s[i-1][j]+s[i][j-1]+Q[i][j]-s[i-1][j-1];
	for(int i=1;i<=n;++i)
	{
		int k;
		scanf("%d",&k);
		while(k--)
		{
			ll v,c;
			scanf("%lld%lld",&v,&c);
			g[i].push_back(mp(v,-c));
		}
	}
    memset(t,0,sizeof(t));
    for(int i=1;i<=n;i++)
    {
        sort(g[i].begin(),g[i].end());
        for(auto p:g[i])
            add(i,p.F,p.S);
    }
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            dp[i][j]=-INF;
	printf("%lld\n",dfs(1,n));
}