#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int k,n,a[1000005];
int main(){
	scanf("%d",&k);
	if(k%4==2||k%4==3){
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	n=k/4;
	if(k==n*4){
		a[0]=2*n;
		for(int i=1;i<=n-1;++i)a[i]=n*4-i;
		for(int i=n;i<=2*n-2;++i)a[i]=n*4-1-i;
		for(int i=n*2-1;i<=n*3-2;++i)a[i]=n*4-2-i;
		a[n*3-1]=n*3;
		for(int i=n*3;i<=n*4-1;++i)a[i]=n*4-1-i;
	}
	else{
		a[0]=2*n-1;
		for(int i=1;i<=n;++i)a[i]=n*4+1-i;
		for(int i=n+1;i<=2*n;++i)a[i]=n*4-i;
		for(int i=n*2+1;i<=n*3-2;++i)a[i]=n*4-1-i;
		a[n*3-1]=n*3;
		for(int i=n*3;i<=n*4;++i)a[i]=n*4-i;
	}
	if(k==5){
		printf("2 4 1 3 0\n");
		return 0;
	}
	for(int i=0;i<k-1;++i)printf("%d ",a[i]);
	printf("%d\n",a[k-1]);
    return 0;
}
