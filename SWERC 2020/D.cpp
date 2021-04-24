#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int n,m,L,R;
struct edge
{
    int to,w,id,next;
}e[maxn<<1];
int head[maxn],p;
void addedge(int u,int v,int w,int id)
{
    e[++p].to=v;e[p].w=w;e[p].id=id;e[p].next=head[u];head[u]=p;
    e[++p].to=u;e[p].w=w;e[p].id=id;e[p].next=head[v];head[v]=p;
}
const int inf = 1000000000;
int dis[maxn];
priority_queue< pair<int,int> > q;
int Ans[maxn];
void dijkstra(int s)
{
    for(int i=1;i<=n;++i)dis[i]=inf;
    dis[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int u=q.top().second;q.pop();
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to,w=e[i].w;
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                q.push(make_pair(-dis[v],v));
            }
        }
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&L,&R);
    for(int i=1;i<=m;++i)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        u++;v++;
        addedge(u,v,w,i);
    }
    dijkstra(1);
    for(int u=1;u<=n;++u)if(2*dis[u]<R)
    {
        for(int i=head[u];i;i=e[i].next)
        {
            int id=e[i].id;
            Ans[id]=1;
        }
    }
    int ans=0;
    for(int i=1;i<=m;++i)ans+=Ans[i];
    printf("%d\n",ans);
}