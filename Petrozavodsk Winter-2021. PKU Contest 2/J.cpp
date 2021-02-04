#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  998244353
#define fi   first
#define se   second
using namespace std;
int n,m,l[100005],r[100005],a[100005],P,k,t[300005],L[300005],cnt;
ll b[100005],ans;
pair<int,int> p[300005];
vector<int> vr[300005],va[300005];
void add(int x,int y){while(x<=k)t[x]+=y,x+=(x&-x);}
int sum(int x){
	int ret=0;
	while(x)ret+=t[x],x-=(x&-x);
	return ret;
}
int main(){
	scanf("%d%d",&n,&m);
	b[0]=1;
	for(int i=1;i<=n;++i)b[i]=b[i-1]*2%orz;
	for(int i=1;i<=n;++i)scanf("%d%d",l+i,r+i),p[++P]=mp(l[i],i),p[++P]=mp(r[i],i+n);
	for(int i=1;i<=m;++i)scanf("%d",a+i),p[++P]=mp(a[i],i+n*2);
	sort(p+1,p+P+1);
	for(int i=1;i<=P;++i){
		if(i==1||p[i].fi!=p[i-1].fi)++k;
		if(p[i].se<=n)l[p[i].se]=k;
		else if(p[i].se<=n*2)r[p[i].se-n]=k;
		else a[p[i].se-n*2]=k;
	}
	sort(a+1,a+m+1);
	for(int i=1;i<=n;++i)++L[l[i]],vr[r[i]].pb(l[i]);
	for(int i=1;i<=m;++i)va[a[i]].pb(a[i-1]);
	for(int i=1;i<=k;++i){
		cnt+=L[i];
		add(i,L[i]);
		for(int j=0;j<va[i].size();++j){
			int o=sum(va[i][j]);
			(ans+=(b[cnt-o]-1ll)*b[o])%=orz;
		}
		for(int j=0;j<vr[i].size();++j)add(vr[i][j],-1),--cnt;
	}
	printf("%lld\n",ans);
    return 0;
}
