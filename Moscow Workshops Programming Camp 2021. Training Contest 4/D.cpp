#include<bits/stdc++.h>
#define MAXN 1200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
int n,m;
vector<P> edges;
int n1,n2;
vector<int> G[MAXN];
int mx[MAXN],my[MAXN];
queue<int> que;
int dx[MAXN],dy[MAXN];
bool vis[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
bool find(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        if(!vis[G[u][i]]&&dy[G[u][i]]==dx[u]+1)
        {
            vis[G[u][i]]=true;
            if(!my[G[u][i]]||find(my[G[u][i]]))
            {
                mx[u]=G[u][i];
                my[G[u][i]]=u;
                return true;
            }
        }
    }
    return false;
}
int matching()
{
    memset(mx,0,sizeof(mx));
    memset(my,0,sizeof(my));
    int ans=0;
    while(true)
    {
        bool flag=false;
        while(!que.empty()) que.pop();
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));
        for(int i=1;i<=n1;i++)
            if(!mx[i]) que.push(i);
        while(!que.empty())
        {
            int u=que.front();
            que.pop();
            for(int i=0;i<G[u].size();i++)
                if(!dy[G[u][i]])
                {
                    dy[G[u][i]]=dx[u]+1;
                    if(my[G[u][i]])
                    {
                        dx[my[G[u][i]]]=dy[G[u][i]]+1;
                        que.push(my[G[u][i]]);
                    }
                    else flag=true;
                }
        }
        if(!flag) break;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n1;i++)
            if(!mx[i]&&find(i)) ans++;
    }
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    n1=m;
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        edges.push_back(P(u,v));
        add_edge(i+1,3*(u-1)+1+m);  add_edge(i+1,3*(u-1)+2+m);  add_edge(i+1,3*(u-1)+3+m); 
        add_edge(i+1,3*(v-1)+1+m);  add_edge(i+1,3*(v-1)+2+m);   add_edge(i+1,3*(v-1)+3+m); 
    }
    if(matching()!=m) {puts("no"); return 0;}
    printf("%d %d\n",n,m);
    for(int i=0;i<m;i++)
    {
        int u=edges[i].F,v=edges[i].S;
        if((mx[i+1]-m+2)/3==u) printf("%d %d\n",u,v);
        else printf("%d %d\n",v,u);
    }
    return 0;
}
