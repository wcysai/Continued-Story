#include<bits/stdc++.h>
#define ll      long long
using namespace std;
int n,q,k;
ll a[505105];
int main(){
    scanf("%d%d",&n,&q);
    k=1;
    for(int i=1;i<=n;++i)scanf("%I64d",a+i);
    for(int i=2;i<=n;++i)if(a[i]*k<a[k]*i)k=i;
    for(int i=n+1;i<=5051*k;++i){
        a[i]=a[i-1]+a[1];
        for(int j=2;j<=n;++j)a[i]=min(a[i],a[i-j]+a[j]);
    }
    while(q--){
        int m;
        scanf("%d",&m);
        if(m<=5051*k){
            printf("%I64d\n",a[m]);
        }
        else{
            int o=m%k+5050*k;
            printf("%I64d\n",a[o]+(m-o)/k*a[k]);
        }
    }
    return 0;
}