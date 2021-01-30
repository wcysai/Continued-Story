#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
typedef long long ll;
int n,m,d;
int block;
ll a[maxn],b[maxn];
int id[maxn];
struct Query
{
    int l,r,id;
    Query(int l=0,int r=0,int id=0):l(l),r(r),id(id){}
}q[maxn];
bool operator < (Query a,Query b)
{
    if(id[a.l]==id[b.l])
    {
        if(id[a.l]&1)return a.r<b.r;
        else return a.r>b.r;
    }
    return id[a.l]<id[b.l];
}
const ll mod = 1000000007;
ll Ans[maxn];
ll num[maxn<<2],osum[maxn<<2],esum[maxn<<2];
void pushup(int rt)
{
	num[rt]=num[rt<<1]+num[rt<<1|1];
	if(num[rt<<1]&1)
	{
		osum[rt]=osum[rt<<1]+esum[rt<<1|1];
		esum[rt]=esum[rt<<1]+osum[rt<<1|1];
	}
	else
	{
		osum[rt]=osum[rt<<1]+osum[rt<<1|1];
		esum[rt]=esum[rt<<1]+esum[rt<<1|1];
	}
}
void add(int rt,int l,int r,int pos,int v)
{
	if(l==r)
	{
		osum[rt]+=b[l]*v;esum[rt]=0;num[rt]+=v;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)add(rt<<1,l,mid,pos,v);
	else add(rt<<1|1,mid+1,r,pos,v);
	pushup(rt);
}
void add(int x)
{
	add(1,1,d,x,1);
}
void del(int x)
{
	add(1,1,d,x,-1);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%lld",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	d=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+d+1,a[i])-b;
	/*for(int i=1;i<=n;++i)cerr<<a[i]<<" ";
	cerr<<endl;*/
	block=sqrt(n);
	for(int i=1;i<=n;++i)id[i]=(i-1)/block+1;
	for(int i=1;i<=m;++i)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		++l;++r;
		q[i]=Query(l,r,i);
	}
	sort(q+1,q+m+1);
	int l=1,r=0;
    for(int i=1;i<=m;++i)
    {
        while(r<q[i].r)++r,add(a[r]);
        while(r>q[i].r)del(a[r]),--r; 
        while(l>q[i].l)--l,add(a[l]);
        while(l<q[i].l)del(a[l]),++l;
        //cerr<<l<<" "<<r<<endl;
        Ans[q[i].id]=osum[1]%mod;
    }
    for(int i=1;i<=m;++i)printf("%lld\n",Ans[i]);
}