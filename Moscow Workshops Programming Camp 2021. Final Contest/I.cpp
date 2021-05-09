#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
typedef long long ll;
struct node
{
	int ch[2],key,size;
	ll val,minv,addv;
};
node t[maxn];
int root[6];
void init(int n)
{
	for(int i=0;i<6;++i)root[i]=0;
	for(int i=1;i<=n;++i)t[i].ch[0]=t[i].ch[1]=t[i].key=t[i].size=t[i].val=t[i].minv=0;
}
void pushup(int rt)
{
	int lc=t[rt].ch[0],rc=t[rt].ch[1];
	t[rt].size=t[lc].size+t[rc].size+1;
	t[rt].minv=t[rt].val;
	if(lc)t[rt].minv=min(t[rt].minv,t[lc].minv);
	if(rc)t[rt].minv=min(t[rt].minv,t[rc].minv);
}
void pushdown(int rt)
{
	if(t[rt].addv)
	{
		ll tag=t[rt].addv;
		int lc=t[rt].ch[0],rc=t[rt].ch[1];
		if(lc){t[lc].minv+=tag;t[lc].val+=tag;t[lc].addv+=tag;}
		if(rc){t[rc].minv+=tag;t[rc].val+=tag;t[rc].addv+=tag;}
		t[rt].addv=0;
	}
}
int merge(int x,int y)
{
	if(x)pushdown(x);
	if(y)pushdown(y);
	if(!x||!y)return x+y;
	if(t[x].key>t[y].key)
	{
		t[x].ch[1]=merge(t[x].ch[1],y);
		pushup(x);
		return x;
	}
	else
	{
		t[y].ch[0]=merge(x,t[y].ch[0]);
		pushup(y);
		return y;
	}
}
void split(int rt,int k,int &x,int &y)
{
	if(!rt)
	{
		x=y=0;
		return;
	}
	pushdown(rt);
	if(t[t[rt].ch[0]].size+1<=k)
	{
		x=rt;
		split(t[rt].ch[1],k-t[t[rt].ch[0]].size-1,t[rt].ch[1],y);
	}
	else
	{
		y=rt;
		split(t[rt].ch[0],k,x,t[rt].ch[0]);
	}
	pushup(rt); 
}
int n,q;
int tc[maxn];
void add(int x,int v)
{
	for(;x<=n;x+=x&(-x))tc[x]+=v;
}
int query(int x)
{
	int ans=0;
	for(;x;x-=x&(-x))ans+=tc[x];
	return ans;
}
int main()
{
	srand(time(NULL)); 
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)add(i,1);
	for(int i=1;i<=n;++i)
	{
		t[i].key=rand();
		t[i].val=0;
		pushup(i);
		root[i%6]=merge(root[i%6],i);
	}
	while(q--)
	{
		char opt[15];
		int l,r,k,x;
		scanf("%s",opt);
		if(opt[0]=='c')
		{
			scanf("%d%d%d%d",&l,&r,&k,&x);
			for(int i=1;i<=6;++i)if(i%k==l%k)
			{
				int L=(l-1)/6+1;while((L-1)*6+i<l)L++;
				int R=(r-1)/6+1;while((R-1)*6+i>r)R--;
				if(L<=R)
				{
					int u,v,w;
					split(root[i%6],R,root[i%6],v);
					split(root[i%6],L-1,root[i%6],u);
					t[u].addv+=1ll*x;t[u].val+=1ll*x;t[u].minv+=1ll*x;
					root[i%6]=merge(root[i%6],u);
					root[i%6]=merge(root[i%6],v);
				}
			}
		}
		else if(opt[0]=='g')
		{
			ll ans=(ll)1e18;
			scanf("%d%d%d",&l,&r,&k);
			for(int i=1;i<=6;++i)if(i%k==l%k)
			{
				int L=(l-1)/6+1;while((L-1)*6+i<l)L++;
				int R=(r-1)/6+1;while((R-1)*6+i>r)R--;
				if(L<=R)
				{
					int u,v,w;
					split(root[i%6],R,root[i%6],v);
					split(root[i%6],L-1,root[i%6],u);
					ans=min(ans,t[u].minv);
					root[i%6]=merge(root[i%6],u);
					root[i%6]=merge(root[i%6],v);
				}
			}
			printf("%lld\n",ans);
		}
		else if(opt[0]=='k')
		{
			int tmp[6];
			memset(tmp,0,sizeof(tmp));
			scanf("%d",&l);
			for(int i=1;i<=6;++i)
			{
				int L=(l-1)/6+1;
				if((L-1)*6+i==l)
				{
					int u;
					split(root[i%6],L-1,root[i%6],u);
					split(u,1,u,tmp[i%6]);
					add(u,-1);
				}
				else
				{
					while((L-1)*6+i<l)L++;
					split(root[i%6],L-1,root[i%6],tmp[i%6]);
				}
			}
			for(int i=0;i<6;++i)root[i]=merge(root[i],tmp[(i+1)%6]);
		}
		else if(opt[0]=='r')
		{
			int d,tmp[6];
			memset(tmp,0,sizeof(tmp));
			scanf("%d",&d);
			int k=query(d)+1;
			for(int i=1;i<=6;++i)
			{
				int L=(k-1)/6+1;
				while((L-1)*6+i<k)L++;
				split(root[i%6],L-1,root[i%6],tmp[i%6]);
			}
			for(int i=0;i<6;++i)
			{
				if(k%6==i)
				{
					t[d].val=t[d].addv=0;
					pushup(d);
					root[i]=merge(root[i],d);
					root[i]=merge(root[i],tmp[(i+5)%6]);
				}
				else
				{
					root[i]=merge(root[i],tmp[(i+5)%6]);
				}
			}
			add(d,1);
		}
	}
}