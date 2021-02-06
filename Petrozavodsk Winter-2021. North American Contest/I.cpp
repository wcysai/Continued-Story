#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,m,a[200005],b[200005],cnt;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",a+i),cnt+=a[i];
	for(int i=1;i<=m;++i)scanf("%d",b+i);
	if(!cnt){
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;++i){
		if(i<=m){
			cnt-=a[b[i]];
			a[b[i]]^=1;
			cnt+=a[b[i]];
		}
		if(cnt<=i){
			printf("%d\n",i);
			return 0;
		}
	}
    return 0;
}
