#include<bits/stdc++.h>
#define pb    push_back
#define mp    make_pair
using namespace std;
int n,m,cnt[200005],f[200005],ans;
vector<int> v[200005];
queue<int> q;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        ++x,++y;
        v[x].pb(y),v[y].pb(x);
        ++cnt[x],++cnt[y];
    }
    for(int i=1;i<=n+m;++i)if(cnt[i]==1)q.push(i);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        if(!f[x]){
            for(int i=0;i<v[x].size();++i){
                int y=v[x][i];
                if(cnt[y]>1){
                    --cnt[y];
                    f[y]=1;
                    if(cnt[y]==1)q.push(y);
                }
            }
        }
        else{
            for(int i=0;i<v[x].size();++i){
                int y=v[x][i];
                if(cnt[y]>1){
                    --cnt[y];
                    if(cnt[y]==1)q.push(y);
                }
            }
        }
    }
    for(int i=1;i<=n+m;++i)ans+=f[i];
    int ok=0;
    for(int i=1;i<=n;++i)if(f[i])ok=i;
    if(!ok){
        printf("%d\n",ans+(n+1)/2);
        return 0;
    }
    int cnt=0;
    for(int i=ok+1;i!=ok;i=i%n+1){
        if(!f[i])++cnt;
        else ans+=cnt/2,cnt=0;
    }
    printf("%d\n",ans+cnt/2);
    return 0;
}