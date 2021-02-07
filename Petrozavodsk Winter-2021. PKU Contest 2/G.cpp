#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,a[4005],b[4005],f[4005][4005];
void u(int &x,int y){if(y<x)x=y;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d",a+i,b+i);
	for(int i=0;i<=n;++i){
		for(int j=0;j<=n;++j)f[i][j]=orz;
	}
	f[0][0]=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=n;++j){
			int t=f[i-1][j];
			if(t==orz) continue;
			if(a[i]*(i-1)<t)u(f[i][j+1],t+a[i]);
			else u(f[i][j],t+a[i]);
			if(b[i]*(i-1)<t)u(f[i][j+1],t+b[i]);
			else u(f[i][j],t+b[i]);
		}
	}
	int k=0;
	while(f[n][k]==orz)++k;
	printf("%d\n",k);
    return 0;
}
