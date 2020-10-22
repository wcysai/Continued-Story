#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],b[200005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)scanf("%d",a+i);
	for(int i=m;i;--i)if(!b[a[i]])printf("%d\n",a[i]),b[a[i]]=1;
	for(int i=1;i<=n;++i)if(!b[i])printf("%d\n",i);
	return 0;
}
	