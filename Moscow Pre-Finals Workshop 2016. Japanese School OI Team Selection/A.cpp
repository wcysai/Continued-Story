#include<bits/stdc++.h>
#define mp    make_pair
#define fi    first
#define se    second
#define ll    long long
using namespace std;
ll n,S,ans;
int m;
string s[100005];
ll k[100005];
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    cin>>m;
    for(int i=1;i<=m;++i)cin>>s[i]>>k[i];
    for(int i=1;i<=m;++i){
        int l=s[i].size();
        ll o=0;
        for(int j=0;j<l;++j)if(s[i][j]=='F')++o;
        S+=o*k[i];
    }
    if(S<n){
        cout<<-1<<endl;
        return 0;
    }
    S=(S-n)*2;
    ans=S;
    for(int i=1;i<=m;++i){
        int ss=0,mm=0,l=s[i].size();
        for(int j=0;j<l;++j){
            if(s[i][j]=='M')++ss;
            else --ss;
            if(ss<mm)mm=ss;
        }
        if(ss<0)ans=min(ans,S+ss*1ll*(k[i]-1)+mm);
        else ans=min(ans,S+mm);
        S+=ss*1ll*k[i];
    }
    cout<<max(0ll,-1ll-ans)<<endl;
    return 0;
}