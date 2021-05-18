#include<bits/stdc++.h>
#define MAXN 1000005
#define MAXM 60000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,tot,cnt,a[MAXN],root[MAXN];
int lson[MAXM],rson[MAXM];
ll sum[MAXM];
void pushup(int k)
{
    sum[k]=sum[lson[k]]+sum[rson[k]];
}
void build(int &k,int l,int r)
{
    k=++tot;
    if(l==r)
    {
        sum[k]=0;
        return;
    }
    int mid=(l+r)/2;
    build(lson[k],l,mid); build(rson[k],mid+1,r);
    pushup(k);
}
void update(int &k,int last,int l,int r,int p,int v)
{
    k=++tot;
    sum[k]=sum[last];
    if(l==r)
    {
        sum[k]+=v;
        return;
    }
    lson[k]=lson[last]; rson[k]=rson[last];
    int mid=(l+r)/2;
    if(p<=mid) update(lson[k],lson[last],l,mid,p,v);
    else update(rson[k],rson[last],mid+1,r,p,v);
    pushup(k);
}
int query(int k,int last,int l,int r,ll s)
{
    if(!k) assert(0);
    if(l==r) return l;
    int mid=(l+r)/2;
    if(sum[lson[k]]-sum[lson[last]]>=s) return query(lson[k],lson[last],l,mid,s); else return query(rson[k],rson[last],mid+1,r,s-(sum[lson[k]]-sum[lson[last]]));
}
ll query_sum(int k,int last,int l,int r,int x,int y)
{
    if(!k) return 0;
    if(l>y||x>r) return 0;
    if(l>=x&&r<=y) return sum[k]-sum[last];
    int mid=(l+r)/2;
    return query_sum(lson[k],lson[last],l,mid,x,y)+query_sum(rson[k],rson[last],mid+1,r,x,y);
}
vector<int> dis;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        dis.push_back(a[i]);
    }
    cnt=0;
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    int sz=(int)dis.size();
    build(root[0],1,sz);
    for(int i=1;i<=n;i++)
    {
        int id=lower_bound(dis.begin(),dis.end(),a[i])-dis.begin()+1;
        update(root[cnt+1],root[cnt],1,sz,id,a[i]);
        cnt++;
    }
    ll ans=0;
    for(int i=0;i<q;i++)
    {
        int l,r,tl,tr;
        scanf("%d%d",&tl,&tr);
        l=min((tl+ans)%n+1,(tr+ans)%n+1);
        r=max((tl+ans)%n+1,(tr+ans)%n+1);
        ll cur=1;
        ans=-1;
        while(cur<=1000000000000000LL)//find minimum in the range[ 2^k,2^(k+1) )
        {
            int id=query(root[r],root[l-1],1,sz,cur);
            ll x=query_sum(root[r],root[l-1],1,sz,1,id-1),y=x+dis[id-1];
            if(2*x+1<y)
            {
                ans=x+1;
                break;
            }
            cur<<=1;
        }
        if(ans==-1) ans=query_sum(root[r],root[l-1],1,sz,1,sz)+1;
        printf("%lld\n",ans);
    }
    return 0;
}