#include<bits/stdc++.h>
#define mp    make_pair
#define fi    first
#define se    second
using namespace std;
int n,q,ans[200005],t[400005],m;
pair<int,int> b[400005];
pair<pair<int,int>,int> a[400005];
int mx(int x,int y){
    return x>y?x:y;
}
void upd(int x,int k){
    while(x<=m)t[x]=max(t[x],k),x+=(x&-x);
}
int get(int x){
    int ret=0;
    while(x)ret=mx(ret,t[x]),x-=(x&-x);
    return ret;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        a[i]=mp(mp(1000000001-x,y),0);
    }
    for(int i=1;i<=q;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        a[i+n]=mp(mp(1000000001-x,y),i);
    }
    n+=q;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i)b[i]=mp(a[i].fi.se,i);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;++i){
        if(i==1||b[i].fi!=b[i-1].fi)++m;
        a[b[i].se].fi.se=m;
    }
    for(int i=1;i<=n;++i){
        int o=get(a[i].fi.se);
        if(a[i].se)ans[a[i].se]=o;
        else upd(a[i].fi.se,o+1);
    }
    for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
    return 0;
}
