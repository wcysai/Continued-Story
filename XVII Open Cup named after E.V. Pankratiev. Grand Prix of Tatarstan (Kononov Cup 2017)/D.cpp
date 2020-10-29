#include<bits/stdc++.h>
using namespace std;
#define  ll    long long
ll a[7],r;
ll f[1000005];
int k,m;
void dfs(int _,ll o,int i){
	if(_>k){
		f[++m]=o;
		return;
	}
	if(o>r/a[i]) return;
	dfs(_+1,o*a[i],i);
	if(i<6)dfs(_,o,i+1);	
}
int main(){
	ios::sync_with_stdio(0);
	a[1]=2ll*2ll;
	a[2]=3ll*3ll*3ll;
	a[3]=5ll*5ll*5ll*5ll*5ll;
	a[4]=7ll*7ll*7ll*7ll*7ll*7ll*7ll;
	a[5]=11ll*11ll*11ll*11ll*11ll*11ll*11ll*11ll*11ll*11ll*11ll;
	a[6]=13ll*13ll*13ll*13ll*13ll*13ll*13ll*13ll*13ll*13ll*13ll*13ll*13ll;
	cin>>k>>r;
	dfs(1,1ll,1);
	sort(f+1,f+m+1);
	cout<<m<<endl;
	for(int i=1;i<m;++i)cout<<f[i]<<' ';
	if(m)cout<<f[m]<<endl;
	return 0;
}