#include<bits/stdc++.h>
#define mp   make_pair
#define pb   push_back
using namespace std;
typedef long long ll;
int n,m,x[100005],y[100005],d[100005],lv[100005],c,S,T,st[400005],tt;
bool b[400005];
int la[400005],le[400005];
ll D[400005];
vector<int> lst[100005];
vector<int> v[400005],e[400005],f[400005];
map<pair<int,int>,int> M;
priority_queue<pair<ll,int> >q;
void add(int x,int y,int d,int i){
    v[x].pb(y);
    e[x].pb(d);
    f[x].pb(i);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        scanf("%d%d%d%d",x+i,y+i,d+i,lv+i);
        if(x[i]==2||x[i]==n)x[i]=n+2-x[i];
        if(y[i]==2||y[i]==n)y[i]=n+2-y[i];
        lst[x[i]].pb(lv[i]);
        lst[y[i]].pb(lv[i]);
        int X=M[mp(x[i],lv[i])],Y=M[mp(y[i],lv[i])];
        if(!X)M[mp(x[i],lv[i])]=X=++c;
        if(!Y)M[mp(y[i],lv[i])]=Y=++c;
        add(X,Y,d[i],i);
        add(Y,X,d[i],i);
        x[i]=n*2-x[i],y[i]=n*2-y[i];
        X=M[mp(x[i],lv[i])],Y=M[mp(y[i],lv[i])];
        if(!X)M[mp(x[i],lv[i])]=X=++c;
        if(!Y)M[mp(y[i],lv[i])]=Y=++c;
        add(X,Y,d[i],i);
        add(Y,X,d[i],i);
    }
    for(int i=1;i<=n;++i)sort(lst[i].begin(),lst[i].end());
    for(int i=1;i<=n;++i){
        if(!lst[i].size()) continue;
        int k=lst[i][0];
        for(int j=1;j<lst[i].size();++j){
            if(lst[i][j]==lst[i][j-1]) continue;
            add(M[mp(i,lst[i][j])],M[mp(i,k)],0,0);
            add(M[mp(n*2-i,lst[i][j])],M[mp(n*2-i,k)],0,0);
            k=lst[i][j];
        }
    }
    memset(D,-1,sizeof(D));
    S=M[mp(1,lst[1][((int)lst[1].size())-1])];
    T=M[mp(2*n-1,lst[1][0])];
    D[S]=0;
    q.push(mp(0,S));
    while(!q.empty()){
        int x=q.top().second;
        ll y=-q.top().first;
        q.pop();
        if(b[x]) continue;
        b[x]=1;
        for(int i=0;i<v[x].size();++i){
            int z=v[x][i];
            if(D[z]==-1||D[z]>y+e[x][i]){
                D[z]=y+e[x][i];
                la[z]=x;
                le[z]=f[x][i];
                q.push(mp(-D[z],z));
            }
        }
    }
    printf("%lld\n",D[T]);
    int x=T;
    while(x!=S){
        if(le[x])st[++tt]=le[x];
        x=la[x];
    }
    for(int i=1;i<tt;++i)printf("%d ",st[i]);
    printf("%d\n",st[tt]);
    return 0;
}