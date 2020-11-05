#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
struct segtree
{
    int mini[4*MAXN],lazy[4*MAXN];
    void pushup(int k)
    {
        mini[k]=min(mini[k*2],mini[k*2+1]);
    }
    void add(int k,int v)
    {
        mini[k]+=v;
        lazy[k]+=v;
    }
    void pushdown(int k)
    {
        if(!lazy[k]) return;
        for(int i=k*2;i<=k*2+1;i++) add(i,lazy[k]);
        lazy[k]=0; 
    }
    void update(int k,int l,int r,int x,int y,int v)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y) 
        {
            add(k,v);
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return INF;
        if(l>=x&&r<=y) return mini[k];
        pushdown(k);
        int mid=(l+r)/2;
        return min(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
vector<int> dis;
vector<P> save[MAXN];
vector<P> op;
vector<P> v;
bool cmp(P x,P y)
{
    if(x.S!=y.S) return x.S<y.S;
    return x.F>y.F;
}
vector<int> st;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d",&a[i],&b[i]);
        dis.push_back(b[i]);
        save[a[i]].push_back(P(b[i],-1));
        op.push_back(P(b[i],-1));
    }
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d",&c[i],&d[i]);
        dis.push_back(d[i]);
        save[c[i]].push_back(P(d[i],1));
        op.push_back(P(d[i],1));
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    int sz=(int)dis.size();
    sort(op.begin(),op.end());
    for(int i=1;i<=n;i++) sort(save[i].begin(),save[i].end());
    for(auto p:op)
    {
        int id=lower_bound(dis.begin(),dis.end(),p.F)-dis.begin()+1;
        seg.update(1,1,sz,id,sz,-p.S);
    }
    for(int i=1;i<=n;i++)
    {
        st.clear();
        for(auto p:save[i])
        {
             int id=lower_bound(dis.begin(),dis.end(),p.F)-dis.begin()+1;
             if(p.S==-1) st.push_back(id);
             else
             {
                 if(st.size())
                 {
                    int val=st.back(); st.pop_back();
                    v.push_back(P(val,id-1));
                 }
             }
        }
    }
    sort(v.begin(),v.end(),cmp);
    int ans=n;
    for(auto p:v)
    {
        if(seg.query(1,1,sz,p.F,p.S)>0)
        {
            seg.update(1,1,sz,p.F,p.S,-1);
            ans--;
        }
    }
    printf("%d\n",ans);
    return 0;
}