#include<bits/stdc++.h>
#define MAXN 25
#define MAXM 105
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<P> G[MAXN];
int u[MAXM],v[MAXM];
int fa[MAXN],faid[MAXN],dep[MAXN];
int cnt[(1<<20)],f[(1<<20)];
int dp[(1<<20)];
int fact[(1<<20)];
int invf[(1<<20)];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dfs(int v,int p,int id,int d)
{
    dep[v]=d; fa[v]=p; faid[v]=id;
    for(auto e:G[v])
    {
        int to=e.F;
        if(to==p) continue;
        dfs(to,v,e.S,d+1);
    }
}
int get_mask(int u,int v)
{
    int mask=0;
    while(dep[u]!=dep[v])
    {
        if(dep[u]<dep[v]) swap(u,v);
        mask^=(1<<faid[u]);
        u=fa[u];
    }
    while(u!=v)
    {
        mask^=(1<<faid[u]);
        mask^=(1<<faid[v]);
        u=fa[u]; v=fa[v];
    }
    return mask;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<(1<<20);i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[(1<<20)-1]=pow_mod(fact[(1<<20)-1],MOD-2);
    for(int i=(1<<20)-2;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        if(i<n-1)
        {
            G[u[i]].push_back(P(v[i],i));
            G[v[i]].push_back(P(u[i],i));
        }
    }
    dfs(1,0,-1,0);
    for(int i=n-1;i<m;i++) 
    {
        cnt[get_mask(u[i],v[i])]++;
    }
    for(int i=0;i<(1<<(n-1));i++)
		f[i]=cnt[i];
	for(int i=0;i<n-1;i++) 
	{
		for(int mask=0;mask<(1<<(n-1));mask++)
			if(mask&(1<<i))
				f[mask]+=f[mask^(1<<i)];
	}
    int notedge=m-(n-1);
    int num=cnt[0],rem=notedge-cnt[0]+n;
    dp[0]=1LL*fact[rem+num-1]*invf[rem-1]%MOD;
    for(int i=0;i<(1<<(n-1));i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(!(i&(1<<j)))
            {
                int num=f[i^(1<<j)]-f[i];
                int rem=(notedge-f[i^(1<<j)])+n-1-__builtin_popcount(i);
                add(dp[i^(1<<j)],1LL*dp[i]*fact[rem+num-1]%MOD*invf[rem-1]%MOD);
            }
        }
    }
    printf("%d\n",dp[(1<<(n-1))-1]);
    return 0;
}