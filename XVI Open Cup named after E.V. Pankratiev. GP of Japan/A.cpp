#include<bits/stdc++.h>
#define ll      long long
#define mp      make_pair
#define pb      push_back
using namespace std;
int n,m,f[100005],g[100005],a[100005],F[500005],x[200005],y[200005],N,G[500005];
vector<int> v[100005],c[100005];
map<pair<int,int>,int> M;
ll ans;
int get(int x){return x==F[x]?x:F[x]=get(F[x]);}
int main(){
    scanf("%d",&n);
    N=n;
    for(int i=1;i<=n;++i){
        scanf("%d",a+i);
        c[a[i]].pb(i);
        F[i]=i;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i){
        scanf("%d%d",x+i,y+i);
        v[x[i]].pb(y[i]);
        v[y[i]].pb(x[i]);
    }
    for(int i=1;i<=m;++i){
        if(a[x[i]]==a[y[i]]){
            if(get(x[i])!=get(y[i]))F[F[x[i]]]=F[y[i]];
            continue;
        }
        int X,Y;
        if(M.count(mp(x[i],a[y[i]])))X=M[mp(x[i],a[y[i]])];
        else ++N,F[N]=N,M[mp(x[i],a[y[i]])]=N,X=N;
        if(M.count(mp(y[i],a[x[i]])))Y=M[mp(y[i],a[x[i]])];
        else ++N,F[N]=N,M[mp(y[i],a[x[i]])]=N,Y=N;
        if(get(X)!=get(y[i]))F[F[X]]=F[y[i]];
        if(get(Y)!=get(x[i]))F[F[Y]]=F[x[i]];
    }
    for(int _=1;_<=100000;++_){
        for(int i=0;i<c[_].size();++i){
            int x=c[_][i];
            f[x]=g[x];
            for(int j=0;j<v[x].size();++j)f[x]=max(f[x],g[v[x][j]]);
            ++f[x];
            get(x);
            G[F[x]]=max(G[F[x]],f[x]);
        }
        for(int i=0;i<c[_].size();++i){
            int x=c[_][i];
            f[x]=G[F[x]];
        }
        for(int i=0;i<c[_].size();++i){
            int x=c[_][i];
            for(int j=0;j<v[x].size();++j)g[v[x][j]]=max(f[x],g[v[x][j]]);
        }
    }
    for(int i=1;i<=n;++i)ans+=f[i];
    cout<<ans<<endl;
    return 0;
}