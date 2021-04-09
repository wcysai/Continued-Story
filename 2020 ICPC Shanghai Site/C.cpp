#include<bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;
int T,n,a[5005],f[5005][5005],L[5005],b[5005][16],c[5005];
void u(int &x,int y){
    if(y>x)x=y;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",a+i),L[i]=0;
        if(n==1){
            printf("0\n");
            continue;
        }
        for(int i=1;i<n;++i){
            for(int j=i+1;j<=n;++j)f[i][j]=0;
        }
        for(int i=1;i<=n;++i){
            c[i]=L[a[i]];
            b[a[i]][L[a[i]]++]=i;
        }
        for(int i=1;i<n;++i)f[i][i+1]=(a[i]==a[i+1]);
        for(int d=2;d<n;++d){
            for(int r=d+1;r<=n;++r){
                int l=r-d,o=(a[l]==a[r])+max(f[l+1][r],f[l][r-1]);
                int x=a[l];
                for(int i=c[l]+1;i<L[x];++i){
                    int k=b[x][i];
                    if(k>=r) break;
                    u(o,f[l][k]+f[k][r]);
                }
                x=a[r];
                for(int i=c[r]-1;i>=0;--i){
                    int k=b[x][i];
                    if(k<=l) break;
                    u(o,f[l][k]+f[k][r]);
                }
                f[l][r]=o;
            }
        }
        printf("%d\n",n-1-f[1][n]);
    }
    return 0;
}