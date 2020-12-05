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
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,a[1000005],ans[1000005],r[1000005],q[1000005],qr;
bool b[1000005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i),a[i]*=2;
	for(int i=1;i<n;++i)r[i]=i+1;
	r[n]=1;
	for(int x=1;x<=n;++x){
		int L=b[x]?a[x]:a[x]/2;
		int R=b[r[x]]?a[r[x]]:a[r[x]]/2;
		if(L>=a[r[x]]){
			ans[x]=x;
			if(!b[x])a[x]/=2;
			b[x]=b[r[x]]=1;
			q[++qr]=x;
		}
		else if(R>=a[x]){
			ans[x]=r[x];
			if(!b[r[x]])a[r[x]]/=2;
			b[x]=b[r[x]]=1;
			q[++qr]=x;
		}
	}
	for(int ql=1;ql<=qr;++ql){
		int x=q[ql];
		--x;
		if(!x)x=n;
		if(!ans[x]){
			int L=b[x]?a[x]:a[x]/2;
			int R=b[r[x]]?a[r[x]]:a[r[x]]/2;
			if(L>=a[r[x]]){
				ans[x]=x;
				if(!b[x])a[x]/=2;
				b[x]=b[r[x]]=1;
				q[++qr]=x;
			}
			else if(R>=a[x]){
				ans[x]=r[x];
				if(!b[r[x]])a[r[x]]/=2;
				b[x]=b[r[x]]=1;
				q[++qr]=x;
			}
		}
		x=r[r[x]];
		if(!ans[x]){
			int L=b[x]?a[x]:a[x]/2;
			int R=b[r[x]]?a[r[x]]:a[r[x]]/2;
			if(L>=a[r[x]]){
				ans[x]=x;
				if(!b[x])a[x]/=2;
				b[x]=b[r[x]]=1;
				q[++qr]=x;
			}
			else if(R>=a[x]){
				ans[x]=r[x];
				if(!b[r[x]])a[r[x]]/=2;
				b[x]=b[r[x]]=1;
				q[++qr]=x;
			}
		}
	}
	for(int i=1;i<=n;++i)if(!ans[i])ans[i]=i;
	for(int i=1;i<n;++i)printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
    return 0;
}
