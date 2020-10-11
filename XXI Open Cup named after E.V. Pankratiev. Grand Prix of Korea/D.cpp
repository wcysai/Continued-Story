#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN];
int n,m,p[MAXN],r[MAXN],sz[MAXN];
ll cnt=0;
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        r[i]=0;
		sz[i]=1;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) {p[x]=y; sz[y]+=sz[x];}
    else
    {
        p[y]=x;
        if(r[x]==r[y]) r[x]++;
		sz[x]+=sz[y];
    }
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
struct edge
{
	int u,v,d;
};
bool cmp(edge x,edge y)
{
	return x.d>y.d;
}
vector<edge> ve;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		ve.push_back((edge){u,v,d});
	}
	sort(ve.begin(),ve.end(),cmp);
	vector<edge> tmp;
	bool f=true;
	init(n);
	ll ans=0;
	for(int i=0;i<(int)ve.size();i++)
	{
		if(i!=0&&ve[i].d!=ve[i-1].d)
		{
			for(auto e:tmp)
			{
				int u=find(e.u),v=find(e.v);
				if(same(u,v)) continue;
				ans+=1LL*sz[u]*sz[v]*e.d;
				cnt+=1LL*sz[u]*sz[v];
				unite(u,v);
			}
			tmp.clear();
		}
		if(same(ve[i].u,ve[i].v)) {f=false; break;}
		tmp.push_back(ve[i]);
	}
	for(auto e:tmp)
	{
		int u=find(e.u),v=find(e.v);
		if(same(u,v)) continue;
		ans+=1LL*sz[u]*sz[v]*e.d;
		cnt+=1LL*sz[u]*sz[v];
		unite(u,v);
	}
	if(!f) puts("-1");
	else printf("%lld\n",ans+1LL*n*(n-1)/2-cnt);
	return 0;
}