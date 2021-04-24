#include<bits/stdc++.h>
#define MAXN 1000005
#define MAXLOGN 20
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,d[MAXN];
vector<int> G[MAXN],rG[MAXN];
int vis[MAXN],dist[MAXN];
bool oncyc[MAXN];                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
  
int to[MAXLOGN+1][MAXN];
ll sum[MAXLOGN+1][MAXN];
ll compute_sum(int x,int k)
{
    int now=x;
    ll s=x;
    for(int i=0;i<=MAXLOGN;i++)
    {
        if(k&(1<<i))
        {
            s+=sum[i][now]-now;
            now=to[i][now];
        }
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=1000000;i++)
        for(int j=i;j<=1000000;j+=i)
            d[j]++;
    for(int i=0;i<n;i++) d[i]=(d[i]+i)%n;
    for(int i=0;i<n;i++)
    {
        G[i].push_back(d[i]);
        rG[d[i]].push_back(i);
    }
    memset(vis,0,sizeof(vis));
    memset(oncyc,false,sizeof(oncyc));
    for(int i=0;i<n;i++)
    {
        if(!vis[i])
        {
            vector<int> v;
            int now=i,cnt=1;
            while(!vis[now])
            {
                v.push_back(now);
                vis[now]=cnt;
                now=d[now];
                cnt++;
            }
            int len=cnt-vis[now];
            queue<int> que;
            for(int j=(int)v.size()-1;j>=0;j--) {oncyc[v[j]]=true; dist[v[j]]=len-1; que.push(v[j]); if(v[j]==now) break;}
            while(que.size())
            {
                int x=que.front(); que.pop();
                for(auto to:rG[x])
                {
                    if(oncyc[to]) continue;
                    dist[to]=dist[x]+1;
                    vis[to]=1;
                    que.push(to);
                }
            }
        }
    }
    for(int i=0;i<n;i++) 
    {
        to[0][i]=d[i];
        sum[0][i]=i+d[i];
    }
    for(int k=0;k<MAXLOGN;k++)
        for(int i=0;i<n;i++) 
        {
            to[k+1][i]=to[k][to[k][i]];
            sum[k+1][i]=sum[k][i]+sum[k][to[k][i]]-to[k][i];
        }
    ll ans=INF;
    int id=-1;
    for(int i=0;i<n;i++) 
    {
        if(dist[i]<k-1) continue;
        if(compute_sum(i,k-1)<ans)
        {
            ans=compute_sum(i,k-1);
            id=i;
        }
    }
    if(ans==INF) {puts("-1"); return 0;}
    for(int i=0;i<k;i++)
    {
        printf("%d%c",id,i==k-1?'\n':' ');
        id=d[id];
    }
    return 0;
}