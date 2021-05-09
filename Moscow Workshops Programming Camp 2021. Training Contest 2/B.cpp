#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,k,a[MAXN];
vector<int> G[MAXN];
int val[MAXN],p[MAXN],r[MAXN],cnt[MAXN];
ll ans;
void init(int n)
{
    for(int i=1;i<=n;i++) 
    {
        p[i]=i;
        r[i]=0;
        cnt[i]=1;
    }
}
int find(int v)
{
    if(p[v]==v) return v;
    return p[v]=find(p[v]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    if(r[x]<r[y])
    {
        p[x]=y;
        ans-=1LL*cnt[x]*(cnt[x]-1)/2;
        ans-=1LL*cnt[y]*(cnt[y]-1)/2;
        cnt[y]+=cnt[x];
        ans+=1LL*cnt[y]*(cnt[y]-1)/2;
    }
    else
    {
        p[y]=x;
        ans-=1LL*cnt[x]*(cnt[x]-1)/2;
        ans-=1LL*cnt[y]*(cnt[y]-1)/2;
        cnt[x]+=cnt[y];
        ans+=1LL*cnt[x]*(cnt[x]-1)/2;
        if(r[x]==r[y]) r[x]++;
    }
}
void dfs(int v,int p,int d)
{
    val[v]=min(val[v],d);
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v,d+1);
    }
}
bool cmp(int x,int y)
{
    return val[x]>val[y];
}
bool used[MAXN];
vector<int> v;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for(int i=1;i<=n;i++) val[i]=INF;
    dfs(1,0,0); dfs(2,0,0);
    for(int i=1;i<=n;i++) v.push_back(i);
    sort(v.begin(),v.end(),cmp);
    memset(used,false,sizeof(used));
    int now=0;
    ans=0;
    init(n);
    ll res=0;
    while(now<(int)v.size())
    {
        int tmp=now;
        int cur=val[v[tmp]];
        ll ctmp=ans;
        while(now<(int)v.size()&&val[v[now]]==cur)
        {
            used[v[now]]=true;
            for(auto to:G[v[now]])
            {
                if(used[to]) unite(v[now],to);
            }
            now++;
        }
        res+=cur*(ans-ctmp);
    }
    printf("%lld\n",res);
    return 0;
}
