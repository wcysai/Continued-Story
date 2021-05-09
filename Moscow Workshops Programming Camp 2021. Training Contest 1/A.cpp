#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
#define P    pair<int,int>
#define X    first
#define Y    second
using namespace std;
int n,m,t,x[30005],y[30005],dx[30005],dy[30005],a[90005],b[90005],ans;
pair<int,int> p[30005];
P A[50005],B[50005],C[50005];
ll res;
P mns(P x,P y){x.X-=y.X,x.Y-=y.Y;return x;}
ll det(P x,P y){return x.X*1ll*y.Y-x.Y*1ll*y.X;}
ll norm(P x){return x.X*1ll*x.X+x.Y*1ll*x.Y;}
ll pw(int x){return x*1ll*x;}
ll dis(int x,int y){return pw(a[x]-a[y])+pw(b[x]-b[y]);}
ll g(int x,int y,int z){return abs((a[y]-a[x])*1ll*(b[z]-b[x])-(a[z]-a[x])*1ll*(b[y]-b[x]));}
ll f(int _){
	for(int i=1;i<=n;++i)A[i]=mp(x[i]+dx[i]*_,y[i]+dy[i]*_);
	sort(A+1,A+n+1);
	int lb=0,lc=0;
	for(int i=1;i<=n;++i){
        while(lb>1&&det(mns(B[lb],B[lb-1]),mns(A[i],B[lb]))>=0)--lb;
        B[++lb]=A[i];
    }
    for(int i=1;i<=n;++i){
        while(lc>1&&det(mns(C[lc],C[lc-1]),mns(A[i],C[lc]))<=0)--lc;
        C[++lc]=A[i];
    }
    for(int i=1;i<=lb;++i)a[i]=B[i].first,b[i]=B[i].second;
    m=lb;
    for(int i=lc-1;i>1;--i)++m,a[m]=C[i].first,b[m]=C[i].second;
    for(int i=1;i<=m;++i)a[i+m]=a[i+m*2]=a[i],b[i+m]=b[i+m*2]=b[i];
	int k=2;
	ll ret=0;
	for(int i=1;i<=m;++i){
		while(k<m*3&&g(i,i+1,k+1)>=g(i,i+1,k))++k;
		ret=max(ret,dis(i,k));
		ret=max(ret,dis(i+1,k));
	}
	return ret;
}
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;++i)cin>>x[i]>>y[i]>>dx[i]>>dy[i];
	int l=0,r=t;
	while(r-l>2){
		int L=(l*2+r)/3,R=l+r-L;
		if(f(L)<=f(R))r=R;
		else l=L;
	}
	ans=l,res=f(l);
	for(int i=l-1;i<=r+1;++i){
		if(i>=0&&i<=t){
			ll o=f(i);
			if(o<res||(o==res&&i<ans))
			{
				res=o,ans=i;
			}
		}
	}
	cout<<ans<<endl<<res<<endl;
    return 0;
}
