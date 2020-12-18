#include<bits/stdc++.h>
#define ll      long long
using namespace std;
int n,L,d[55],h[55];
int L2,D[55][55],D2[55][55],H[55][55],H2[55][55],mh[55][55];
double f[105],c1[55][55],c2[55][55],l1[55][55],l2[55][55];
int main(){
    scanf("%d%d",&n,&L);
    for(int i=1;i<=n;++i)scanf("%d",d+i);
    for(int i=1;i<=n;++i)scanf("%d",h+i);
    L2=L*L;
    for(int i=0;i<=n;++i){
        for(int j=0;j<=n;++j)D[i][j]=d[i]-d[j],D2[i][j]=D[i][j]*D[i][j];
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)H[i][j]=h[i]-h[j],H2[i][j]=H[i][j]*H[i][j];
    }
    for(int i=1;i<=n;++i){
        mh[i][i]=h[i];
        for(int j=i+1;j<=n;++j)mh[i][j]=max(mh[i][j-1],h[j]);
    }
    for(int i=2;i<=n*2;++i)f[i]=1e9;
    for(int i=1;i<n;++i){
        for(int j=i+1;j<=n;++j)c1[i][j]=c2[i][j]=1e9;
    }
    for(int x=1;x<=n;++x){
         for(int y=x+1;y<=n;++y){
            if(mh[x][y-1]>=h[y]) continue;
            int _=H2[y][x];
            if(_+D2[y-1][x]>L2) continue;
            if(L2>_+D2[y-1][x-1]) continue;
            bool ok=1;
            int __=L2-_;
            for(int i=x+1;i<y;++i){
                if(__*1ll*H2[y][i]<=_*1ll*D2[y-1][i-1]){
                    ok=0;
                    break;
                }
            }
            if(ok){
                c1[x][y]=-sqrt(__*1.0)+D[y-1][x-1];
                l1[x][y]=D2[y-1][x]+H2[y][x];
                for(int i=x+1;i<y;++i){
                    l1[x][y]=max(l1[x][y],_*1.0*(H2[y][i]+D2[y-1][i-1])/(H2[y][i]*1.0));
                }
            }
        }
        for(int y=x+1;y<=n;++y){
            if(mh[x+1][y]>=h[x]) continue;
            int _=H2[y][x];
            if(_+D2[y-1][x]>L2) continue;
            if(L2>_+D2[y][x]) continue;
            bool ok=1;
            int __=L2-_;
            for(int i=x+1;i<y;++i){
                if(__*1ll*H2[x][i]<=_*1ll*D2[i][x]){
                    ok=0;
                    break;
                }
            }
            if(ok){
                c2[x][y]=-sqrt(__*1.0)+D[y][x];
                l2[x][y]=D2[y-1][x]+H2[y][x];
                for(int i=x+1;i<y;++i){
                    l2[x][y]=max(l2[x][y],_*1.0*(H2[x][i]+D2[i][x])/(H2[x][i]*1.0));
                }
            }
        }
    }
    for(int x=1;x<=n;++x){
        f[x*2]=min(f[x*2],f[x*2-1]+d[x]-d[x-1]);
        for(int y=x+1;y<=n;++y){
            if(c1[x][y]<9e8)f[y*2-1]=min(f[y*2-1],f[x*2-1]+L+c1[x][y]);
        }
        for(int y=x+1;y<=n;++y){
            if(c2[x][y]<9e8)f[y*2]=min(f[y*2],f[x*2]+L+c2[x][y]);
        }
        for(int y=x+1;y<=n;++y){
            if(c2[x][y]>9e8) continue;
            for(int z=y+1;z<=n;++z){
                if(c1[y][z]>9e8) continue;
                f[z*2-1]=min(f[z*2-1],f[x*2]+L*2+max(0.0,c1[y][z]+c2[x][y]-D[y][y-1]));
                double l=c2[x][y]+D[z-1][y];
                l=l*l+H2[z][y];
                if(l<L2+1e-10&&l>l1[y][z]-1e-10)f[z*2-1]=min(f[z*2-1],f[x*2]+L+sqrt(l));
                l=c1[y][z]+D[y-1][x];
                if(l<L2+1e-10&&l>l2[x][y]-1e-10)f[z*2-1]=min(f[z*2-1],f[x*2]+L+sqrt(l));
            }
        }
        for(int y=x+1;y<=n;++y){
            if(h[y]!=h[x]) continue;
            if(y>x+1&&mh[x+1][y-1]>=h[x]) continue;
            if(D[y-1][x]>L) continue;
            f[y*2-1]=min(f[y*2-1],f[x*2]+D[y-1][x]);
        }
        for(int y=x+2;y<=n;++y){
            int _=D[y-1][x];
            int M=max(h[x],h[y]);
            if(mh[x+1][y-1]>=M) continue;
            for(int z=x+1;z<y;++z){
                int __=h[x]+h[y]-h[z]*2;
                int len2=_*_+__*__;
                if(len2*1ll*(M-h[z])*(M-h[z])>L2*1ll*__*__) continue;
                if(H[x][z]*_<=D[z-1][x]*__) continue;
                if(H[y][z]*_<=D[y-1][z]*__) continue;
                if(x+1<z&&mh[x+1][z-1]>=h[x]) continue;
                if(z+1<y&&mh[z+1][y-1]>=h[y]) continue;
                bool ok=1;
                for(int i=x+1;i<z&&ok;++i){
                    if(H[x][i]*_<=D[i][x]*__)ok=0;
                }
                for(int i=z+1;i<y&&ok;++i){
                    if(H[y][i]*_<=D[y-1][i-1]*__)ok=0;
                }
                if(ok)f[y*2-1]=min(f[y*2-1],f[x*2]+sqrt(len2*1.0));
            }
        }
        for(int y=x+1;y<=n;++y){
            if(mh[x][y-1]>=h[y]) continue;
            int _=H[y][x],__=D[y-1][x-1];
            if(_*_+__*__>L2) continue;
            bool ok=1;
            for(int i=x+1;i<y;++i){
                if(_*D[y-1][i-1]>=__*H[y][i]){
                    ok=0;
                    break;
                }
            }
            if(ok)f[y*2-1]=min(f[y*2-1],f[x*2-1]+sqrt(_*_+__*__*1.0));
        }
        for(int y=x+1;y<=n;++y){
            if(mh[x+1][y]>=h[x]) continue;
            int _=H[y][x],__=D[y][x];
            if(_*_+__*__>L2) continue;
            bool ok=1;
            for(int i=x+1;i<y;++i){
                if(_*D[i][x]>=__*H[x][i]){
                    ok=0;
                    break;
                }
            }
            if(ok)f[y*2]=min(f[y*2],f[x*2]+sqrt(_*_+__*__*1.0));
        }
    }
    if(f[n*2]>9e8)printf("-1\n");
    else printf("%.10lf\n",f[n*2]);
    return 0;
}