#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int T,n,a[2005][2005],b[2005],B,u[2005],k,la[2005];
pair<int,int> p[2005];
ll d[2005];
void dfs(int x){
	u[x]=-1;
	for(int i=1;i<=n;++i)if(a[x][i]&&!u[i])dfs(i);
	b[++B]=x;
}
void dfs2(int x){
	u[x]=k;
	for(int i=1;i<=n;++i)if(a[x][i]&&u[i]==-1)dfs2(i);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j)scanf("%d",a[i]+j);
		}
		if(n==2){
			printf("NO\n");
			continue;
		}
		for(int i=1;i<=n;++i)u[i]=0;
		B=k=0;
		for(int i=1;i<=n;++i)if(!u[i])dfs(i);
		for(int i=1;i<=n;++i)if(u[b[i]]==-1)++k,dfs2(b[i]);
		for(int i=1;i<=n;++i){
			if(u[i]==1)b[i]=1,d[i]=0;
			else b[i]=0,d[i]=-1;
		}
		for(int i=1;i<=n;++i){
			int k=0;
			for(int j=1;j<=n;++j)if(b[j]==1&&(!k||d[j]<d[k]))k=j;
			b[k]=2;
			for(int j=1;j<=n;++j){
				if(b[j]==2) continue;
				if(d[j]==-1)d[j]=d[k]+a[j][k],b[j]=1,la[j]=k;
				else if(d[k]+a[j][k]<d[j])d[j]=d[k]+a[j][k],la[j]=k;
			}
		}
		int x=0,m=0;
		for(int i=1;i<=n;++i)if(u[i]==k&&(!x||d[x]>d[i]))x=i;
		for(int i=x;u[i]>1;i=la[i])if(a[i][la[i]])p[++m]=mp(i,la[i]);
		printf("YES\n%d %lld\n",m,d[x]);
		for(int i=1;i<=m;++i)printf("%d %d\n",p[i].first,p[i].second);
	}
    return 0;
}
