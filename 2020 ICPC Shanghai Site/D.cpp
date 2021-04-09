#include<bits/stdc++.h>
#define ll    long long
using namespace std;
int T;
ll x,y;
int main(){
    cin>>T;
    while(T--){
        cin>>x>>y;
        ll o=__gcd(x,y);
        while(o>1)x/=o,o=__gcd(x,y);
        if(x==1)puts("HUMAN");
        else puts("ROBOT");
    }
    return 0;
}