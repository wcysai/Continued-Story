#include<bits/stdc++.h>
#define pb    push_back
#define mp    make_pair
#define fi    first
#define se    second
using namespace std;
int n,x[500005],y[500005],z[500005],u[500005],D;
int st[500005],S,mk[500005],out[500005],res;
bool ok,ban[500005],o[500005];
vector<pair<int,int> > v[500005];
vector<int> e[500005];
void add(int y,int x,int z){
    if(mk[z]&&mk[z]!=x){
        puts("-1");
        exit(0);
    }
    if(!mk[z]){
        mk[z]=x;
        e[x].pb(y);
    }
}
void gen(int x,int y){
    ban[st[++S]=x]=1;
    for(int i=0;i<e[x].size();++i)if(e[x][i]!=y)gen(e[x][i],x);
}
pair<int,int> chk(int x,int y){
    pair<int,int> p=mp(x,x);
    bool l=0,r=0;
    for(int i=0;i<v[x].size();++i){
        if(v[x][i].fi==y) continue;
        pair<int,int> P=chk(v[x][i].fi,x);
        if(P.fi<x&&P.se>x)ok=0;
        if(P.fi<x){
            if(l)ok=0;
            else l=1;
        }
        if(P.se>x){
            if(r)ok=0;
            else r=1;
        }
        p.fi=min(P.fi,p.fi);
        p.se=max(P.se,p.se);
    }
    return p;
}
int dfs(int x,int y){
    for(int i=0;i<e[x].size();++i)if(e[x][i]!=y) return dfs(e[x][i],x);
    return x;
}
int main(){
    scanf("%d",&n);
    if(n==1){
        puts("1");
        return 0;
    }
    for(int i=1;i<n;++i){
        scanf("%d%d",x+i,y+i);
        ++z[x[i]];
        ++z[y[i]];
        if(x[i]<y[i])++u[x[i]];
        else ++u[y[i]];
        v[x[i]].pb(mp(y[i],i));
        v[y[i]].pb(mp(x[i],i));
    }
    for(int i=1;i<=n;++i)D=max(D,z[i]);
    if(D>3){
        puts("-1");
        return 0;
    }
    if(D==3){
        for(int i=1;i<=n;++i){
            if(z[i]!=3) continue;
            if(u[i]==0||u[i]==3){
                puts("-1");
                return 0;
            }
            sort(v[i].begin(),v[i].end());
            if(u[i]==1){
                add(v[i][0].fi,i,v[i][0].se);
                add(i,v[i][1].fi,v[i][1].se);
                add(i,v[i][2].fi,v[i][2].se);
            }
            else{
                add(v[i][2].fi,i,v[i][2].se);
                add(i,v[i][1].fi,v[i][1].se);
                add(i,v[i][0].fi,v[i][0].se);
            }
        }
        for(int i=1;i<n;++i)if(!mk[i])e[x[i]].pb(y[i]),e[y[i]].pb(x[i]);
        for(int i=1;i<=n;++i){
            if(z[i]==3){
                int x=dfs(i,0);
                gen(x,0);
                ok=1;
                pair<int,int> p=mp(n+1,0);
                for(int j=0;j<v[st[1]].size();++j)if(!ban[v[st[1]][j].fi])p=chk(v[st[1]][j].fi,st[1]);
                int O=0;
                for(int j=1;j<=S;++j){
                    if(p.fi<=st[j]&&p.se>=st[j])O=1;
                    if(O)o[j]=1;
                    p.fi=min(p.fi,st[j]);
                    p.se=max(p.se,st[j]);
                }
                p=mp(n+1,0);
                for(int j=0;j<v[st[S]].size();++j)if(!ban[v[st[S]][j].fi])p=chk(v[st[S]][j].fi,st[S]);
                O=0;
                for(int j=S;j;--j){
                    if(p.fi<=st[j]&&p.se>=st[j])O=1;
                    if(O)o[j]=1;
                    p.fi=min(p.fi,st[j]);
                    p.se=max(p.se,st[j]);
                }
                if(!ok){
                    puts("-1");
                    return 0;
                }
                break;
            }
        }
    }
    else{
        for(int i=1;i<n;++i)e[x[i]].pb(y[i]),e[y[i]].pb(x[i]);
        for(int i=1;i<=n;++i){
            if(z[i]==1){
                gen(i,0);
                break;
            }
        }
        pair<int,int> p=mp(n+1,0);
        int O=0;
        for(int j=1;j<=S;++j){
            if(p.fi<=st[j]&&p.se>=st[j])O=1;
            if(O)o[j]=1;
            p.fi=min(p.fi,st[j]);
            p.se=max(p.se,st[j]);
        }
        p=mp(n+1,0);
        O=0;
        for(int j=S;j;--j){
            if(p.fi<=st[j]&&p.se>=st[j])O=1;
            if(O)o[j]=1;
            p.fi=min(p.fi,st[j]);
            p.se=max(p.se,st[j]);
        }
    }
    if(S==1){
        ok=1;
        chk(st[1],0);
        if(ok)printf("%d\n",st[1]);
        else puts("-1");
        return 0;
    }
    for(int i=1;i<=S;++i){
        if(u[st[i]]>1) o[i]=1;
        if(z[st[i]]-u[st[i]]>1) o[i]=1;
    }
    for(int i=1;i<=S;++i)if(!o[i])out[++res]=st[i];
    if(!res)puts("-1");
    else{
        sort(out+1,out+res+1);
        for(int i=1;i<res;++i)printf("%d ",out[i]);
        printf("%d\n",out[res]);
    }
    return 0;
}