#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<int> G[MAXN];
int d[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    memset(d,-1,sizeof(d));
    queue<int> que;
    que.push(1);
    d[1]=0;
    while(que.size())
    {
        int v=que.front(); que.pop();
        for(auto to:G[v])
        {
            if(d[to]==-1)
            {
                d[to]=d[v]+1;
                que.push(to);
            }
        }
    }
    int res=0;
    for(int i=1;i<=n;i++)
    {
        if(d[i]==-1) {puts("-1"); return 0;}
        res=max(res,d[i]);
    }
    int t=0;
    while((1<<t)<res) t++;
    printf("%d\n",t+1);
}