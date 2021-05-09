//team continued story
#include<bits/stdc++.h>
#define ll    long long
#define orz   1000000007
using namespace std;
ll fp(ll x,int k=orz-2){
    ll a=1;
    while(k){
        if(k&1)(a*=x)%=orz;
        k>>=1,(x*=x)%=orz;
    }
    return a;
}

ll jc[5005],njc[5005],ny[5005],c[5005],nc[5005],p[5005],d[5005],ny1,f[5005][5005],q[5005],P[5005],C[5005],ans;
int n;
int main(){
    cin>>n;
    ny1=fp(1000000000);
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%orz;
    njc[n]=fp(jc[n]);
    for(int i=n;i;--i)njc[i-1]=njc[i]*i%orz;
    for(int i=1;i<=n;++i)ny[i]=njc[i]*jc[i-1]%orz;
    for(int i=0;i<=n;++i)nc[i]=jc[i]*jc[n-i]%orz*njc[n]%orz,c[i]=njc[i]*njc[n-i]%orz*jc[n]%orz;
    for(int i=1;i<=n;++i){
        cin>>p[i]>>d[i];
        p[i]=p[i]*ny1%orz;
        P[i]=(orz+1-p[i])%orz;
    }
    for(int i=1;i<=n;++i)f[i][1]=(f[i-1][1]+P[i])%orz;
    for(int i=1;i<=n;++i){
        for(int j=2;j<=i;++j)f[i][j]=(f[i-1][j]+f[i-1][j-1]*P[i])%orz;
    }
    for(int i=1;i<=n;++i)q[i]=f[n][i];
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;++i)C[i]=f[1][i]=ny[n];
    for(int i=1;i<n;++i){
        ll _=c[i-1]*(n-i+1)%orz,__=nc[i]*ny[n-i]%orz;
        for(int j=1;j<=n;++j)(C[j]+=(f[i+1][j]=__*(q[i]-_*f[i][j]%orz*P[j]%orz)%orz))%=orz;
    }
    for(int i=1;i<=n;++i)(ans+=C[i]*p[i]%orz*d[i])%=orz;
    ans=(ans%orz+orz)%orz;
    cout<<ans<<endl;
    return 0;
}