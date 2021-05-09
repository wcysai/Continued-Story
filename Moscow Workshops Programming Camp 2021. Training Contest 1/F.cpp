//team continued story
#include<bits/stdc++.h>
#define ll    long long
#define orz   1000000007
using namespace std;
ll fp(ll x,ll k=orz-2){
    ll a=1;
    while(k){
        if(k&1)(a*=x)%=orz;
        k>>=1,(x*=x)%=orz;
    }
    return a;
}
int t;
ll r,g,b,k;
int main(){
    cin>>t;
    while(t--){
        cin>>r>>g>>b>>k;
        ll ans=r*(1-fp(b*fp(b+1)%orz,k))+k*(g+b)%orz*fp(b)%orz;
        ans=(ans%orz+orz)%orz;
        cout<<ans<<endl;
    }
    return 0;
}