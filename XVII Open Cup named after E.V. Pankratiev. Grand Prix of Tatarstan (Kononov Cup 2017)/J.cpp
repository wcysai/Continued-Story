#include<bits/stdc++.h>
#define fi    first
#define se    second
#define ll    long long
using namespace std;
int n,m,k,f[100005];
ll ans;
pair<int,int> p[2005];
int mx(int x,int y){return x>y?x:y;}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	ans=n*1ll*n+1ll;
	if(n<=k)ans--;
	for(int i=1;i<=n;++i){
		int x;
		scanf("%d",&x);
		p[x].fi=i;
		++p[x].se;
		if(p[x].se>k){
			puts("-1");
			return 0;
		}
	}
	sort(p+1,p+m+1);
	for(int i=1;i<m;++i){
		int o=f[k-p[i].se];
		if(o+p[i].se+k>=n){
			ans=min(ans,(o+p[i].se)*1ll*p[i].fi+(n-o-p[i].se)*1ll*n);
		}
		int s=p[i].se;
		for(int j=n;j>=s;--j)f[j]=mx(f[j],f[j-s]+s);	
	}
	if(ans>n*1ll*n)puts("-1");
	else cout<<ans<<endl;
	return 0;
}