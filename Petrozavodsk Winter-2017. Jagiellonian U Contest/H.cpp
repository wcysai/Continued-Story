#include<bits/stdc++.h>
#define orz      1000000007
using namespace std;
int z,n,S,m,d[200005],s[200005],cnt[200005];
vector<int> v[200005];
void dfs(int x,int y){
	for(int i=0;i<v[x].size();++i){
		if(v[x][i]!=y)d[v[x][i]]=d[x]+1,dfs(v[x][i],x);
	}
}
void dfs2(int x,int y){
	s[x]=1;
	for(int i=0;i<v[x].size();++i){
		if(v[x][i]!=y)dfs2(v[x][i],x),s[x]+=s[v[x][i]];
	}
}
void ope(int x,int y){
	for(int i=0;i<v[x].size();++i){
		int z=v[x][i];
		if(z==y) continue;
		ope(z,x);
		d[x]=max(d[x],d[z]);
	}
	cnt[d[x]]+=2;
}
void sol(int x,int y){
	if(x==m){
		for(int i=0;i<v[x].size();++i){
			if(v[x][i]!=y)ope(v[x][i],x),cnt[d[v[x][i]]]=orz;
		}
		return;
	}
	for(int i=0;i<v[x].size();++i){
		int z=v[x][i];
		if(z==y||d[z]<d[x]) continue;
		ope(z,x);
	}
	for(int i=0;i<v[x].size();++i){
		if(d[v[x][i]]<d[x])sol(v[x][i],x);
	}
}
int main(){
    scanf("%d",&z);
    while(z--){
    	scanf("%d%d%d",&n,&S,&m);
    	for(int i=1;i<=n;++i)v[i].clear(),cnt[i]=0;
    	for(int i=1;i<n;++i){
    		int x,y;
    		scanf("%d%d",&x,&y);
    		v[x].push_back(y);
    		v[y].push_back(x);
    	}
    	d[m]=0;
    	dfs(m,0);
    	//dfs2(S,0);
    	sol(S,0);
    	int ans=orz,c=0;
    	for(int i=n;i;--i){
    		c+=cnt[i];
    		if(c>=orz) break;
    		ans=min(ans,c+i-1);
    	}
    	printf("%d\n",ans+d[S]);
    }
    return 0;
}
