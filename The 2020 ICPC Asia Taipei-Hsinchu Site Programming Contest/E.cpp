#include<bits/stdc++.h>
using namespace std;
char c[505];
int n,m,f[505][205],g[505][205],dp[505][505];
int main(){
    char C=getchar();
    while(C!=' ')c[++n]=C,C=getchar();
    scanf("%d",&m);
    for(int i=1;i<=n;++i) f[i][c[i]]=f[i-1][c[i]]+1;
    for(int i=n;i;--i) g[i][c[i]]=g[i+1][c[i]]+1;
    for(int d=1;d<=n;++d){
        for(int r=d;r<=n;++r){
            int l=r-d+1;
            if(g[l][c[l]]>=d)dp[l][r]=(d>=m);
            else if(c[l]==c[r]){
                if(g[l][c[l]]+f[r][c[r]]>=m){
                    int L=g[l][c[l]],R=f[r][c[r]];
                    for(int k=0;k<m;++k){
                        int o=min(k,L);
                        if(dp[l+L-o][r-R+k-o]){
                            dp[l][r]=1;
                            break;
                        }
                    }
                }
            }
            else{
                if(g[l][c[l]]>=m){
                    int L=g[l][c[l]];
                    for(int k=0;k<m;++k){
                        if(dp[l+L-k][r]){
                            dp[l][r]=1;
                            break;
                        }
                    }
                }
                if(f[r][c[r]]>=m){
                    int R=f[r][c[r]];
                    for(int k=0;k<m;++k){
                        if(dp[l][r-R+k]){
                            dp[l][r]=1;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(dp[1][n])puts("Yes");
    else puts("No");
    return 0;
}