#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,t,p[22][5],a[1100],ans;
int main(){
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;++i)scanf("%d%d%d",p[i]+3,p[i]+2,p[i]+1);
	for(int i=1;i<=t;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		ans+=p[x][y]*y;
		a[i]=p[x][1]*y-p[x][y]*y;
	}
	sort(a+1,a+t+7);
	for(int i=1;i<=6;++i)ans+=a[i];
	double d=ans*0.01;
	printf("%.10lf\n",d);
    return 0;
}
