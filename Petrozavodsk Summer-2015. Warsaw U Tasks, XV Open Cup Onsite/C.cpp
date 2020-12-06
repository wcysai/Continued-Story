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
int n,a,b,p,m,Q,k,ans;
pair<int,int> q[6000010];
void add(int x,int y){
	x=(x%n+n)%n;
	y=(y%n+n)%n;
	if(x<y)q[++Q]=mp(x,1),q[++Q]=mp(y,-1);
	else{
		q[++Q]=mp(x,1),q[++Q]=mp(n,-1);
		q[++Q]=mp(0,1),q[++Q]=mp(y,-1);
	}
}
int main(){
	scanf("%d%d%d%d%d",&n,&a,&b,&p,&m);
	for(int i=0;i<m;++i){
		int x;
		scanf("%1d",&x);
		int I=i*1ll*a%n;
		if(!x)add(-b-I,p-b-I);
		else add(p-b-I,-b-I);
	}
	for(int i=n-m+1;i<n;++i){
		int x=i*1ll*a%n;
		q[++Q]=mp(x,-1);
		q[++Q]=mp(x+1,1);
	}
	sort(q+1,q+Q+1);
	for(int i=1;i<=Q;++i){
		if(q[i].second==-1){
			if(k==m)ans+=q[i].first;
			--k;
		}
		else{
			++k;
			if(k==m)ans-=q[i].first;
		}
	}
	printf("%d\n",ans);
    return 0;
}
