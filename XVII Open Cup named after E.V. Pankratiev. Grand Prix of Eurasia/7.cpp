#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
struct E{int x,y,z;};
vector<E> v[5105];
void add(int x,int y,int z){
    E X,Y;
    X.x=y,X.y=z,X.z=v[y].size();
    Y.x=x,Y.y=0,Y.z=v[x].size();
    v[x].pb(X),v[y].pb(Y);
}
int n,m,s,t,ans;
int l[5105],i[5105],q[5105],L,R;
int dfs(int x,int y){
    if(x==t) return y;
    int ret=0;
    for(;i[x]<v[x].size();++i[x]){
        E &e=v[x][i[x]];
        if(!e.y||l[e.x]!=l[x]+1) continue;
        int d=dfs(e.x,min(y,e.y));
        if(!d) continue;
        e.y-=d,v[e.x][e.z].y+=d,ret+=d,y-=d;
        if(!y) return ret;
    }
    l[x]=-1;
    return ret;
}
int N,a[105],sm[5105];
char c[105][105];
int main(){
    cin>>N;
    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j)cin>>c[i][j];
    }
    for(int i=1;i<=N;++i)cin>>a[i];
    n=N;
    for(int i=1;i<=N;++i){
        for(int j=i+1;j<=N;++j){
            ++n;
            sm[n]=i+j;
            if(c[i][j]=='.')add(i,n,3),add(j,n,3);
            else if(c[i][j]=='W')a[i]-=3;
            else if(c[i][j]=='w')a[i]-=2,a[j]-=1;
            else if(c[i][j]=='l')a[i]-=1,a[j]-=2;
            else a[j]-=3;
        }
    }
    s=n+1,t=n+2;
    for(int i=1;i<=N;++i)if(a[i])add(s,i,a[i]);
    for(int i=N+1;i<=n;++i)add(i,t,3);
    n+=2;
    while(1){
        memset(i,0,sizeof(i));
        memset(l,-1,sizeof(l));
        l[s]=0,L=0,R=1,q[1]=s;
        while(L!=R){
            int x=q[++L];
            for(int i=0;i<v[x].size();++i){
                if(v[x][i].y&&l[v[x][i].x]==-1)l[v[x][i].x]=l[x]+1,q[++R]=v[x][i].x;
            }
        }
        if(l[t]==-1) break;
        ans+=dfs(s,orz);
    }
    for(int i=1;i<=N;++i){
        for(int j=0;j<v[i].size();++j){
            int x=v[i][j].x;
            if(x>=s) continue;
            x=sm[x]-i;
            if(v[i][j].y==3)c[i][x]='L';
            else if(v[i][j].y==2)c[i][x]='l';
            else if(v[i][j].y==1)c[i][x]='w';
            else c[i][x]='W';
        }
    }
    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j)cout<<c[i][j];
        cout<<endl;
    }
    return 0;
}