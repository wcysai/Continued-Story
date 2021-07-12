#include<bits/stdc++.h>
#define ll    long long
#define pb    push_back
#define mp    make_pair
using namespace std;
int T,n,l,k;
int ans;
ll res;
double g;
void u(int x){
    int a=(l-1)/x+1;
    int b=g*x+1-5e-14;
    if(ans==0||a*1ll*b<res)ans=x,res=a*1ll*b;
}
int main(){
    cin>>T;
    while(T--){
        cin>>n>>l>>k;
        g=log2(n*1.0);
        ans=0;
        if(l==1){
            u(1);
            cout<<res<<' '<<ans<<endl;
            continue;
        }
        if(k==l){
            u(l);
            --k;
        }
        for(int i=1;i<=k;){
            u(i);
            i=(l-1)/((l-1)/i)+1;
        }
        cout<<res<<' '<<ans<<endl;
    }
    return 0;
}