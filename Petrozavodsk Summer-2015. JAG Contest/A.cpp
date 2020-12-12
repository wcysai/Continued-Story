#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,a[100005],b[100005],f[100005][18],s[100005][18],mn[100005][18],mx[100005][18],num[100005];
vector<int> v[100005],dl[100005],dr[100005];
map<int,int> ml[100005],mr[100005];
ll ans;
void dfs(int x,int y){
	f[x][0]=y;
	b[x]=b[y]+a[x];
	s[x][0]=mn[x][0]=mx[x][0]=a[x];
	for(int i=0;i<17;++i)f[x][i+1]=f[f[x][i]][i],s[x][i+1]=s[x][i]+s[f[x][i]][i],mn[x][i+1]=min(mn[x][i],s[x][i]+mn[f[x][i]][i]),mx[x][i+1]=max(mx[x][i],s[x][i]+mx[f[x][i]][i]);
	int k=x,S=0,_=0;
	if(a[x]>0){
		for(int i=17;i>=0;--i)if(mn[k][i]+S>=0)S+=s[k][i],k=f[k][i],_|=(1<<i);
		--_;
		k=x;
		for(int i=17;i>=0;--i)if(_&(1<<i))k=f[k][i];
		dl[k].pb(b[x]);
	}
	else{
		for(int i=17;i>=0;--i)if(mx[k][i]+S<=0)S+=s[k][i],k=f[k][i],_|=(1<<i);
		--_;
		k=x;
		for(int i=17;i>=0;--i)if(_&(1<<i))k=f[k][i];
		dr[k].pb(b[x]);
	}
	for(int i=0;i<v[x].size();++i)if(v[x][i]!=y)dfs(v[x][i],x);
}
void sol(int x,int y){
	int k=x;
	for(int i=0;i<v[x].size();++i){
		int z=v[x][i];
		if(z==y) continue;
		sol(z,x);
		if(ml[num[z]].size()+mr[num[z]].size()>ml[k].size()+mr[k].size())k=num[z];
	}
	num[x]=k;
	int _=b[x]+b[f[x][0]];
	for(int i=0;i<v[x].size();++i){
		int z=v[x][i];
		if(z==y) continue;
		z=num[z];
		if(z==k) continue;
		for(map<int,int>::iterator it=ml[z].begin();it!=ml[z].end();++it)if(mr[k].count(_-it->first))ans+=(it->second)*1ll*mr[k][_-it->first];
		for(map<int,int>::iterator it=mr[z].begin();it!=mr[z].end();++it)if(ml[k].count(_-it->first))ans+=(it->second)*1ll*ml[k][_-it->first];
		for(map<int,int>::iterator it=ml[z].begin();it!=ml[z].end();++it)ml[k][it->first]+=it->second;
		for(map<int,int>::iterator it=mr[z].begin();it!=mr[z].end();++it)mr[k][it->first]+=it->second;
	}
	if(a[x]>0){
		if(mr[k].count(_-b[x]))ans+=mr[k][_-b[x]];
		++ml[k][b[x]];
	}
	else{
		if(ml[k].count(_-b[x]))ans+=ml[k][_-b[x]];
		++mr[k][b[x]];
	}
	for(int i=0;i<dl[x].size();++i)--ml[k][dl[x][i]];
	for(int i=0;i<dr[x].size();++i)--mr[k][dr[x][i]];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		char c;
		scanf(" %c",&c);
		if(c=='(')a[i]=1;
		else a[i]=-1;
	}
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].pb(y);
		v[y].pb(x);
	}
	dfs(1,0);
	sol(1,0);
	cout<<ans<<endl;
    return 0;
}
