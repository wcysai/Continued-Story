#include<bits/stdc++.h>
#define I   insert
#define mp     make_pair
using namespace std;
int n,l[1000005],r[1000005],l2[1000005],r2[1000005],f[1000005],t[1000005],b[1000005];
set<pair<int,int> >s[1000005];
void add(int x){while(x<=n)++t[x],x+=(x&-x);}
int sum(int x){int s=0;while(x)s+=t[x],x&=(x-1);return s;}
int F(int x){return x==f[x]?x:f[x]=F(f[x]);}
int sol(){
    for(int i=1;i<=n;++i)f[i]=i;
    memset(t,0,sizeof(t));
    for(int i=1;i<=n;++i)s[i].clear();
    for(int i=1;i<=n;++i)s[l[i]].insert(mp(r[i],i));
    for(int i=1;i<=n;++i){
        int k=F(i);
        if(s[k].empty()) return 0;
        pair<int,int> p=*s[k].begin();
        s[k].erase(p);
        if(p.first<i) return 0;
        if(p.first<n){
            int K=F(p.first+1);
            if(s[K].size()<s[k].size())swap(k,K);
            f[k]=K;
            for(set<pair<int,int> >::iterator it=s[k].begin();it!=s[k].end();++it)s[K].insert(*it);
        }
        b[i]=p.second;
    }
    long long ans=0;
    for(int i=1;i<=n;++i){
        ans+=sum(b[i]);
        add(b[i]);
    }
    if(ans&1) return -1;
    return 1;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d%d%d%d",l+i,r+i,l2+i,r2+i);
    int ans=sol();
    for(int i=1;i<=n;++i)l[i]=l2[i],r[i]=r2[i];
    ans*=sol();
    printf("%d\n",ans);
    return 0;
}
