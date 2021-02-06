#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  998244353
using namespace std;
int n,k,l[200005],r[200005],L,R;
ll k3,k2,ans;
char c[200005];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)scanf(" %c",c+i);
	for(int i=1;i<=n;++i)l[i]=l[i-1]+(c[i]=='W');
	for(int i=n;i;--i)r[i]=r[i+1]+(c[i]=='C');
	L=l[n],R=r[1];
	k3=(k-2ll)*(k-1ll)*k/6%orz*L%orz*R%orz;
	k2=(k-1ll)*k/2%orz;
	for(int i=1;i<=n;++i)if(c[i]=='A')(ans+=k3+(L*1ll*r[i]+R*1ll*l[i])%orz*k2%orz+l[i]*1ll*r[i]%orz*k)%=orz;
	printf("%lld\n",ans);
    return 0;
}
