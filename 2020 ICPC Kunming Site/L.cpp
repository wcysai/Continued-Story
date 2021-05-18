#include<bits/stdc++.h>
using namespace std;
int T,n,a[1000005],f[1000005],c[1000005];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",a+i);
        int m=1;
        c[1]=1;
        f[1]=a[1];
        for(int i=2;i<=n;++i){
            int o=0;
            for(int j=19;j>=0;--j){
                int O=(1<<j)+o;
                if(O>m) continue;
                if(f[O]>a[i])o=O;
            }
            ++o;
            if(o>m)++m;
            c[i]=o;
            f[o]=a[i];
        }
        printf("%d\n",m);
        for(int i=1;i<n;++i)printf("%d ",c[i]);
        printf("%d\n",c[n]);
    }
    return 0;
}