#include<bits/stdc++.h>
#define ll    long long
#define pb    push_back
#define mp    make_pair
using namespace std;
int K,cnt,n,q;
map<pair<int,int>,int> M;
bitset<2002> b[1005];
vector<int> v[1005];
int main(){
    scanf("%d",&K);
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        char c=getchar();
        ll x=0,y=0;
        while(c<'A')c=getchar();
        int o=0;
        while(c>='A'){
            ++o;
            if(c<'a')c+='a'-'A',b[i][o]=1;
            x=(x*2333+c)%1000000007;
            y=(y*40009+c)%998244353;
            c=getchar();
        }
        pair<int,int> p=mp(x,y);
        if(!M[p])M[p]=++cnt;
        v[M[p]].pb(i);
    }
    scanf("%d",&q);
    while(q--){
        char c=getchar();
        ll x=0,y=0;
        while(c<'A')c=getchar();
        int o=0;
        bitset<2002> B;
        while(c>='A'){
            ++o;
            if(c<'a')c+='a'-'A',B[o]=1;
            x=(x*2333+c)%1000000007;
            y=(y*40009+c)%998244353;
            c=getchar();
        }
        pair<int,int> p=mp(x,y);
        if(!M.count(p)){
            printf("0\n");
            continue;
        }
        o=M[p];
        int ans=0;
        for(int i=0;i<v[o].size();++i)if((b[v[o][i]]^B).count()<=K)++ans;
        printf("%d\n",ans);
    }
    return 0;
}