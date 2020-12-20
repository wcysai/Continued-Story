#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  998244353
using namespace std;
struct FFT{
    static const int N=524333,M=998244353ll;
    int n,m;
    ll a[N],b[N],w[N],w2[N],r;
    ll P(ll x,ll k){
        ll ans=1;
        while(k){
            if(k&1)ans=ans*x%M;
            x=x*x%M,k>>=1;
        }
        return ans;
    }
    void fft(ll *a,ll *w){
        for(int i=0,j=0;i<n;++i){
            if(i<j)swap(a[i],a[j]);
            for(int k=n>>1;(j^=k)<k;k>>=1);
        }
        for(int i=2;i<=n;i<<=1){
            for(int j=0;j<n;j+=i){
                for(int k=0;k<(i>>1);++k){
                    int l=j+k,r=l+(i>>1);
                    ll o=a[r]*w[n/i*k]%M;
                    a[r]=(a[l]+M-o)%M,a[l]=(a[l]+o)%M;
                }
            }
        }
    }
    void mul(){
        fft(a,w),fft(b,w);
        for(int i=0;i<n;++i)a[i]=a[i]*b[i]%M*r%M;
        fft(a,w2);
    }
    void init(){
        m+=n-2,n=1;
        while(n<=m)n<<=1;
        r=P(n,M-2),w[0]=w2[0]=1,w[1]=w2[n-1]=P(3,(M-1)/n);
        for(int i=2;i<n;++i)w[i]=w2[n-i]=w[i-1]*w[1]%M;
    }
}_;
int n,k,l[200005],r[200005],a[400005],s[400005],p[400005],cnt;
ll tla=1,jc[200005],njc[200005];
map<int,int> m;
ll fp(ll x,int k=orz-2){
	ll ans=1;
	while(k){
		if(k&1)(ans*=x)%=orz;
		k>>=1;
		(x*=x)%=orz;
	}
	return ans;
}
void sol(){
	++cnt;
	k=0;
	m.clear();
	for(int i=1;i<=n;++i){
		scanf("%d%d",l+i,r+i);
		p[i]=l[i],p[i+n]=r[i];
	}
	sort(p+1,p+n*2+1);
	for(int i=1;i<=n*2;++i)if(i==1||p[i]!=p[i-1])a[m[p[i]]=++k]=p[i];
	for(int i=1;i<=k;++i)s[i]=0;
	for(int i=1;i<=n;++i)++s[m[l[i]]],--s[m[r[i]]];
	int S=0;
	ll ret=0,tl=0;
	for(int i=1;i<k;++i){
		S+=s[i];
		int len=a[i+1]-a[i];
		if(S){
			tl+=len;
			if(cnt==1)_.a[S]+=len;
			else _.b[S]+=len;
		}
	}
	(tla*=tl)%=orz;
}
int main(){
	scanf("%d",&n);
	jc[0]=1;
	for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%orz;
	njc[n]=fp(jc[n]);
	for(int i=n;i;--i)njc[i-1]=njc[i]*i%orz;
	sol();
	sol();
	_.n=_.m=n+1;
	for(int i=0;i<=n;++i)(_.a[i]*=jc[n-i])%=orz,(_.b[i]*=jc[n-i])%=orz;
	_.init();
	_.mul();
	ll res=0;
	for(int i=1;i<=n;++i)(res+=_.a[i]*njc[n-i])%=orz;
	res%=orz;
	res=res*njc[n]%orz;
	res=tla-res;
	res=(res%orz+orz)%orz;
	cout<<res<<endl;
    return 0;
}
