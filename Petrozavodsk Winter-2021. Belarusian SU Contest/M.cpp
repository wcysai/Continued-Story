#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int k;
ll n,a[1000005];
int main(){
	scanf("%lld",&n);
	if(n==1){
		printf("1\n1\n");
		return 0;
	}
	a[++k]=1;
	for(ll i=1,j=2;;){
		if(i*j>n) break;
		a[++k]=i*j;
		i=j;
		if(j%3==2)j+=2;
		else ++j;
	}
	k=min(k,1000000);
	printf("%d\n",k);
	for(int i=1;i<k;++i)printf("%lld ",a[i]);
	printf("%lld\n",a[k]);
    return 0;
}
