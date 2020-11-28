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
int ax[505],ay[505],bx[505],by[505];
int n,m,f[505][505],lx[505],ly[505],vx[505],vy[505],sl[505];
int q[505],ql,qr,pre[505],ml[505],mr[505],out[505];
void go(int x){
    while(1){
        ql=0,qr=1,vx[x]=1,q[1]=x;
        while(ql<qr){
            int o=q[++ql];
            for(int i=1;i<=n;++i){
                if(vy[i]) continue;
                int t=lx[o]+ly[i]-f[o][i];
                if(t>sl[i]) continue;
                pre[i]=o;
                if(!t){
                    if(!ml[i]){
                        while(i){
                            ml[i]=pre[i];
                            swap(i,mr[pre[i]]);
                        }
                        return;
                    }
                    q[++qr]=ml[i];
                    vy[i]=vx[ml[i]]=1;
                }
                else sl[i]=t;
            }
        }
        int o,O=orz;
        for(int i=1;i<=n;++i)if(!vy[i]&&O>sl[i])o=i,O=sl[i];
        for(int i=1;i<=n;++i){
            if(vx[i])lx[i]-=O;
            if(vy[i])ly[i]+=O;
            else sl[i]-=O;
        }
        if(!ml[o]){
            while(o){
                ml[o]=pre[o];
                swap(o,mr[pre[o]]);
            }
            return;
        }
        vy[o]=1,x=ml[o];
    }
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d",ax+i,ay+i);
	for(int i=1;i<=n;++i)scanf("%d%d",bx+i,by+i);
    for(int i=1;i<=n;++i){
    	for(int j=1;j<=n;++j){
	        f[i][j]=ax[i]*bx[j]+ay[i]*by[j]+orz/2;
	        lx[i]=max(lx[i],f[i][j]);
    	}
    }
    for(int i=1;i<=n;++i){
        memset(vx,0,sizeof(vx));
        memset(vy,0,sizeof(vy));
        for(int j=1;j<=n;++j)sl[j]=orz;
        go(i);
    }
    printf("Yes\n");
    for(int i=1;i<=n;++i)out[i]=f[i][mr[i]]?mr[i]:0;
    for(int i=1;i<n;++i)printf("%d ",out[i]);
    printf("%d\n",out[n]);
	//system("pause");
	return 0;
}
