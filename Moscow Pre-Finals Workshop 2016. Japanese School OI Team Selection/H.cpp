#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot;
char str[MAXN][MAXN];
int id[MAXN][MAXN];
struct edge{int to,cost;};
vector<edge> G[MAXN*MAXN];
int d[MAXN*MAXN];
int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};
void add_edge(int u,int v,int w)
{
    G[u].push_back((edge){v,w});
}
void dijkstra(int s)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d+1,d+tot+1,INF);
    d[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        int v=p.second;
        if(d[v]<p.first) continue;
        for(int i=0;i<(int)G[v].size();i++)
        {
            edge e=G[v][i];
            if(d[e.to]>d[v]+e.cost)
            {
                d[e.to]=d[v]+e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",str[i]);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(str[i][j]=='.') id[i][j]=++tot;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            if(str[i][j]=='#') continue;
            for(int k=0;k<4;k++)
            {
                int nx=i+dx[k],ny=j+dy[k];
                if(nx<0||nx>=n||ny<0||ny>=m||str[nx][ny]=='#') continue;
                add_edge(id[i][j],id[nx][ny],2);
            }
        }
    for(int i=0;i<n;i++)
    {
        int cur=-1;
        for(int j=0;j<m;j++)
        {
            if(str[i][j]=='#') {cur=-1; continue;}
            else
            {
                if(cur==-1) cur=j;
                else add_edge(id[i][j],id[i][cur],1);
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        int cur=-1;
        for(int j=m-1;j>=0;j--)
        {
            if(str[i][j]=='#') {cur=-1; continue;}
            else
            {
                if(cur==-1) cur=j;
                else add_edge(id[i][j],id[i][cur],1);
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        int cur=-1;
        for(int j=0;j<n;j++)
        {
            if(str[j][i]=='#') {cur=-1; continue;}
            else
            {
                if(cur==-1) cur=j;
                else add_edge(id[j][i],id[cur][i],1);
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        int cur=-1;
        for(int j=n-1;j>=0;j--)
        {
            if(str[j][i]=='#') {cur=-1; continue;}
            else
            {
                if(cur==-1) cur=j;
                else add_edge(id[j][i],id[cur][i],1);
            }
        }
    }
    int x,y,s,t;
    scanf("%d%d",&x,&y);
    s=id[x-1][y-1];
    scanf("%d%d",&x,&y);
    t=id[x-1][y-1];
    dijkstra(s);
    if(d[t]==INF) puts("-1"); else printf("%d\n",d[t]);
    return 0;
}
