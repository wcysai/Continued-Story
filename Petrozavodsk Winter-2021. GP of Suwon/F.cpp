#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,ll> P;
int n,m,q;
vector<P> G[MAXN];
int val[MAXN];
int color[MAXN];
int cnt[MAXN][30];
vector<int> basis;
void dfs(int v,int p)
{
    color[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i].F;
        int cost=G[v][i].S;
        if(color[to]==0)
        {
            val[to]=val[v]^cost;
            dfs(to,v);
        }
        else if(color[to]==1)
        {
            basis.push_back(val[v]^val[to]^cost);
        }
    }
    color[v]=2;
}
ll bas[62];
void add_basis(int x)
{
    for(int j=29;j>=0;j--)
    {
        if(x&(1<<j))
        {
            if(!bas[j])
            {
                bas[j]=x;
                break;
            }
            x^=bas[j];
        }
    }
}
int query(int x)
{
    for(int j=29;j>=0;j--)
    {
        if(!(x&(1ll<<j)))
            if(bas[j]) x^=bas[j];
    }
    return x;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back(P(v,w)); G[v].push_back(P(u,w));
    }
    val[1]=0;
    memset(color,0,sizeof(color));
    dfs(1,0);
    for(auto x:basis) add_basis(x);
    for(int i=1;i<=n;i++)
        for(int j=0;j<30;j++)
             if(val[i]&(1<<j)) cnt[i][j]=cnt[i-1][j]+1; else cnt[i][j]=cnt[i-1][j];
    for(int i=0;i<q;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int len=r-l+1,mask=0;
        bool odd=false;
        ll num=1LL*len*(len-1)/2;
        int nmask;
        if(num&1) nmask=(1<<30)-1; else nmask=0;
        int ans=0;
        for(int j=0;j<30;j++)
        {
            int x=(cnt[r][j]-cnt[l-1][j]);
            if((1LL*x*(len-x))&1) mask^=(1<<j);
        }
        for(int j=29;j>=0;j--)
        {
            if(mask&(1<<j)) ans^=(1<<j);
            if((nmask^mask)&(1<<j))
            {
                if(bas[j])
                {
                    ans^=(1<<j);
                    mask^=bas[j];
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}