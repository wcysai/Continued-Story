#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  998244353
using namespace std;
int n;
ll ans=1;
int main(){
	scanf("%d",&n);
	if(n&1){
		printf("0\n");
		return 0;
	}
	if(n==2){
		printf("1\n");
		return 0;
	}
	for(int i=n/2+1;i<=n;++i)(ans*=i)%=orz;
	for(int i=n/2-2;i;--i)(ans*=n)%=orz;
	printf("%lld\n",ans);
    return 0;
}
