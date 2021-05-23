#include<bits/stdc++.h>
#define mp    make_pair
using namespace std;
mt19937 r(time(NULL));
int n,ax,ay,bx,by,x[100005],y[100005],f[3005][3005],g[3005][3005];
pair<int,int> p[100005],q[100005];
int P,Q;
bool ok(){
    int i=1,j=1;
    while(i<=P&&j<=Q){
        if(p[i]==q[j]) return 1;
        if(p[i]<q[j])++i;
        else ++j;
    }
    return 0;
}
int main(){
    scanf("%d%d%d%d%d",&n,&ax,&ay,&bx,&by);
    for(int i=1;i<=n;++i)scanf("%d%d",x+i,y+i);
    for(int i=1;i<=n;++i){
        int X=ax+x[i],Y=ay+y[i];
        if(X>0&&Y>0&&X<=n&&Y<=n)p[++P]=mp(X,Y);
        X=bx-x[i],Y=by-y[i];
        if(X>0&&Y>0&&X<=n&&Y<=n)q[++Q]=mp(X,Y);
    }
    q[++Q]=mp(bx,by);
    sort(p+1,p+P+1);
    sort(q+1,q+Q+1);
    if(ok()){
        printf("Alice wins\n");
        return 0;
    }
    if(n<=3000){
        for(int i=0;i<=n;++i){
            int X=bx+x[i],Y=by+y[i];
            if(X>0&&Y>0&&X<=n&&Y<=n)f[X][Y]=1;
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(f[i][j]){
                    g[i][j]=1;
                    for(int k=1;k<=n;++k){
                        int X=i+x[k],Y=j+y[k];
                        if(X>0&&Y>0&&X<=n&&Y<=n)g[X][Y]=1;
                    }
                }
            }
        }
        g[ax][ay]=1;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(!g[i][j]){
                    printf("tie %d %d\n",i,j);
                    return 0;
                }
            }
        }
        printf("Bob wins\n");
        return 0;
    }
    p[P=1]=mp(bx,by);
    for(int i=1;i<=n;++i){
        int X=bx+x[i],Y=by+y[i];
        if(X>0&&Y>0&&X<=n&&Y<=n)p[++P]=mp(X,Y);
    }
    sort(p+1,p+P+1);
    for(int _=10000000/n;_;--_){
        int xx=r()%n+1,yy=r()%n+1;
        if(xx==ax&&yy==ay) continue;
        q[Q=1]=mp(xx,yy);
        for(int i=1;i<=n;++i){
            int X=xx-x[i],Y=yy-y[i];
            if(X>0&&Y>0&&X<=n&&Y<=n)q[++Q]=mp(X,Y);
        }
        sort(q+1,q+Q+1);
        if(!ok()){
            printf("tie %d %d\n",xx,yy);
            return 0;
        }
    }
    printf("Bob wins\n");
    return 0;
}