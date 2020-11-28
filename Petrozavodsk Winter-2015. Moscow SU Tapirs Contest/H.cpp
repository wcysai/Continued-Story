#include<bits/stdc++.h>
#define orz  1000000007
using namespace std;
typedef long long ll;
ll jc[105],b[10005];
int n;
int main()
{
    jc[0]=1;
    for(int i=1;i<=101;++i)jc[i]=jc[i-1]*i%orz;
    b[0]=1;
    for(int i=1;i<=10000;++i)b[i]=b[i-1]*2ll%orz;
    cin>>n;
    if(n==1){
        puts("1");
        puts("0");
        puts("0");
        return 0;
    }
    if(n==2){
        puts("2");
        puts("1");
        puts("0");
        return 0;
    }
    if(n==3){
        puts("12");
        puts("6");
        puts("6");
        return 0;
    }
    cout<<jc[n]*b[(n-2)*(n-1)/2]%orz<<endl;
    cout<<jc[n+1]*b[(n+1)*(n-4)/2]%orz<<endl;
    cout<<jc[n]*n%orz*b[(n+1)*(n-4)/2]%orz<<endl;
    return 0;
}