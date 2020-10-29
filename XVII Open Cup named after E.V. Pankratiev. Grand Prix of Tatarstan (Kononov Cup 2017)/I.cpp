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
        int tmp=0;
        for(int i=head[u];~i&&tmp<maxf;i=e[i].next)
        {
            int v=e[i].to,f=e[i].f;
            if(f&&dis[v]==dis[u]+1)
            {
                int minn=min(maxf-tmp,f);
                f=dfs(v,minn,t);
                tmp+=f;
                e[i].f-=f;e[i^1].f+=f;
            }
        }
        if(!tmp)dis[u]=inf;
        return tmp;
    }
    int dinic(int s,int t)
    {
        int ans=0;
        while(bfs(s,t))ans+=dfs(s,inf,t);
        return ans;
    }
}fl;
bool check(int k)
{
    mp.clear();
    memset(fl.head,-1,sizeof(fl.head));fl.p=0;
    fl.s=0;fl.t=210001;
    int cnt=0,num=0;
    for(int i=1;i<=n;++i)if(Len[i]>=k)
    {
        ++num;
        int v1=0,v2=0;
        for(int j=1;j<=k;++j)
        {
            v1=add1(v1,s[i][j]-'a'+1);
            v2=add2(v2,s[i][j]-'a'+1);
        }
        //cerr<<v1<<" "<<v2<<endl;
        if(!mp.count(make_pair(v1,v2)))mp[make_pair(v1,v2)]=++cnt;
        fl.addedge(i,mp[make_pair(v1,v2)]+n,1);
        for(int j=1;j<Len[i];++j)
        {
            v1=del1(v1,1ll*xp1[k-1]*(s[i][j]-'a'+1)%mod1);
            v2=del2(v2,1ll*xp2[k-1]*(s[i][j]-'a'+1)%mod2);
            //cerr<<i<<" "<<j<<" "<<v1<<" "<<v2<<endl;
            v1=add1(v1,s[i][j+k]-'a'+1);
            v2=add2(v2,s[i][j+k]-'a'+1);
            //cerr<<i<<" "<<j<<" "<<v1<<" "<<v2<<endl;
            if(!mp.count(make_pair(v1,v2)))mp[make_pair(v1,v2)]=++cnt;
            fl.addedge(i,mp[make_pair(v1,v2)]+n,1);
        }
    }
    for(int i=1;i<=n;++i)fl.addedge(fl.s,i,1);
    for(int i=1;i<=cnt;++i)fl.addedge(i+n,fl.t,1);
    return fl.dinic(fl.s,fl.t)==num;
}
int main()
{
    xp1[0]=xp2[0]=1;
    for(int i=1;i<=200000;++i)xp1[i]=1ll*xp1[i-1]*bas1%mod1,xp2[i]=1ll*xp2[i-1]*bas2%mod2;
    scanf("%d",&n);
    int l=1,r=1;
    for(int i=1;i<=n;++i)
    {
        scanf("%s",IN+1);
        Len[i]=strlen(IN+1);
        s[i].push_back(' ');
        for(int j=1;j<=Len[i];++j)s[i].push_back(IN[j]);
        for(int j=1;j<=Len[i];++j)s[i].push_back(s[i][j]);
        r=max(r,Len[i]);
    }
    int ans=r;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
}