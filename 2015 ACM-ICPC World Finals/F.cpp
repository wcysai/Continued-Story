#include<bits/stdc++.h>
using namespace std;
char c[55][55];
int u[55][55],d[55][55],l[55][55],r[55][55];
int q[26000005],qr,f[10002][3500];
string s;
int n,m,L;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j)cin>>c[i][j];
    }
    cin>>s;
    s+="*";
    L=s.size();
    for(int i=1;i<=m;++i)u[1][i]=d[n][i]=-1;
    for(int i=1;i<=n;++i)l[i][1]=r[i][m]=-1;
    for(int i=1;i<=n;++i){
        for(int j=2;j<=m;++j)l[i][j]=(c[i][j]==c[i][j-1]?l[i][j-1]:(i<<6)+j-1);
    }
    for(int i=2;i<=n;++i){
        for(int j=1;j<=m;++j)u[i][j]=(c[i][j]==c[i-1][j]?u[i-1][j]:((i-1)<<6)+j);
    }
    for(int i=1;i<=n;++i){
        for(int j=m-1;j;--j)r[i][j]=(c[i][j]==c[i][j+1]?r[i][j+1]:(i<<6)+j+1);
    }
    for(int i=n-1;i;--i){
        for(int j=1;j<=m;++j)d[i][j]=(c[i][j]==c[i+1][j]?d[i+1][j]:((i+1)<<6)+j);
    }
    memset(f,-1,sizeof(f));
    f[0][65]=0;
    q[++qr]=(1<<6)+1;
    for(int ql=1;ql<=qr;++ql){
        int i=q[ql]>>12,x=(q[ql]>>6)&63,y=q[ql]&63;
        int o=f[i][(x<<6)+y]+1;
        if(i==L){
            printf("%d\n",o-1);
            return 0;
        }
        if(s[i]==c[x][y]){
            int _=q[ql]+(1<<12);
            if(f[i+1][(x<<6)+y]==-1){
                f[i+1][(x<<6)+y]=o;
                q[++qr]=_;
            }
        }
        if(l[x][y]!=-1){
            int _=(i<<12)+l[x][y];
            if(f[i][l[x][y]]==-1){
                f[i][l[x][y]]=o;
                q[++qr]=_;
            }
        }
        if(r[x][y]!=-1){
            int _=(i<<12)+r[x][y];
            if(f[i][r[x][y]]==-1){
                f[i][r[x][y]]=o;
                q[++qr]=_;
            }
        }
        if(u[x][y]!=-1){
            int _=(i<<12)+u[x][y];
            if(f[i][u[x][y]]==-1){
                f[i][u[x][y]]=o;
                q[++qr]=_;
            }
        }
        if(d[x][y]!=-1){
            int _=(i<<12)+d[x][y];
            if(f[i][d[x][y]]==-1){
                f[i][d[x][y]]=o;
                q[++qr]=_;
            }
        }
    }
}