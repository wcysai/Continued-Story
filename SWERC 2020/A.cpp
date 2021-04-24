#include<bits/stdc++.h>
#define mp    make_pair
#define fi    first
#define se    second
#define L    long long
using namespace std;
int n,f[8],a[65536][60];
L k;
int main()
{
    for(int i=15;i>=0;--i){
        int x;
        scanf("%1d",&x);
        n+=(x<<i);
    }
    scanf("%lld",&k);
    f[6]=f[5]=f[3]=f[2]=f[1]=1;
    for(int _=0;_<65536;++_){
        int __=0;
        for(int i=0;i<15;++i)__|=(2<<f[(_>>i)&7]);
        a[_][0]=(__|f[(_&3)<<1]);
    }
    for(int k=0;k<59;++k){
        for(int _=0;_<65536;++_)a[_][k+1]=a[a[_][k]][k];
    }
    for(int i=59;i>=0;--i){
        if(k&(1ll<<i))n=a[n][i];
    }
    int cnt=0;
    for(int i=0;i<16;++i)if(n&(1<<i))++cnt;
    printf("%d\n",cnt);
    return 0;
}