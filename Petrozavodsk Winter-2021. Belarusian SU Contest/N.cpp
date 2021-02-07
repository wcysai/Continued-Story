#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,a[1000005],f[1000005][20],b[1000005],ans,B[1000005];
int get(int l,int r){
	int d=B[r-l];
	int L=f[l][d],R=f[r-(1<<d)+1][d];
	if(a[L]<a[R]) return R;
	return L;
}
void sol(int l,int r,int x){
	int k=get(l,r);
	if(a[k]+r-l<x) return;
	if(k>l)sol(l,k-1,max(a[k],x-r+k-1));
	b[++ans]=k;
	if(k<r)sol(k+1,r,max(a[k],x-k+l-1));
}		
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i),f[i][0]=i;
	for(int i=1;i<=n;++i){
		B[i]=B[i-1];
		if(i==(2<<B[i]))++B[i];
	}
	for(int k=0;k<19;++k){
		for(int i=n-(1<<k)+1;i>0;--i)f[i][k+1]=a[f[i][k]]<a[f[i+(1<<k)][k]]?f[i+(1<<k)][k]:f[i][k];
	}
	int k=get(1,n);
	if(k>1)sol(1,k-1,a[k]);
	b[++ans]=k;
	if(k<n)sol(k+1,n,a[k]);
	printf("%d\n",ans);
	for(int i=1;i<ans;++i)printf("%d ",b[i]);
	printf("%d\n",b[ans]);
    return 0;
}