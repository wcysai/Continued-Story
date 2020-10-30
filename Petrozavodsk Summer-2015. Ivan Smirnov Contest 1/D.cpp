#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
int n;
int d[MAXN];
set<int> save[MAXN];
void go(int v)
{
    d[v]=0;
    queue<int> que;
    que.push(v);
    while(que.size())
    {
        int v=que.front(); que.pop();
        for(auto to:G[v])
            if(d[to]>d[v]+1)
            {
                d[to]=d[v]+1;
                que.push(to);
            }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    for(int i=1;i<=n;i++) d[i]=INF;
    go(1);
    int maxi=0;
    for(int i=2;i<=n;i++) 
    {
        maxi=max(maxi,d[i]);
        save[d[i]].insert(i);
    }
    for(int i=0;i<n-2;i++)
    {
tt:     while(save[maxi].size()) 
        {
            int v=*save[maxi].begin();
            if(d[v]<maxi)
            {
                save[d[v]].insert(v);
                save[maxi].erase(save[maxi].begin());
            }
            else break;
        }
        if(!save[maxi].size()) {maxi--; goto tt;}
        int v=*save[maxi].begin();
        save[maxi].erase(save[maxi].begin());
        go(v);
    }
    int ans=-1;
    for(int i=1;i<=n;i++) if(d[i]!=0) ans=i;
    printf("%d\n",ans);
    return 0;
}