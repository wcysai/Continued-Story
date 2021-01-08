#include<bits/stdc++.h>
#define mp(a,b) make_pair(a,b)
#define maxn 800005
using namespace std;
int n;
int L[maxn],R[maxn],c[maxn];
vector< pair<int,int> > g[maxn];
int dis[maxn],cnt[maxn],inq[maxn];
vector<int> Ans;
bool spfa()
{
    queue<int> q;
    for(int i=0;i<=4*n;++i)
    {
        dis[i]=0;
        q.push(i);
    }
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=0;
        for(auto p:g[u])
        {
            int v=p.first,w=p.second;
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                if(!inq[v])
                {
                    ++cnt[v];
                    if(cnt[v]>n)return 0;
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
    return 1;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&L[i],&R[i]);
        L[i]++;R[i]++;
        g[L[i]-1].push_back(mp(R[i],1));
        g[R[i]].push_back(mp(L[i]-1,-1));
        cerr<<L[i]-1<<" "<<R[i]<<" "<<1<<endl;
        cerr<<R[i]<<" "<<L[i]-1<<" "<<-1<<endl;
        c[L[i]]++;c[R[i]]--;
    }
    for(int i=1;i<=4*n;++i)c[i]+=c[i-1];
    for(int i=0;i<=4*n-1;++i)if(!c[i])
    {
        g[i+1].push_back(mp(i,0));
        g[i].push_back(mp(i+1,0));
    }
    if(!spfa())
    {
        puts("-1");
    }
    else
    {
        for(int i=0;i<=4*n;++i)cerr<<dis[i]<<endl;
        for(int i=1;i<=4*n;++i)
        {
            if(dis[i]!=dis[i-1])Ans.push_back(i-1);
        }
        printf("%d\n",Ans.size());
        for(int x:Ans)printf("%d ",x);
    }
}
