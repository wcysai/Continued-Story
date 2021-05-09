#include<bits/stdc++.h>
using namespace std;
string s;
int ans;
int main(){
    cin>>s;
    for(int i=15;i>=0;--i){
        int x=s[i]-48;
        if(i%2==0)x*=2;
        if(x>9)x-=9;
        ans+=x;
    }
    if(ans%10==0)puts("YES");
    else puts("NO");
    return 0;
}