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
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,m,q,a[250005],b[250005],A[250005],B[250005],T[500005],TT,L,R,X;
ll c[250005],t[1000005],add[1000005];
void bld(int k,int l,int r){
	if(l==r){
		t[k]=c[l];
		return;
	}
	int m=(l+r)>>1,lc=k<<1,rc=lc^1;
	bld(lc,l,m),bld(rc,m+1,r);
	t[k]=min(t[lc],t[rc]);
}
void ins(int k,int l,int r){
	if(l>=L&&r<=R){
		add[k]+=X;
		return;
	}
	int m=(l+r)>>1,lc=k<<1,rc=lc^1;
	if(L<=m)ins(lc,l,m);
	if(R>m)ins(rc,m+1,r);
	t[k]=min(t[lc]+add[lc],t[rc]+add[rc]);
}
void ADD(int k,int x){
	if(!k){
		TT+=x;
		return;
	}
	while(k<=500000)T[k]+=x,k+=(k&-k);
}
int SUM(int k){
	if(k<0) return 0;
	int s=TT;
	while(k)s+=T[k],k-=(k&-k);
	return s;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",a+i),A[i]=a[i],ADD(a[i],1);
	for(int i=1;i<=m;++i)scanf("%d",b+i),B[i]=b[i];
	if(n<m)TT+=m-n;
	n=max(n,m);
	scanf("%d",&m);
	sort(A+1,A+n+1);
	sort(B+1,B+n+1);
	for(int i=1;i<=n;++i)c[i]=c[i-1]-A[n+1-i];
	int k=0;
	ll s=0;
	for(int i=1;i<=n;++i){
		while(k<n&&B[k+1]<i)s+=B[++k];
		c[i]+=s+(n-k)*1ll*i;
	}
	bld(1,1,n);
	while(m--){
		int ty,x;
		scanf("%d%d",&ty,&x);
		if(ty==1){
			L=n-SUM(a[x])+1,X=-1;
			ADD(a[x],-1);
			++a[x];
			ADD(a[x],1);
		}
		else if(ty==2){
			L=n-SUM(a[x]-1),X=1;
			ADD(a[x],-1);
			--a[x];
			ADD(a[x],1);
		}
		else if(ty==3){
			L=b[x]+1,X=1;
			++b[x];
		}
		else{
			L=b[x],X=-1;
			--b[x];
		}
		R=n;
		if(L<=R)ins(1,1,n);
		if(t[1]+add[1]>=0)printf("1\n");
		else printf("0\n");
	}
    return 0;
}