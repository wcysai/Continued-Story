#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 18
#define MAXC 25
#define MAXM (1<<20)
#define INF 1000000000
#define MOD 1000000007
#define REV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,c;
vector<int> G[MAXN];
int p[MAXC];
int val[MAXM];
int cnt[MAXM];
int color[MAXN],save[MAXN];
void FWT(int a[],int n)    
{    
    for(int d=1;d<n;d<<=1)    
        for(int m=d<<1,i=0;i<n;i+=m)    
            for(int j=0;j<d;j++)    
            {    
                int x=a[i+j],y=a[i+j+d];    
                //xor:
                a[i+j]=(x+y)%MOD,a[i+j+d]=(x-y+MOD)%MOD;     
                //and:a[i+j]=x+y;    
                //or:a[i+j+d]=x+y;    
            }    
}    
    
void UFWT(int a[],int n)    
{    
    for(int d=1;d<n;d<<=1)    
        for(int m=d<<1,i=0;i<n;i+=m)    
            for(int j=0;j<d;j++)    
            {    
                int x=a[i+j],y=a[i+j+d];    
                //xor:
                a[i+j]=1LL*(x+y)*REV%MOD,a[i+j+d]=(1LL*(x-y)*REV%MOD+MOD)%MOD;      
                //and:a[i+j]=x-y;    
                //or:a[i+j+d]=y-x;    
            }    
}    
void solve(int a[],int b[],int n)    
{    
    FWT(a,n);    
    FWT(b,n);    
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%MOD;    
    UFWT(a,n);    
}   
int pa[MAXLOGN][MAXN],st[MAXN],ed[MAXN];
int tot,depth[MAXN];
int mask[MAXN];
void dfs(int v,int p,int d)
{
    st[v]=++tot; save[tot]=v;
    mask[v]^=(1<<color[v]); 
    pa[0][v]=p;
    depth[v]=d;
    for(int i=0;i<(int)G[v].size();i++)
        if(G[v][i]!=p) 
        {
            mask[G[v][i]]=mask[v];
            dfs(G[v][i],v,d+1);
        }
    ed[v]=tot;
}
void init(int V)
{
    dfs(1,-1,0);
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=V;v++)
        {
            if(pa[k][v]<0) pa[k+1][v]=-1;
            else pa[k+1][v]=pa[k][pa[k][v]];
        }
    }
}
int get(int v,int x)
{
    for(int k=0;k<MAXLOGN;k++)
        if((x>>k)&1)
            v=pa[k][v];
    return v;
}
int lca(int u,int v)
{
    if(depth[u]>depth[v]) swap(u,v);
    v=get(v,depth[v]-depth[u]);
    if(u==v) return u;
    for(int k=MAXLOGN-1;k>=0;k--)
    {
        if(pa[k][u]!=pa[k][v])
        {
            u=pa[k][u];
            v=pa[k][v];
        }
    }
    return pa[0][u];
}
struct segtree
{
    int val[4*MAXN],lazy[4*MAXN];
    void pushdown(int k)
    {
        for(int i=k*2;i<=k*2+1;i++)
        {
            val[i]^=lazy[k];
            lazy[i]^=lazy[k];
        }
        lazy[k]=0;
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            val[k]=mask[save[l]];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int x,int y,int p)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            val[k]^=p;
            lazy[k]^=p;
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,p); update(k*2+1,mid+1,r,x,y,p);
    }
    int query(int k,int l,int r,int pos)
    {
        if(l==r) return val[k];
        pushdown(k);
        int mid=(l+r)/2;
        if(pos<=mid) return query(k*2,l,mid,pos); else return query(k*2+1,mid+1,r,pos);
    }
}seg;
int main()
{
    scanf("%d%d%d",&m,&c,&n);
    for(int i=0;i<=c-1;i++) scanf("%d",&p[i]);
    for(int i=0;i<(1<<c);i++)
    {
        for(int j=0;j<c;j++)
            if(i&(1<<j)) val[i]=__gcd(val[i],p[j]);
    }
    for(int i=0;i<m;i++)
    {
        int mask=0,x;
        scanf("%d",&x);
        for(int j=0;j<x;j++)
        {
            int y;
            scanf("%d",&y);
            mask^=(1<<y);
        }
        cnt[mask]++;
    }
    solve(val,cnt,(1<<c));
    for(int i=1;i<=n;i++) scanf("%d",&color[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        u++; v++;
        G[u].push_back(v); G[v].push_back(u);
    }
    init(n);
    seg.build(1,1,n);
    int mm=0;
    for(int i=0;i<m;i++)
    {
        int u,v,w,y;
        scanf("%d%d%d%d",&u,&v,&w,&y); u++; v++; w++;
        int l=lca(u,v);
        int res=seg.query(1,1,n,st[u]);
        res^=seg.query(1,1,n,st[v]);
        res^=seg.query(1,1,n,st[l]);
        if(l!=1) res^=seg.query(1,1,n,st[pa[0][l]]);
        mm^=res;
        printf("%d ",val[mm]);
        int tmp=(1<<color[w])^(1<<y);
        color[w]=y;
        seg.update(1,1,n,st[w],ed[w],tmp);
    }
    return 0;
}