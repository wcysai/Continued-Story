#include<bits/stdc++.h>
#define MAXN 300005
#define MAXLOGN 19
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,ll> P;
int n,k;
vector<P> G[MAXN];
struct edge
{
    int u,v,cost;
};
bool cmp(edge x,edge y)
{
    return x.cost<y.cost;
}
vector<edge> E;
ll ans=0;
int cost[MAXN];//cost[i]: minimum weight to get i connected components
int p[MAXN],r[MAXN],mini[MAXN];
vector<int> v[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        r[i]=0;
        mini[i]=i;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y,int w)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    v[max(mini[x],mini[y])].push_back(w);
    if(r[x]<r[y]) {p[x]=y; mini[y]=min(mini[x],mini[y]);} 
    else
    {
        p[y]=x;
        mini[x]=min(mini[x],mini[y]);
        if(r[x]==r[y]) r[x]++;
    }
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
ll bit[2][MAXN+1];
ll sum(int id,int i)
{
    ll s=0;
    while(i>0)
    {
        s+=bit[id][i];
        i-=i&-i;
    }
    return s;
}
void add(int id,int i,int x)
{
    while(i<=n)
    {
        bit[id][i]+=x;
        i+=i&-i;
    }
}
int bisearch(int id,ll v)
{
    ll sum=0;
    int pos=0;
    for(int i=MAXLOGN;i>=0;i--)
    {
        if(pos+(1<<i)<=n&&sum+bit[id][pos+(1<<i)]<v)
        {
            sum+=bit[id][pos+(1<<i)];
            pos+=(1<<i);
        }
    }
    return pos+1;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n-1;i++)
    {
        int u,v,cost;
        scanf("%d%d%d",&u,&v,&cost);
        E.push_back((edge){u,v,cost});
    }
    init(n);
    sort(E.begin(),E.end(),cmp);
    for(auto e:E) unite(e.u,e.v,e.cost);
    memset(bit,0,sizeof(bit));
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        for(auto x:v[i])
        {
            add(0,n+1-x,1);
            add(1,n+1-x,x);
        }
        int pos=bisearch(0,min(k,i-1));
        printf("%lld\n",sum(1,pos)-1LL*(n-pos+1)*(sum(0,pos)-min(k,i-1)));
    }
    return 0;
}