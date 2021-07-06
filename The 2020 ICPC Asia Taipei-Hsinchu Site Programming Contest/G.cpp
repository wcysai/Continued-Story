#include<bits/stdc++.h>
#define maxn 2000005
#define ull unsigned long long
using namespace std;
const ull bas=31;
int T,m;
int n;
int prime[maxn*2],flg[maxn*10],tot;
void getprime()
{
    int N=20000000;
    for(int i=2;i<=N;++i)
    {
        if(!flg[i])prime[++tot]=i;
        for(int j=1;j<=tot&&prime[j]<=N/i;++j)
        {
            flg[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
}
vector<int> g[maxn];
int d[maxn];
void toposort()
{
    queue<int> q;
    for(int i=1;i<=n;++i)if(d[i]==1)q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int v:g[u])
        {
            d[v]--;
            if(d[v]==1)q.push(v);
        }
    }
}
int sz[maxn];
ull f[maxn];
void dfs(int u,int fa)
{
    sz[u]=1;f[u]=1;
    for(int v:g[u])if(v!=fa&&d[v]!=2)
    {
        dfs(v,u);
        sz[u]+=sz[v];
        f[u]+=f[v]*(ull)prime[sz[v]];
    }
}
ull b[maxn],c[maxn];
int cnt;
void getcircle(int u,int fa,int from)
{
    if(u==from&&fa==0)return;
    b[cnt++]=f[u];
    for(int v:g[u])if(v!=fa&&d[v]==2)
    {
        getcircle(v,u,from);
    }
}
void sp()
{
    for(int i=1;i<=cnt;++i)b[i+cnt]=b[i];
    int i,j,k,l;
    for(i=0,j=1;j<cnt;)
    {
        for(k=0;k<cnt&&b[i+k]==b[j+k];++k);
        if(k>=cnt)break;
        if(b[i+k]<b[j+k])j+=k+1;
        else
        {
            l=i+k;
            i=j;
            j=max(l,j)+1;
        }
    }
    for(int x=0;x<cnt;++x)c[x+1]=b[x+i];
}
pair<ull,ull> solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)g[i].clear(),d[i]=0,f[i]=0,sz[i]=0,b[i]=0;
    for(int i=1;i<=n;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);d[u]++;
        g[v].push_back(u);d[v]++;
    }
    toposort();
    for(int i=1;i<=n;++i)if(d[i]!=2)d[i]=0;
    for(int i=1;i<=n;++i)if(d[i]==2)dfs(i,0);
    cnt=0;
    for(int i=1;i<=n;++i)if(d[i]==2)
    {
        getcircle(i,0,i);
    }
    sp();
    ull h1=0,h2=0;
    for(int i=1;i<=cnt;++i)
    {
        h1=h1*bas+c[i];
    }
    for(int i=cnt;i>=1;--i)
    {
        h2=h2*bas+c[i];
    }
    return make_pair(h1,h2);
}
pair<ull,ull> a[maxn];
int main()
{
    getprime();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&m);
        for(int i=1;i<=m;++i)a[i]=solve();
        sort(a+1,a+m+1);
        int ans=0;
        for(int i=1;i<=m;++i)if(a[i]!=a[i-1])ans++;
        printf("%d\n",ans);
    }
}