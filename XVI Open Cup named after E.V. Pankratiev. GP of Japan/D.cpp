#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int prime[MAXN],phi[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=1;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; phi[i]=i-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            phi[prime[j]*i]=(i%prime[j]?phi[i]*(prime[j]-1):phi[i]*prime[j]);
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
vector<int> pr;
int pow_mod(int a,int i,int m)
{
    a%=m;
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=1LL*a*a%m;
        i>>=1;
    }
    return s;
}
ll lcm(ll x,ll y)
{
    return 1LL*x*y/__gcd(x,y);
}
int getphi(int n)
{
    int res=n;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            res=res/i*(i-1);
            for(;n%i==0;n/=i);
        }
    }
    if(n!=1) res=res/n*(n-1);
    return res;
}
int main()
{
    int p=sieve(100000);
    scanf("%d",&n);
    bool f=true;
    int tmp=n;
    for(int i=0;i<p;i++)
    {
        if(tmp%prime[i]) continue;
        int cnt=0;
        while(tmp%prime[i]==0) tmp/=prime[i],cnt++;
        if(cnt>1) {f=false; break;}
        pr.push_back(prime[i]);
    }
    if(!f) {puts("-1"); return 0;}
    if(tmp>1) pr.push_back(tmp);
    ll k=1;
    for(auto p:pr)
    {
        if(p==2) continue;
        if(__gcd(n,p-1)>1) {f=false; break;}
        int res=INF;
        int ph=getphi(p-1);
        for(int i=1;i*i<=ph;i++)
        {
            if(ph%i) continue;
            if(pow_mod(n,i,p-1)==1) res=min(res,i); 
            if(pow_mod(n,ph/i,p-1)==1) res=min(res,ph/i); 
        }
        assert(res!=INF);
        k=lcm(k,res);
    }
    if(!f) {puts("-1"); return 0;}
    printf("%lld\n",k);
    return 0;
}