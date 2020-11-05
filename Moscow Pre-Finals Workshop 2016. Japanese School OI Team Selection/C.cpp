#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,sz;
int a[MAXN];
struct segtree
{
    int maxi[4*MAXN],lazy[4*MAXN];
    void pushup(int k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void add(int k,int v)
    {
        maxi[k]+=v;
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
    int query(int k,int l,int r,int p)
    {
        if(l==r) return maxi[k];
        pushdown(k);
        int mid=(l+r)/2;
        if(p<=mid) return query(k*2,l,mid,p); else return query(k*2+1,mid+1,r,p);
    }
}seg;
struct node
{
    int type;
    int x,y;
};
vector<int> dis;
vector<node> query;
void check(int pos,int delta)
{
    int val=lower_bound(dis.begin(),dis.end(),a[pos])-dis.begin()+1;
    if(pos==1) seg.update(1,1,sz,1,val,delta);
    else
    {
        int pre=lower_bound(dis.begin(),dis.end(),a[pos-1])-dis.begin()+1;
        if(pre<val) seg.update(1,1,sz,pre+1,val,delta);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        dis.push_back(a[i]);
    }
    for(int i=0;i<m;i++)
    {
        int type,x,y;
        scanf("%d%d",&type,&x);
        if(type==1) 
        {
            query.push_back((node){type,x,0});
            dis.push_back(x);
        } 
        else
        {
            scanf("%d",&y);
            query.push_back((node){type,x,y});
            dis.push_back(y);
        }
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    sz=(int)dis.size();
    for(int i=1;i<=n;i++) check(i,1);
    for(auto p:query)
    {
        if(p.type==1)
        {
            int val=lower_bound(dis.begin(),dis.end(),p.x)-dis.begin()+1;
            printf("%d\n",seg.query(1,1,sz,val)); 
        }
        else
        {
            int pos=p.x,val=p.y;
            check(pos,-1); if(pos<n) check(pos+1,-1);
            a[pos]=val;
            check(pos,1); if(pos<n) check(pos+1,1);
        }
    }
    return 0;
}