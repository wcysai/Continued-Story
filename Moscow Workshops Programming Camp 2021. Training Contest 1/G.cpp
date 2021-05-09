#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
vector<P> v;
int h[MAXN];
int st[MAXN],t;
int s[MAXN],e[MAXN];
ll w[MAXN];
int fa[MAXN],ls[MAXN],rs[MAXN],son[MAXN],root;
ll val[MAXN];
vector<ll> ans;
void compute_weight(int cur,int l,int r)
{
    if(!cur) return;
    if(l>r) return;
    w[cur]=1LL*(r-l)*(fa[cur]?(v[cur-1].F-v[fa[cur]-1].F):v[cur-1].F);
    compute_weight(ls[cur],l,s[cur]); compute_weight(rs[cur],e[cur],r);
}
void dfs(int v)
{
    if(ls[v])
    {
        dfs(ls[v]);
        if(val[ls[v]]+w[v]>val[son[v]]+w[v]) son[v]=ls[v];
    }
    if(rs[v])
    {
        dfs(rs[v]);
        if(val[rs[v]]+w[v]>val[son[v]]+w[v]) son[v]=rs[v];
    }
    val[v]=val[son[v]]+w[v];
    if(ls[v]&&son[v]!=ls[v]) ans.push_back(val[ls[v]]);
    if(rs[v]&&son[v]!=rs[v]) ans.push_back(val[rs[v]]);
    if(v==root) ans.push_back(val[v]);
}
int main()
{
    scanf("%d",&n);
    int lastx,lasty,x,y;
    scanf("%d%d",&x,&y);
    lastx=lasty=0;
    for(int i=0;i<n-1;i++)
    {
        scanf("%d%d",&x,&y);
        if(y==lasty) 
        {
            v.push_back(P(y,x-lastx));
            s[(int)v.size()]=lastx;
            e[(int)v.size()]=x;
        }
        lastx=x; lasty=y;
    }
    int sz=(int)v.size();
    t=0;
    for(int i=1;i<=sz;i++)
    {
        while(t&&v[st[t-1]-1].F>v[i-1].F) ls[i]=st[--t];
        if(t) rs[st[t-1]]=i;
        st[t++]=i;
    }
    for(int i=1;i<=sz;i++) fa[ls[i]]=fa[rs[i]]=i;
    for(int i=1;i<=sz;i++) if(!fa[i]) root=i;
    compute_weight(root,0,lastx);
    ans.clear();
    memset(val,0,sizeof(val));
    dfs(root);
    scanf("%d",&k);
    ll res=0;
    sort(ans.begin(),ans.end(),greater<ll>());
    for(int i=0;i<min(k,(int)ans.size());i++) res+=ans[i];
    printf("%lld\n",res);
    return 0;
}