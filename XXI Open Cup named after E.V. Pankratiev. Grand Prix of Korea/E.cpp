#include<bits/stdc++.h>
#define maxn 250005 
using namespace std;
int n,m;
struct Link_Cut_Tree
{
	int ch[maxn][2],fa[maxn],rev[maxn],val[maxn],minv[maxn],stk[maxn],top;
	bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	void pushup(int x)
	{
		minv[x]=val[x];
		if(ch[x][0])minv[x]=min(minv[x],minv[ch[x][0]]);
		if(ch[x][1])minv[x]=min(minv[x],minv[ch[x][1]]);
	}
	void pushdown(int x)
	{
		if(!rev[x])return;
		swap(ch[x][0],ch[x][1]);
		rev[ch[x][0]]^=1,rev[ch[x][1]]^=1;rev[x]=0;
	}
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],kind;
		if(ch[y][0]==x)kind=1;else kind=0;
		if(!isroot(y)){if(ch[z][0]==y)ch[z][0]=x;else ch[z][1]=x;}
		ch[y][kind^1]=ch[x][kind];fa[ch[y][kind^1]]=y;ch[x][kind]=y;
		fa[y]=x;fa[x]=z;pushup(y);pushup(x);
	}
	void splay(int x)
	{
		stk[top=1]=x;for(int i=x;!isroot(i);i=fa[i])stk[++top]=fa[i];
		for(int i=top;i;--i)pushdown(stk[i]);
		while(!isroot(x))
		{
			int y=fa[x],z=fa[y];
			if(!isroot(y)){if(ch[z][0]==y^ch[y][0]==x)rotate(x);else rotate(y);}
			rotate(x);
		}
	}
	void access(int x){for(int c=0;x;c=x,x=fa[x])splay(x),ch[x][1]=c,pushup(x);}
	void makeroot(int x){access(x);splay(x);rev[x]^=1;}
	int find(int x){access(x);splay(x);while(ch[x][0])x=ch[x][0];return x;}
	bool same(int x,int y){return find(x)==find(y);}
	void link(int x,int y){makeroot(x);fa[x]=y;splay(x);}
	void cut(int x,int y){makeroot(x);makeroot(y);if(ch[y][0]==x&&fa[x]==y)ch[y][0]=fa[x]=0;}
	void change(int x,int y){makeroot(x);val[x]=y;pushup(x);}
	int query(int x,int y){makeroot(x);makeroot(y);return minv[y];}
}lct;
vector<int> g1[maxn],g2[maxn];
int L[maxn],d[maxn];
int maxv[maxn<<2],num[maxn<<2],addv[maxn<<2];
void pushup(int rt)
{
	maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
	num[rt]=0;
	if(maxv[rt]==maxv[rt<<1])num[rt]+=num[rt<<1];
	if(maxv[rt]==maxv[rt<<1|1])num[rt]+=num[rt<<1|1];
}
void pushdown(int rt)
{
	if(addv[rt])
	{
		int t=addv[rt];
		maxv[rt<<1]+=t;maxv[rt<<1|1]+=t;
		addv[rt<<1]+=t;addv[rt<<1|1]+=t;
		addv[rt]=0;
	}
}
void build(int rt,int l,int r)
{
	if(l==r)
	{
		maxv[rt]=l;num[rt]=1;
		return;
	}
	addv[rt]=0;
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);build(rt<<1|1,mid+1,r);
	pushup(rt);
}
void add(int rt,int l,int r,int ql,int qr,int v)
{
	if(ql<=l&&r<=qr)
	{
		maxv[rt]+=v;addv[rt]+=v;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(ql<=mid)add(rt<<1,l,mid,ql,qr,v);
	if(qr>mid)add(rt<<1|1,mid+1,r,ql,qr,v);
	pushup(rt);
}
pair<int,int> query(int rt,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)
	{
		return make_pair(maxv[rt],num[rt]);
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(qr<=mid)return query(rt<<1,l,mid,ql,qr);
	else if(ql>mid)return query(rt<<1|1,mid+1,r,ql,qr);
	else
	{
		pair<int,int> A=query(rt<<1,l,mid,ql,qr),B=query(rt<<1|1,mid+1,r,ql,qr);
		pushup(rt);
		int x=A.first,y=B.first,nx=A.second,ny=B.second;
		if(x==y)return make_pair(x,nx+ny);
		else if(x>y)return A;
		else return B;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(u>v)swap(u,v);
		g1[u].push_back(v);
		g2[v].push_back(u);
	}
	for(int i=1;i<=n;++i)lct.change(i,i);
	int l=1;
	for(int r=1;r<=n;++r)
	{
		sort(g2[r].begin(),g2[r].end());
		for(int x:g2[r])if(x>=l)
		{
			if(!lct.same(x,r))
			{
				lct.link(x,r);
				continue;
			}
			int last=l,t=lct.query(x,r);
			l=t+1;
			for(int i=last;i<l;++i)
				for(int y:g1[i])if(y<=r)lct.cut(i,y);
			if(x!=t)lct.link(x,r);
		}
		L[r]=l;
		//cerr<<L[r]<<" "<<r<<endl;
	}
	l=1;
	for(int r=1;r<=n;++r)
	{
		for(int x:g2[r])if(x>=l)
		{
			d[x]++;d[r]++;
			while(1)
			{
				if(d[x]<=2&&d[r]<=2)break;
				for(int y:g1[l])if(y<=r)d[y]--,d[l]--;
				l++;
			}
		}
		L[r]=max(L[r],l);
	}
	build(1,1,n);
	long long ans=0;
	for(int i=1;i<=n;++i)
	{
		for(int x:g2[i])add(1,1,n,1,x,1);
		pair<int,int> A=query(1,1,n,L[i],i);
		if(A.first==i)ans+=1ll*A.second;
	}
	cout<<ans<<endl;
}