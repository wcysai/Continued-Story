#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int T;
ll n,x[7][7],a[7][7],t[7][7];
int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n;
		memset(x,0,sizeof(x));
		memset(a,0,sizeof(a));
		x[1][2]=x[2][3]=x[3][4]=x[4][5]=x[5][6]=1;
		x[1][1]=1,x[2][1]=2,x[3][1]=6,x[4][1]=1,x[6][1]=-1;
		a[1][1]=a[2][2]=a[3][3]=a[4][4]=a[5][5]=a[6][6]=1;
		while(n){
			if(n&1){
				for(int i=1;i<=6;++i){
					for(int j=1;j<=6;++j){
						ll o=0;
						for(int k=1;k<=6;++k)(o+=x[i][k]*a[k][j])%=orz;
						t[i][j]=o;
					}
				}
				for(int i=1;i<=6;++i){
					for(int j=1;j<=6;++j)a[i][j]=t[i][j];
				}
			}
			n>>=1;
			for(int i=1;i<=6;++i){
				for(int j=1;j<=6;++j){
					ll o=0;
					for(int k=1;k<=6;++k)(o+=x[i][k]*x[k][j])%=orz;
					t[i][j]=o;
				}
			}
			for(int i=1;i<=6;++i){
				for(int j=1;j<=6;++j)x[i][j]=t[i][j];
			}
		}
		ll ans=a[1][6]*62+a[2][6]*23+a[3][6]*10+a[4][6]*3+a[5][6]+a[6][6];
		ans=(ans%orz+orz)%orz;
		cout<<ans<<endl;
	}
    return 0;
}