#include<bits/stdc++.h>
#define MAXN 500005
#define INF 2000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
struct edge{int to,cost;};
vector<edge> G[MAXN];
bool centroid[MAXN];
int des[MAXN];
int sz[MAXN],d[MAXN];
int ans;
int maxi,mini;
bool valid[MAXN];
void add_edge(int u,int v,int w)
{
    G[u].push_back((edge){v,w});
    G[v].push_back((edge){u,w});
}
P getroot(int v,int p,int t)
{
    P res=P(INT_MAX,-1);
    int m=0;
    sz[v]=1;
    for(auto e:G[v])
    {
        int to=e.to;
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
void getdeep(int v,int p)
{
    if(des[v]!=-1) 
    {
        maxi=max(maxi,des[v]-d[v]);
        mini=min(mini,des[v]-d[v]);
    }
    for(auto e:G[v])
    {
        int to=e.to;
        if(to==p||centroid[to]) continue;
        d[to]=d[v]+e.cost;
        getdeep(to,v);
    }
}
void check(int v,int p,int maxi,int mini)
{
    if(mini==INF);
    else if(mini!=maxi||d[v]!=mini) valid[v]=false;
    for(auto e:G[v])
    {
        int to=e.to;
        if(to==p||centroid[to]) continue;
        check(to,v,maxi,mini);
    }
}
vector<P> save;
vector<P> pre,suf;
void solve(int v)
{
    centroid[v]=true;
    d[v]=0; 
    save.clear();
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(centroid[to]) continue;
        maxi=-INF,mini=INF;
        d[to]=cost;
        getdeep(to,v);
        save.push_back(P(maxi,mini));
    }
    pre.clear(); suf.clear();
    pre.resize(save.size()); suf.resize(save.size());
    for(int i=0;i<(int)save.size();i++) if(i==0) pre[i]=save[i]; else {pre[i].F=max(save[i].F,pre[i-1].F); pre[i].S=min(save[i].S,pre[i-1].S);}
    for(int i=(int)save.size()-1;i>=0;i--) if(i==(int)save.size()-1) suf[i]=save[i]; else {suf[i].F=max(save[i].F,suf[i+1].F); suf[i].S=min(save[i].S,suf[i+1].S);}
    P p=P(-INF,INF);
    if(des[v]!=-1) p=P(des[v],des[v]);
    int cnt=0;
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(centroid[to]) continue;
        P q=p;
        if(cnt!=0) {q.F=max(q.F,pre[cnt-1].F); q.S=min(q.S,pre[cnt-1].S);}
        if(cnt!=(int)save.size()-1) {q.F=max(q.F,suf[cnt+1].F); q.S=min(q.S,suf[cnt+1].S);}
        check(to,v,q.F,q.S);
        cnt++;
    }
    P q=p;
    if(suf.size()) {q.F=max(q.F,suf[0].F); q.S=min(q.S,suf[0].S);}
    if(q.S==INF);
    else if(q.F!=q.S||q.F!=0) valid[v]=false;
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(centroid[to]) continue;
        int rt=getroot(to,v,sz[to]).S;
        solve(rt);
    }
}
void go()
{
    int rt=getroot(1,0,n).S;
    solve(rt);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n-1;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
    }
    memset(des,-1,sizeof(des));
    memset(valid,true,sizeof(valid));
    for(int i=0;i<k;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        des[x]=y;
    }
    go();
    vector<int> ans;
    for(int i=1;i<=n;i++) if(valid[i]) ans.push_back(i);
    printf("%d\n",(int)ans.size());
    for(auto x:ans) printf("%d ",x);
    puts("");
    return 0;
}