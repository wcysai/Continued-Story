#include<bits/stdc++.h>
#define mp     make_pair
#define pb     push_back
using namespace std;
int n,a[100005],b[100005],u[100005];
vector<pair<int,int> > vx,vy;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",a+i);
    for(int i=1;i<=n;++i){
        if(u[i]) continue;
        if(a[i]==i) continue;
        int k=0;
        for(int x=i;!u[x];x=a[x]){
            u[x]=1;
            b[++k]=x;
        }
        if(k==2)vx.pb(mp(b[1],b[2]));
        else{
            for(int i=1;i<k;++i){
                int j=k-i;
                if(i<j)vx.pb(mp(b[i],b[j]));
            }
            for(int i=1;i<=k;++i){
                int j=k+1-i;
                if(i<j)vy.pb(mp(b[i],b[j]));
            }
        }
    }
    if(vx.empty()){
        printf("0\n");
        return 0;
    }
    if(vy.empty()){
        printf("1\n");
        printf("%d",(int)vx.size());
        for(int i=0;i<vx.size();++i)printf(" %d %d",vx[i].first,vx[i].second);
        printf("\n");
        return 0;
    }
        printf("2\n");
        printf("%d",(int)vx.size());
        for(int i=0;i<vx.size();++i)printf(" %d %d",vx[i].first,vx[i].second);
        printf("\n");
        printf("%d",(int)vy.size());
        for(int i=0;i<vy.size();++i)printf(" %d %d",vy[i].first,vy[i].second);
        printf("\n");
    return 0;
}