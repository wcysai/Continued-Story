#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  10007
using namespace std;
int n,m,k,a[505][505],_,t1[505][505],t2[505][505],t3[505][505],t4[505][505],ans;
pair<int,pair<int,int> > p[250005];
void add(int x,int y){
	for(int i=x;i<=n;i+=(i&-i)){
		for(int j=y;j<=m;j+=(j&-j)){
			(t1[i][j]+=1)%=orz;
			(t2[i][j]+=x)%=orz;
			(t3[i][j]+=y)%=orz;
			(t4[i][j]+=x*y)%=orz;
		}
	}
}
void sub(int x,int y){
	for(int i=x;i<=n;i+=(i&-i)){
		for(int j=y;j<=m;j+=(j&-j)){
			(t1[i][j]-=1)%=orz;
			(t2[i][j]-=x)%=orz;
			(t3[i][j]-=y)%=orz;
			(t4[i][j]-=x*y)%=orz;
		}
	}
}
int sum(int x,int y){
	int s=0,_=(x+1)*(y+1)%orz;
	for(int i=x;i;i&=(i-1)){
		for(int j=y;j;j&=(j-1))(s+=t1[i][j]*_-t2[i][j]*(y+1)-t3[i][j]*(x+1)+t4[i][j])%=orz;
	}
	return s;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)scanf("%d",a[i]+j),p[++_]=mp(a[i][j],mp(i,j));
	}
	sort(p+1,p+_+1);
	int __=(k*k-1)%orz;
	for(int i=1;i<=_;++i){
		int x=p[i].second.first,y=p[i].second.second,u=max(1,x-k+1),d=min(n-k+1,x),l=max(1,y-k+1),r=min(m-k+1,y);
		(ans+=p[i].first%orz*(((sum(d,r)-sum(d,l-1)-sum(u-1,r)+sum(u-1,l-1))*2-(d-u+1)*(r-l+1)%orz*__)%orz))%=orz;
		add(u,l),add(d+1,r+1),sub(u,r+1),sub(d+1,l);
	}
	ans=(ans*2%orz+orz)%orz;
	printf("%d\n",ans);
    return 0;
}