#include<bits/stdc++.h>
#define ll      long long
#define pb      push_back
#define mp      make_pair
using namespace std;
int n,a[100005],s[100005],t[100005];
int T,p,ans[105];
int A[1100005],C[1100005],L[1100005];
ll ansc[105];
int ansl[105],ansr[105];
int qry(int x){
    int k=x*1ll*x%1000003ll;
    while(A[k]!=-1&&A[k]!=x)++k;
    return k;
}
int fp(ll x,ll p,int k){
    ll a=1;
    while(k){
        if(k&1)(a*=x)%=p;
        k>>=1,(x*=x)%=p;
    }
    return a;
}
int main(){
    char c=getchar();
    while(c>47)a[++n]=c-48,c=getchar();
    cin>>T>>p;
    for(int i=1;i<=T;++i)cin>>ans[i];
    t[0]=1,t[1]=fp(10,p,p-2);
    for(int i=2;i<=n;++i)t[i]=t[i-1]*1ll*t[1]%p;
    for(int i=1;i<=n;++i)s[i]=(s[i-1]+a[i]*1ll*t[i])%p;
    memset(A,-1,sizeof(A));
    for(int i=1;i<=n;++i){
        int k=qry(s[i-1]);
        if(A[k]==-1)A[k]=s[i-1],C[k]=1,L[k]=i;
        else ++C[k];
        for(int j=1;j<=T;++j){
            ll o=s[i]-ans[j]*1ll*t[i];
            o=(o%p+p)%p;
            int k=qry(o);
            if(A[k]==-1) continue;
            if(!ansc[j])ansl[j]=L[k],ansr[j]=i;
            ansc[j]+=C[k];
        }
    }
    for(int i=1;i<=T;++i)cout<<ansc[i]<<' '<<ansl[i]<<' '<<ansr[i]<<endl;
    return 0;
}