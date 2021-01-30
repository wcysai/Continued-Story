#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
#define fi   first
#define se   second
using namespace std;
int n1,n2,m1,m2,f1[100005],f2[100005];
pair<pair<int,int>,pair<int,int> >p[200005];
ll ans;
int get1(int x){return x==f1[x]?x:f1[x]=get1(f1[x]);}
int get2(int x){return x==f2[x]?x:f2[x]=get2(f2[x]);}
int main(){
	scanf("%d%d%d%d",&n1,&m1,&n2,&m2);
	for(int i=0;i<n1;++i)f1[i]=i;
	for(int i=0;i<n2;++i)f2[i]=i;
	for(int i=1;i<=m1;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		p[i]=mp(mp(z,1),mp(x,y));
	}
	for(int i=1;i<=m2;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		p[i+m1]=mp(mp(z,2),mp(x,y));
	}
	sort(p+1,p+m1+m2+1);
	for(int i=1;i<=m1+m2;++i){
		if(p[i].fi.se==1){
			if(get1(p[i].se.fi)==get1(p[i].se.se)) continue;
			f1[f1[p[i].se.fi]]=f1[p[i].se.se];
			ans+=n2*1ll*p[i].fi.fi;
			--n1;
		}
		else{
			if(get2(p[i].se.fi)==get2(p[i].se.se)) continue;
			f2[f2[p[i].se.fi]]=f2[p[i].se.se];
			ans+=n1*1ll*p[i].fi.fi;
			--n2;
		}
	}
	printf("%lld\n",ans);
    return 0;
}
