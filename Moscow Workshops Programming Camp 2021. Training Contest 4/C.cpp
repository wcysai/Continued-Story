#include<bits/stdc++.h>
#define mp     make_pair
#define fi     first
#define se     second
#define ll     long long
using namespace std;
int w,h,n,x[100006],y[100005],a,b;
pair<int,int> px[100005],py[100005],p[100005];
int main(){
//freopen("C.in","r",stdin);
    scanf("%d%d",&w,&h);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d%d",x+i,y+i);
    scanf("%d",&a);
    for(int i=1;i<=a;++i)scanf("%d%d",&px[i].fi,&px[i].second);
    sort(px+1,px+a+1);
    scanf("%d",&b);
    for(int i=1;i<=b;++i)scanf("%d%d",&py[i].se,&py[i].fi);
    sort(py+1,py+b+1);
    for(int i=1;i<=n;++i){
        int o=0;
        for(int _=17;_>=0;--_){
            int O=o+(1<<_);
            if(O>a) continue;
            if(w*1ll*y[i]>px[O].fi*1ll*(w-x[i])+x[i]*1ll*px[O].se)o=O;
        }
        p[i].fi=o;
        o=0;
        for(int _=17;_>=0;--_){
            int O=o+(1<<_);
            if(O>b) continue;
            if(h*1ll*x[i]>py[O].fi*1ll*(h-y[i])+y[i]*1ll*py[O].se)o=O;
        }
        p[i].se=o;
    }
    sort(p+1,p+n+1);
    int cnt=1,ans=1;
    for(int i=2;i<=n;++i){
        if(p[i]==p[i-1])++cnt;
        else ans=max(ans,cnt),cnt=1;
    }
    printf("%d\n",max(ans,cnt));
    return 0;
}