#include<bits/stdc++.h>
using namespace std;
int n,a[1100000];
long long d;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%d",a+i);
	if(n<=1){
		puts("0.000000000");
		return 0;
	}
	for(int i=1;i<n/2;++i)d+=1ll*abs(a[i]-a[n-i]);
	cout<<d<<".000000000"<<endl;
	return 0;
}