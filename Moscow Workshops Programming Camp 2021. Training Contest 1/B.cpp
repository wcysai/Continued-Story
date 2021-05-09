#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 200005
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
int n,m;
int p[MAXN],r[MAXN],cnt[MAXN];
int u[MAXN],v[MAXN];
bool vis[MAXN];
bool f;
void init(int n)
{
    for(int i=1;i<=200000;i++) 
    {
        p[i]=i;
        r[i]=0;
        cnt[i]=1;
    }
}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int find(int x)
{
    if(p[x]==x) return x;
    return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x); y=find(y);
    if(x==y) {f=false; return;}
    if(r[x]<r[y])
    {
        p[x]=y;
        cnt[y]+=cnt[x];
    }
    else
    {
        p[y]=x;
        cnt[x]+=cnt[y];
        if(r[x]==r[y]) r[x]++;
    }
}
vector<int> dis;
int main()
{
    scanf("%d%d",&n,&m);
    f=true;
    init(n);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        dis.push_back(u[i]); dis.push_back(v[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    if(dis.size()>n) {puts("0"); return 0;}
    for(int i=0;i<m;i++)
    {
        int x=lower_bound(dis.begin(),dis.end(),u[i])-dis.begin()+1;
        int y=lower_bound(dis.begin(),dis.end(),v[i])-dis.begin()+1;
        unite(x,y);
    }
    if(!f) {puts("0"); return 0;}
    if(n-m==1) {puts("1"); return 0;}
    int ans=pow_mod(n,n-m-2);
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=(int)dis.size();i++) if(!vis[find(i)]) {vis[find(i)]=true; ans=1LL*ans*cnt[find(i)]%MOD;}
    printf("%d\n",ans);
    return 0;
}
