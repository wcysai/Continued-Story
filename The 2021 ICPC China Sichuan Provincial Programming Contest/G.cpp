#include<bits/stdc++.h>
#define MAXN 500005
#define MAXW 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,q,w[MAXN];
vector<int> G[MAXN];
vector<int> cur;
vector<int> nodes[MAXN];
vector<P> level[MAXW];
int ans[MAXN];
int dist[MAXN];
void bfs()
{
    for(int i=1;i<=n;i++) dist[i]=INF;
    queue<int> que;
    for(auto x:cur) {dist[x]=0; que.push(x);}
    while(que.size())
    {
        int v=que.front(); que.pop();
        for(auto to:G[v])
        {
            if(dist[to]==INF)
            {
                dist[to]=dist[v]+1;
                que.push(to);
            }
        }
    } 
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&w[i]);
        nodes[w[i]].push_back(i);
    }
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for(int i=0;i<q;i++)
    {
        int p,w;
        scanf("%d%d",&p,&w);
        level[w].push_back(P(p,i));
    }
    for(int i=1;i<=100;i++)
    {
        for(auto x:nodes[i]) cur.push_back(x);
        bfs();
        for(auto p:level[i]) ans[p.S]=(dist[p.F]==INF?-1:dist[p.F]);
    }
    for(int i=0;i<q;i++) printf("%d\n",ans[i]);
    return 0;
}