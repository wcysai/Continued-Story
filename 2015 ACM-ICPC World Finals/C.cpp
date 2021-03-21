#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int nl,nr,n,m,f[405][405],lx[405],ly[405],vx[405],vy[405],sl[405];
int q[405],ql,qr,pre[405],ml[405],mr[405],out[405];
void go(int x){
    while(1){
        ql=0,qr=1,vx[x]=1,q[1]=x;
        while(ql<qr){
            int o=q[++ql];
            for(int i=1;i<=n;++i){
                if(vy[i]) continue;
                int t=lx[o]+ly[i]-f[o][i];
                if(t>sl[i]) continue;
                pre[i]=o;
                if(!t){
                    if(!ml[i]){
                        while(i){
                            ml[i]=pre[i];
                            swap(i,mr[pre[i]]);
                        }
                        return;
                    }
                    q[++qr]=ml[i];
                    vy[i]=vx[ml[i]]=1;
                }
                else sl[i]=t;
            }
        }
        int o,O=orz;
        for(int i=1;i<=n;++i)if(!vy[i]&&O>sl[i])o=i,O=sl[i];
        for(int i=1;i<=n;++i){
            if(vx[i])lx[i]-=O;
            if(vy[i])ly[i]+=O;
            else sl[i]-=O;
        }
        if(!ml[o]){
            while(o){
                ml[o]=pre[o];
                swap(o,mr[pre[o]]);
            }
            return;
        }
        vy[o]=1,x=ml[o];
    }
}      
int N,K,a[105][105];  
int main(){
    scanf("%d%d",&N,&K);
    nl=N+K,nr=N;
    for(int i=1;i<=N;++i){
        int x;
        scanf("%d",&x);
        for(int j=N+1;j<=nl;++j)f[j][i]=orz-x;
    }
    for(int i=1;i<N;++i){
        for(int j=i+1;j<=N;++j)scanf("%d",f[i]+j),f[i][j]=orz-f[i][j];
    }
    n=max(nl,nr);
    for(int i=1;i<=nl;++i){
        for(int j=1;j<=nr;++j){
            lx[i]=max(lx[i],f[i][j]);
        }
    }
    for(int i=1;i<=n;++i){
        memset(vx,0,sizeof(vx));
        memset(vy,0,sizeof(vy));
        for(int j=1;j<=n;++j)sl[j]=orz;
        go(i);
    }
    ll ans=0;
    for(int i=1;i<=n;++i)ans+=lx[i]+ly[i];
    printf("%lld\n",orz*1ll*nr-ans);
    return 0;
}