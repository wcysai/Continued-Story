//team continued story
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 500005
#define MAXLOGN 21
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
int n,m,rightmost[MAXN];
vector<int> rG[MAXN];//contain only right edges
vector<int> lG[MAXN];//contain only left edges
multiset<int> st;
int val[MAXN];
int dp[MAXLOGN][MAXN];//starting from i, what's the leftmost closure
struct segtree
{
    int maxi[4*MAXN];
    void pushup(int k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            maxi[k]=rightmost[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int p,int v)
    {
        if(l==r)
        {
            maxi[k]=v;
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid)update(k*2,l,mid,p,v); else update(k*2+1,mid+1,r,p,v);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return -INF;
        if(l>=x&&r<=y) return maxi[k];
        int mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
int save[MAXN];
int solve1(int pos,int last)// maximum <=last
{
    for(int k=18;k>=0;k--)
        if(dp[k][pos]<=last) pos=dp[k][pos];
    return pos;
}
int solve2(int pos,int last)//minimum >last
{
    int x=solve1(pos,last);
    return dp[0][x];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) rightmost[i]=i;
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        if(u>v) swap(u,v);
        rightmost[u]=max(rightmost[u],v);
        rG[u].push_back(v); lG[v].push_back(u);
    }
    int s=0;
    ll ans=0;
    //one up,one down
    //three separated regions
    set<int> lvalid,rvalid;
    st.clear();
    for(int i=1;i<=n;i++)
    {
        for(auto x:rG[i]) st.insert(x);
        if(!st.size()||(*(--st.end())<=i)) lvalid.insert(i); 
        if(st.size()<=1) ans=max(ans,1LL*i*(n-i)); 
        else
        {
            auto it=st.end();
            it--; it--;
            if(*it<=i) ans=max(ans,1LL*i*(n-i));
        }
    }
    st.clear();
    for(int i=n;i>=1;i--)
    {
        for(auto x:lG[i]) st.insert(x);
        if(!st.size()||(*st.begin()>=i)) rvalid.insert(n+1-i);
    }
    //maximize xy+yz+2xz
    for(auto x:lvalid)
    {
        //x+z<=n-1
        int maxi=min(n/2,n-1-x);
        auto it=rvalid.lower_bound(maxi);
        if(it!=rvalid.end())
        {
            int z=*it,y=n-x-z;
            if(x+z<=n-1) ans=max(ans,1LL*x*y+1LL*y*z+2LL*x*z);
        }
        if(it!=rvalid.begin())
        {
            it--;
            int z=*it,y=n-x-z;
            if(x+z<=n-1) ans=max(ans,1LL*x*y+1LL*y*z+2LL*x*z);
        }
    }
    //only middle is separated
    st.clear();
    for(int i=1;i<=n;i++)
    {
        for(auto x:rG[i]) st.insert(x);
        if(!st.size()||*(--st.end())<=i) {save[i]=-1; continue;}
        auto it=st.lower_bound(i+1);
        save[i]=*it-1;
    }
    seg.build(1,1,n);
    for(int i=n;i>=1;i--)
    {
        if(rightmost[i]>i)
        {
            val[i]=seg.query(1,1,n,i+1,rightmost[i]);
            seg.update(1,1,n,i,val[i]);
        }
        else val[i]=i;
    }
    for(int i=1;i<=n;i++) if(val[i]==n) dp[0][i]=n; else dp[0][i]=(val[val[i]+1]);
    for(int k=0;k<18;k++)
    {
        for(int i=1;i<=n;i++)
        {
            if(dp[k][i]==n) dp[k+1][i]=n;
            else dp[k+1][i]=dp[k][dp[k][i]];
        }
    }
    for(int i=2;i<=n;i++)
    {
        if(save[i-1]==-1) continue;
        int last=save[i-1];
        int pos=(i+n/2-1);
        int x=solve1(val[i],min(last,pos));
        if(x>=i&&x<=last) ans=max(ans,1LL*(x-i+1)*(n-(x-i+1)));
        x=dp[0][x];
        if(x>=i&&x<=last) ans=max(ans,1LL*(x-i+1)*(n-(x-i+1)));
    }
    printf("%lld\n",2LL*ans);
    return 0;
}
