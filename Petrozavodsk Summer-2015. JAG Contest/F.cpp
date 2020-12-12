#include<bits/stdc++.h>
#define MAXN 3000005
#define INF 1000000000
#define MOD 1000000009
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int n,m,fact[MAXN],invf[MAXN];
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
multiset<int> ms;
int save[MAXN],sz[MAXN];
vector<P> good,bad;
bool flag;
int cnt2,cnt3;
int p[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        sz[i]=1;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    p[x]=y;
    if(sz[x]==2) cnt2--;
    if(sz[y]==2) cnt2--;
    if(sz[x]==3) cnt3--;
    if(sz[y]==3) cnt3--;
    sz[y]+=sz[x];
    if(sz[y]==2) cnt2++;
    if(sz[y]==3) cnt3++;
    if(sz[y]>3) flag=false;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=3000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[3000000]=pow_mod(fact[3000000],MOD-2);
    for(int i=2999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    save[0]=1;
    for(int i=3;i<=3000000;i+=3) save[i]=1LL*save[i-3]*comb(i,3)%MOD;
    scanf("%d%d",&n,&m);
    init(3*n);
    for(int i=0;i<m;i++)
    {
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        if(c==0) good.push_back(P(u,v)); else bad.push_back(P(u,v));
    }
    int siz=(int)bad.size();
    int ans=0;
    for(int i=0;i<(1<<siz);i++)
    {
        cnt2=cnt3=0;
        flag=true;
        for(auto p:good) unite(p.F,p.S);
        for(int j=0;j<siz;j++) if(i&(1<<j)) unite(bad[j].F,bad[j].S);
        if(flag)
        {
            int fv=3*n-3*cnt3-2*cnt2,res=1;
            if(fv<cnt2) res=0;
            else for(int j=0;j<cnt2;j++) res=1LL*res*fv%MOD,fv--;
            if(fv>=0) { res=1LL*res*save[fv]%MOD; res=1LL*res*invf[fv/3]%MOD;}
            if(__builtin_popcount(i)&1) dec(ans,res); else add(ans,res);
        }
        for(auto q:good) {p[q.F]=q.F; p[q.S]=q.S; sz[q.F]=sz[q.S]=1;}
        for(auto q:bad) {p[q.F]=q.F; p[q.S]=q.S; sz[q.F]=sz[q.S]=1;}
    }
    printf("%d\n",ans);
}
