#include<bits/stdc++.h>
#define pb    push_back
#define mp    make_pair
typedef long long     ll;
using namespace std;
int n,xs[100005],ys[100005],xe[100005],ye[100005],_x,_y,f[100005],s[100005];
int x[100005],y[100005],z[100005];
map<pair<int,int>,int> m;
int get(int x){
    if(f[x]==x) return x;
    return get(f[x]);
}
void un(int i,int j){
    if(s[i]<s[j])swap(i,j);
    s[i]+=s[j];
    f[j]=i;
    if(z[j]<z[i])x[i]=x[j],y[i]=y[j],z[i]=z[j];
}
//
struct T{int l,r,x[2],d[2],k[2];}t[100005];
double K[2];
int D,r=1;
int ans,ans2;
bool cmp(T x,T y){return x.k[D]==y.k[D]?x.k[D^1]<y.k[D^1]:x.k[D]<y.k[D];}
void umx(int &x,int y){if(y>x)x=y;};
void umn(int &x,int y){if(y<x)x=y;};
void upd(int k){
    t[k].x[0]=t[k].d[0]=t[k].k[0];
    t[k].x[1]=t[k].d[1]=t[k].k[1];
    if(t[k].l){
        umn(t[k].x[0],t[t[k].l].x[0]);
        umn(t[k].x[1],t[t[k].l].x[1]);
        umx(t[k].d[0],t[t[k].l].d[0]);
        umx(t[k].d[1],t[t[k].l].d[1]);
    }
    if(t[k].r){
        umn(t[k].x[0],t[t[k].r].x[0]);
        umn(t[k].x[1],t[t[k].r].x[1]);
        umx(t[k].d[0],t[t[k].r].d[0]);
        umx(t[k].d[1],t[t[k].r].d[1]);
    }
}
int build(int l,int r,int d){
    int m=(l+r)>>1;
    D=d;
    nth_element(t+l+1,t+m+1,t+r+1,cmp);
    if(l<m)t[m].l=build(l,m-1,d^1);
    if(m<r)t[m].r=build(m+1,r,d^1);
    upd(m);
    return m;
}
void ins(int k){
    int o=r,d=0;
    while(1){
        umn(t[o].x[0],t[k].x[0]);
        umn(t[o].x[1],t[k].x[1]);
        umx(t[o].d[0],t[k].d[0]);
        umx(t[o].d[1],t[k].d[1]);
        if(mp(t[k].k[d],t[k].k[d^1])<mp(t[o].k[d],t[o].k[d^1])){
            if(!t[o].l){t[o].l=k;return;}
            else o=t[o].l;
        }
        else{
            if(!t[o].r){t[o].r=k;return;}
            else o=t[o].r;
        }
        d^=1;
    }
}
int as(int x){return x<0?-x:x;}
double pw(double x){return x*x;}
int gd(int k){
    int X=0,Y=0;
    if(t[k].x[0]>K[0])X=t[k].x[0]-K[0];
    else if(t[k].d[0]<K[0])X=K[0]-t[k].k[0];
    if(t[k].x[1]>K[1])Y=t[k].x[1]-K[1];
    else if(t[k].d[1]<K[1])Y=K[1]-t[k].k[1];
    return as(X)+as(Y);
}
void ask(int k){
    int _=as(t[k].k[0]-K[0])+as(t[k].k[1]-K[1]);
    if(_<ans){
        ans=_;
        ans2=k;
    }
    int dl=1000000007,dr=1000000007;
    if(t[k].l)dl=gd(t[k].l);
    if(t[k].r)dr=gd(t[k].r);
    if(dl<dr){
        if(dl<ans)ask(t[k].l);
        if(dr<ans)ask(t[k].r);
    }
    else{
        if(dr<ans)ask(t[k].r);
        if(dl<ans)ask(t[k].l);
    }
}
pair<int,int> p[100005];
vector<pair<int,int> >v;
int P;
int main(){
    scanf("%d%d%d",&n,&_x,&_y);
    for(int i=1;i<=n;++i){
        scanf("%d%d%d%d",xs+i,ys+i,xe+i,ye+i);
        xs[i]-=_x,xe[i]-=_x;
        ys[i]-=_y,ye[i]-=_y;
    }
    for(int i=1;i<=n;++i){
        if(xs[i]==xe[i]){
            if(ys[i]*1ll*ye[i]<=0)x[i]=xs[i],y[i]=0,z[i]=abs(x[i]);
            else if(abs(ys[i])<abs(ye[i]))x[i]=xs[i],y[i]=ys[i],z[i]=abs(x[i])+abs(y[i]);
            else x[i]=xs[i],y[i]=ye[i],z[i]=abs(x[i])+abs(y[i]);
        }
        else{
            if(xs[i]*1ll*xe[i]<=0)y[i]=ys[i],x[i]=0,z[i]=abs(y[i]);
            else if(abs(xs[i])<abs(xe[i]))y[i]=ys[i],x[i]=xs[i],z[i]=abs(x[i])+abs(y[i]);
            else y[i]=ys[i],x[i]=xe[i],z[i]=abs(x[i])+abs(y[i]);
        }
    }
    for(int i=1;i<=n;++i)f[i]=i,s[i]=1;
    for(int i=1;i<=n;++i){
        int k;
        k=m[mp(xs[i],ys[i])];
        if(!k)m[mp(xs[i],ys[i])]=i;
        else{
            if(get(k)!=get(i))un(i,k);
        }
        k=m[mp(xe[i],ye[i])];
        if(!k)m[mp(xe[i],ye[i])]=i;
        else{
            if(get(k)!=get(i))un(i,k);
        }
    }
    for(int i=1;i<=n;++i)if(get(i)==i)p[++P]=mp(z[i],i);
    sort(p+1,p+P+1);
    ll A=0;
    for(int i=1;i<=n;++i){
        ans=z[i],ans2=1;
        K[0]=t[i+1].x[0]=t[i+1].d[0]=t[i+1].k[0]=x[p[i].second];
        K[1]=t[i+1].x[1]=t[i+1].d[1]=t[i+1].k[1]=y[p[i].second];
        ask(r);
        if(ans)A+=ans,v.pb(mp(i,ans2));
        if(!(i&16384)){
            for(int j=1;j<=i;++j)t[j].l=t[j].r=0,upd(j);
            r=build(1,i+1,0);
        }
        else ins(i+1);
    }
    printf("%d %lld\n",v.size(),A);
    for(int i=0;i<v.size();++i){
        int p=v[i].first,q=v[i].second;
        if(t[p].k[0]==t[q].k[0]||t[p].k[1]==t[q].k[1])printf("2 %d %d\n",t[p].k[0],t[p].k[1],t[q].k[0],t[q].k[1]);
        else printf("3 %d %d %d %d %d %d\n",t[p].k[0],t[p].k[1],t[p].k[0],t[q].k[1],t[q].k[0],t[q].k[1]);
    }
    return 0;
}