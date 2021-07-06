#include<bits/stdc++.h>
using namespace std;
int T,n,k,f[10002][10002];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        f[1][1]=k-1;
        for(int d=3;d<=n+1;++d){
            for(int x=1;x<d;++x){
                int y=d-x;
                f[x][y]=(f[x][y-1]/2)+((f[x-1][y]+1)/2);
            }
        }
        int x=1,y=1,ans=0;
        for(int i=1;i<=n;++i){
            if(f[x][y]&1)++y,++ans;
            else ++x;
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j)cout<<f[i][j];
            cout<<endl;
        }
        printf("%d\n",ans);
    }
    return 0;
}