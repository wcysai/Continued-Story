#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
using namespace std;
ll orz=1000000ll*10000000ll;
int n,w,u,v,t1,t2,m,s;
ll la=orz,ans;
pair<ll,int> p[2000015];
int main(){
    scanf("%d%d%d%d%d%d",&n,&w,&u,&v,&t1,&t2);
    p[++m]=mp(-orz,-1);
    p[++m]=mp(t1*u*1ll*v,1);
    p[++m]=mp(t2*u*1ll*v,-1);
    for(int I=1;I<=n;++I){
        char c;
        int k;
        scanf(" %c%d",&c,&k);
        if(c=='E'){
            for(int i=1;i<=k;++i){
                int l,x;
                scanf("%d%d",&l,&x);
                p[++m]=mp(-x*v-u*(I)*1ll*w,-1);
                p[++m]=mp(-(x-l)*v-u*(I-1)*1ll*w,1);
            }
        }
        else{
            for(int i=1;i<=k;++i){
                int l,x;
                scanf("%d%d",&l,&x);
                p[++m]=mp(x*v-u*(I)*1ll*w,-1);
                p[++m]=mp((x+l)*v-u*(I-1)*1ll*w,1);
            }
        }
    }
    sort(p+1,p+m+1);
    for(int i=1;i<=m;++i){
        s+=p[i].second;
        if(i<m&&p[i].first==p[i+1].first) continue;
        ans=max(ans,p[i].first-la);
        if(s)la=orz;
        else if(la==orz)la=p[i].first;
    }
    printf("%.10lf\n",ans*1.0/u/v);
    return 0;
}