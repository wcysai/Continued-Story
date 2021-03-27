#include<bits/stdc++.h>
#define M      10007
#define ll     long long
using namespace std;
int n,l[105],f[105][205],out[105][105],res;
ll dp[105],p[205],P=1000000ll*10000000LL+37,s[205],g[105][105];
bool b[105];
inline long long mul(long long x,long long y)
{
    long long tmp=(x*y-(long long)((long double)x/P*y+1.0e-8)*P);
    return tmp<0 ? tmp+P : tmp;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",l+i);
        for(int j=1;j<=l[i];++j)scanf("%d",f[i]+j),f[i][j+l[i]]=f[i][j];
        dp[i]=l[i]+M;
    }
    p[0]=1;
    for(int i=1;i<=n*2;++i)p[i]=p[i-1]*M%P;
    for(int _=1;_<=10;++_){
        for(int i=1;i<=n;++i){
            int k=l[i];
            for(int j=1;j<=k*2;++j)s[j]=(s[j-1]+mul(p[j],dp[f[i][j]]))%P;
            for(int j=1;j<=k;++j)g[i][f[i][j]]=(mul(s[j+k-1]-s[j]+P,p[k-i+1])+dp[i])%P;
        }
        for(int i=1;i<=n;++i){
            int k=l[i];
            for(int j=1;j<=k*2;++j)s[j]=(s[j-1]+mul(p[j],g[f[i][j]][i]))%P,cout<<s[j]<<":";
            cout<<endl;
            dp[i]=0;
            for(int j=1;j<=k;++j)dp[i]=max(dp[i],mul(s[j+k]-s[j]+P,p[k-i])%P);
        }
        cout<<"_"<<_<<endl;
    for(int i=1;i<=n;++i)cout<<dp[i]<<';';
    cout<<endl;
    }
    for(int i=1;i<=n;++i){
        if(b[i]) continue;
        ++res;
        out[res][out[res][0]=1]=i;
        for(int j=i+1;j<=n;++j){
            if(dp[j]==dp[i]){
                b[i]=b[j]=1;
                out[res][++out[res][0]]=j;
            }
        }
        if(!b[i])--res;
    }
    if(!res)printf("none\n");
    else{
        printf("%d\n",res);
        for(int i=1;i<=res;++i){
            for(int j=1;j<out[i][0];++j)printf("%d ",out[i][j]);
            printf("%d\n",out[i][out[i][0]]);
        }
    }
    return 0;
}