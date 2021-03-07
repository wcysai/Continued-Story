#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,a[300005],x=1,cnt=1,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	for(int i=2;i<=n;++i){
		if(a[i]==a[i-1]) continue;
		int y=a[i]>a[i-1]?1:-1;
		if(x!=y)++cnt,x=y;
	}
	int o=1;
	while(o<cnt)o*=2,++ans;
	printf("%d\n",ans);
    return 0;
}
