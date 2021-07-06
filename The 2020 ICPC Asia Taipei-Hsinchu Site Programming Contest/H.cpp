#include<bits/stdc++.h>
#define maxn 10005
#define maxm 500005
#define mp(a,b) make_pair(a,b)
using namespace std;
int n,m;
struct Edge
{
    int u,v,w;
}e[maxm];
bool operator < (Edge A,Edge B)
{
    return A.w<B.w;
}
int fa[maxn];
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
int minv;
long long ans;
int to[maxn],we[maxn],nxt[maxn],head[maxn],p;
void addedge(int u,int v,int w)
{
    to[++p]=v;we[p]=w;nxt[p]=head[u];head[u]=p;
    to[++p]=u;we[p]=w;nxt[p]=head[v];head[v]=p;
}
int rt;
inline int umin(int x,int y){return (x<y)?x:y;}
void dfs(int u,int fa,int minv)
{
    if(u!=rt)ans+=minv;
    if(u!=rt)printf("(%d,%d)\n",rt,u);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i],w=we[i];
        if(v==fa)continue;
        dfs(v,u,umin(minv,w));
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    }
    sort(e+1,e+m+1);
    for(int i=1;i<=n;++i)fa[i]=i;
    minv=1000000000;
    for(int i=m;i>=1;--i)
    {
        int u=find(e[i].u),v=find(e[i].v);
        if(u!=v)
        {
            fa[u]=v;
            minv=e[i].w;
        }
    }
    for(int i=1;i<=n;++i)fa[i]=i;
    for(int i=1;i<=m;++i)if(e[i].w>=minv)
    {
        int u=find(e[i].u),v=find(e[i].v);
        if(u!=v)
        {
            fa[u]=v;
            addedge(e[i].u,e[i].v,e[i].w);
            addedge(e[i].v,e[i].u,e[i].w);
        }
    }
    for(int i=1;i<=n;++i)
    {
        rt=i;
        dfs(i,i,1000000000);
    }
    printf("%lld\n",ans/2);
}