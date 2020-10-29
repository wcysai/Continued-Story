#include<bits/stdc++.h>
#define maxn 210005
using namespace std;
const int inf = 1000000000;
const int bas1=31,bas2=37;
const int mod1=1000000007,mod2=998244353;
int xp1[maxn],xp2[maxn];
int del1(int x,int c)
{
    return (x-c+mod1)%mod1;
}
int del2(int x,int c)
{
    return (x-c+mod2)%mod2;
}
int add1(int x,int c)
{
    return (1ll*x*bas1%mod1+c)%mod1;
}
int add2(int x,int c)
{
    return (1ll*x*bas2%mod2+c)%mod2;
}
int n;
char IN[maxn];
string s[205];
int Len[205];
map<pair<int,int>,int> mp;
struct edge{int to,next,f;};
struct Maxflow
{
    int head[maxn],p,s,t;
    edge e[maxn*6];
    void addedge(int u,int v,int f)
    {
        e[p].to=v;e[p].f=f;e[p].next=head[u];head[u]=p++;
        e[p].to=u;e[p].f=0;e[p].next=head[v];head[v]=p++;
    }
    int dis[maxn];
    bool bfs(int s,int t)
    {
        memset(dis,0,sizeof(dis));
        queue<int> q;q.push(s);dis[s]=1;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=head[u];~i;i=e[i].next)
            {
                int v=e[i].to,f=e[i].f;
                if(f&&(!dis[v]))dis[v]=dis[u]+1,q.push(v);
            }
        }
        return dis[t]!=0;
    }
    int dfs(int u,int maxf,int t)
    {
        if(u==t)return maxf;
        int t