//Relive your past life.
//Face your demons.
//The past is never dead,it is not even past.
//The memories are not only the key to the past but...also to the future.
//coded in Rusty Lake
#include<cmath>
#include<math.h>
#include<ctype.h>
#include<algorithm>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cerrno>
#include<cfloat>
#include<ciso646>
#include<climits>
#include<clocale>
#include<complex>
#include<csetjmp>
#include<csignal>
#include<cstdarg>
#include<cstddef>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cwchar>
#include<cwctype>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<typeinfo>
#include<utility>
#include<valarray>
#include<vector>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,fa[500005],f[500005],g[500005],uf[500005],ug[500005];
int d[500005],la[500005];
int Q[500005],qr;
int mn,Mn,mx,Mx,bx,by;
vector<int> v[500005];
void ope(int x,int y){
	fa[x]=y;
	int p=0,q=0;
	for(int i=0;i<v[x].size();++i){
		int z=v[x][i];
		if(z==y) continue;
		ope(z,x);
		if(f[z]>f[x])f[x]=f[z];
		if(g[z]>p)q=p,p=g[z];
		else if(g[z]>q)q=g[z];
	}
	g[x]=p+1;
	f[x]=max(f[x],p+q+1);
}
void dfs(int x,int y){
	int p=ug[x],q=0,r=0;
	int P=uf[x],Q=0;
	for(int i=0;i<v[x].size();++i){
		int z=v[x][i];
		if(y==z) continue;
		if(f[z]>P)Q=P,P=f[z];
		else if(f[z]>Q)Q=f[z];
		if(g[z]>p)r=q,q=p,p=g[z];
		else if(g[z]>q)r=q,q=g[z];
		else if(g[z]>r)r=g[z];
	}
	for(int i=0;i<v[x].size();++i){
		int z=v[x][i];
		if(y==z) continue;
		if(g[z]==p)uf[z]=q+r+1,ug[z]=q+1;
		else if(g[z]==q)uf[z]=p+r+1,ug[z]=p+1;
		else uf[z]=p+q+1,ug[z]=p+1;
		if(f[z]==P)uf[z]=max(uf[z],Q);
		else uf[z]=max(uf[z],P);
		dfs(z,x);
	}
}
void sol(int x){
	memset(d,-1,sizeof(d));
	qr=1;
	d[x]=0;
	Q[1]=x;
	for(int ql=1;ql<=qr;++ql){
		int x=Q[ql];
		for(int i=0;i<v[x].size();++i){
			int y=v[x][i];
			if(y==by) continue;
			if(d[y]==-1)d[y]=d[x]+1,Q[++qr]=y,la[y]=x;
		}
	}
	int k=Q[qr];
	while(d[k]!=d[Q[qr]]/2)k=la[k];
	printf(" %d",k);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].pb(y);
		v[y].pb(x);
	}
	ope(1,0);
	dfs(1,0);
	mn=orz;
	mx=-orz;
	for(int i=2;i<=n;++i){
		int x=uf[i],y=f[i];
		if(x+y-1>mx)mx=x+y-1,Mx=i;
		if(max(x/2+y/2+1,max(x,y)-1)<mn)mn=max(x/2+y/2+1,max(x,y)-1),Mn=i;
	}
	bx=fa[Mn],by=Mn;
	printf("%d %d %d",mn,bx,by);
	memset(d,-1,sizeof(d));
	d[bx]=0;
	qr=1;
	Q[1]=bx;
	for(int ql=1;ql<=qr;++ql){
		int x=Q[ql];
		for(int i=0;i<v[x].size();++i){
			int y=v[x][i];
			if(y==by) continue;
			if(d[y]==-1)d[y]=d[x]+1,Q[++qr]=y;
		}
	}
	sol(Q[qr]);
	swap(bx,by);
	memset(d,-1,sizeof(d));
	d[bx]=0;
	qr=1;
	Q[1]=bx;
	for(int ql=1;ql<=qr;++ql){
		int x=Q[ql];
		for(int i=0;i<v[x].size();++i){
			int y=v[x][i];
			if(y==by) continue;
			if(d[y]==-1)d[y]=d[x]+1,Q[++qr]=y;
		}
	}
	sol(Q[qr]);
	printf("\n");
	bx=fa[Mx],by=Mx;
	printf("%d %d %d",mx,bx,by);
	memset(d,-1,sizeof(d));
	d[bx]=0;
	qr=1;
	Q[1]=bx;
	for(int ql=1;ql<=qr;++ql){
		int x=Q[ql];
		for(int i=0;i<v[x].size();++i){
			int y=v[x][i];
			if(y==by) continue;
			if(d[y]==-1)d[y]=d[x]+1,Q[++qr]=y;
		}
	}
	printf(" %d",Q[qr]);
	swap(bx,by);
	memset(d,-1,sizeof(d));
	d[bx]=0;
	qr=1;
	Q[1]=bx;
	for(int ql=1;ql<=qr;++ql){
		int x=Q[ql];
		for(int i=0;i<v[x].size();++i){
			int y=v[x][i];
			if(y==by) continue;
			if(d[y]==-1)d[y]=d[x]+1,Q[++qr]=y;
		}
	}
	printf(" %d",Q[qr]);
	printf("\n");
    return 0;
}
