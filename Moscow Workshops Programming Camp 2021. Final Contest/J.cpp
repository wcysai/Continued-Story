//team continued story
#include<bits/stdc++.h>
#define ll     long long
#define mp     make_pair
#define pb     push_back
#define X      first
#define Y      second
#define orz    1000000007
using namespace std;
int n,a[1000005],A[1000005],m,b[1000005],c[1000005],t[2000005];
vector<int> v[1000005];
ll ans;
pair<pair<int,int>,int> p[1000005];
int pos(int x){
	int o=1;
	for(int i=19;i>=0;--i){
		int O=o+(1<<i);
		if(O<=m&&b[O]<=x)o=O;
	}
	return o;
}
void add(int x){while(x<=n*2)++t[x],x+=(x&-x);}
int sum(int x){int s=0;while(x)s+=t[x],x&=(x-1);return s;}


int main(){
//freopen("J.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i),A[i]=a[i];
	sort(A+1,A+n+1);
	for(int i=1;i<=n;++i)if(A[i]!=A[i-1])b[++m]=A[i];
	b[++m]=orz;
	for(int i=1;i<=n;++i)v[A[i]=pos(a[i])].pb(i);
	for(int i=m;i;--i){
		int k=v[i].size(),o=0,cnt=0;
		for(int j=0;j<k;++j)if(v[i][j]>c[i+1])p[v[i][j]]=mp(mp(i,--cnt),v[i][j]),o=v[i][j];
		for(int j=0;j<k;++j)if(v[i][j]<c[i+1])p[v[i][j]]=mp(mp(i,--cnt),v[i][j]),o=v[i][j];
		c[i]=o;
	}
	sort(p+1,p+n+1);
	add(p[1].Y),add(p[1].Y+n);
	for(int i=2;i<=n;++i){
		int r=p[i-1].Y,l=p[i].Y;
		if(r<l)r+=n;
		ans+=sum(r-1)-sum(l);
		add(p[i].Y),add(p[i].Y+n);
	}
	cout<<ans+p[n].Y-1<<endl;
    return 0;
}