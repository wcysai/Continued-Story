#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,a[23],b[23];
double f[4200000],g[25];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%d",a+i);
	for(int _=1;_<(1<<n);++_){
		double s=1.0,S=0,p=1.0;
		for(int i=0;i<n;++i){
			if(_&(1<<i)){
				double d=f[_^(1<<i)]-a[i];
				if(d>=-1e-10)b[i]=0,f[_]=max(f[_],a[i]*1.0);
				else g[i]=1.0/d,b[i]=1;
			}
			else b[i]=0;
		}
		bool ok=0;
		while(!ok){
			s=1.0,S=0,p=1.0;
			for(int i=0;i<n;++i){
				if(b[i]){
					s+=a[i]*g[i];
					S+=g[i];
					p*=g[i];
				}
			}
			ok=1;
			if(fabs(S)<1e-10) break;
			for(int i=0;i<n;++i){
				if(b[i]){
					if(s/S>a[i])ok=0,f[_]=max(f[_],a[i]*1.0),b[i]=0;
				}
			}
		}
		if(fabs(S)>1e-10)f[_]=max(f[_],s/S);
	}
	printf("%.13f\n",f[(1<<n)-1]);
    return 0;
}
