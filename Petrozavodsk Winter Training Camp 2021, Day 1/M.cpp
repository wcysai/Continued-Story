#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
#define fi   first
#define se   second
using namespace std;
int T,n,a[200005],b[200005];
pair<int,int> p[200005];
ll x,y,s[200005];
int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;++i)cin>>p[i].fi,p[i].se=i,a[i]=0;
		cin>>x>>y;
		sort(p+1,p+n+1);
		for(int i=1;i<=n;++i)s[i]=s[i-1]+p[i].fi;
		int m=0,l=n;
		for(int r=n;r;--r){
			while(l>1&&(s[r]-s[l-2])*x>=y*p[r].fi*(r-l+2))--l;
			m=max(m,r-l+1);
		}
		if(m==1){
			cout<<0<<endl<<endl;
			continue;
		}
		l=n;
		for(int r=n;r;--r){
			while(l>1&&(s[r]-s[l-2])*x>=y*p[r].fi*(r-l+2))--l;
			if(m==r-l+1){
				int _=l;
				for(int i=17;i>=0;--i){
					int k=_-(1<<i);
					if(k<1) continue;
					if((s[r]-s[l]+p[k].fi)*x>=y*p[r].fi*(r-l+1))_=k;
				}
				++a[_],--a[r+1];
			}
		}
		int B=0;
		for(int i=1;i<=n;++i){
			a[i]+=a[i-1];
			if(!a[i])b[++B]=p[i].se;
		}
		if(!B){
			cout<<0<<endl<<endl;
			continue;
		}
		cout<<B<<endl;
		sort(b+1,b+B+1);
		for(int i=1;i<B;++i)cout<<b[i]<<' ';
		cout<<b[B]<<endl;
	}
    return 0;
}