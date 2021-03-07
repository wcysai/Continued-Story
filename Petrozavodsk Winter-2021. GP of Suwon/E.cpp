#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,T;
ll a[300005],c[300005],p[300005],P[300005],q[300005],s[300005],d[300005],qd[300005],pc[300005],qc[300005];
ll fp(ll x,int k=orz-2){
	ll a=1;
	while(k){
		if(k&1)(a*=x)%=orz;
		k>>=1;
		(x*=x)%=orz;
	}
	return a;
}
int main(){
	scanf("%d%d",&n,&T);
	for(int i=1;i<n;++i)scanf("%lld",a+i),s[i]=s[i-1]+a[i],p[i]=a[i]*fp(s[i])%orz;
	for(int i=1;i<=n;++i)scanf("%lld",c+i),d[i]=2*p[i]*fp(1+p[i])%orz*c[i]%orz,pc[i]=(p[i]*c[i]+pc[i-1])%orz;
	P[n]=1;
	for(int i=n-1;i;--i)P[i]=((1-p[i]*p[i])%orz+orz)%orz*P[i+1]%orz,(d[i]+=d[i+1])%=orz;
	for(int i=1;i<n;++i)q[i]=p[i]*p[i]%orz*P[i+1]%orz;
	for(int i=n-1;i;--i)qd[i]=(q[i]*d[i+1]+qd[i+1])%orz,qc[i]=(q[i]*c[i]+qc[i+1])%orz,(q[i]+=q[i+1])%=orz;
	while(T--){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==y){
			printf("0\n");
			continue;
		}
		if(x>y)swap(x,y);
		ll ans=pc[y-1]-pc[x];
		ans+=(qd[1]-qd[x]-(q[1]-q[x])*d[x]%orz+qc[1]-qc[x])%orz*(1-p[x])%orz*fp(P[x])%orz;
		ans=ans*2+c[x]+c[y]%orz;
		ans=(ans%orz+orz)%orz;
		printf("%lld\n",ans);
	}
    return 0;
}
