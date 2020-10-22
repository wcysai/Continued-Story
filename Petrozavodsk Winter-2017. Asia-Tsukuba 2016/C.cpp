#include<bits/stdc++.h>
using namespace std;
int n,m,l[200005],r[200005],f[100005],a[200005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		f[x]=y;
	}
	for(int i=1;i<=n;++i)l[i]=r[i]=i;
	for(int i=1;i<=100000;++i){
		if(!f[i]) continue;
		l[f[i]+1]=l[f[i]];
		r[f[i]]=r[f[i]+1];
	}
	for(int i=1;i<=n;++i)a[i]=r[i]-l[i]+1;
	for(int i=1;i<n;++i)printf("%d ",a[i]);
	printf("%d\n",a[n]);
	return 0;
}
	