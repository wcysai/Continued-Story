#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000000000000031LL
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef unsigned long long ULL;
set<ll> factors;
int prime[MAXN],lfact[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; lfact[i]=i;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            lfact[prime[j]*i]=prime[j];
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
//to achieve best running time, sieve until 2/3 prime factors remaining
namespace pollardrho 
{
    ULL gcd(ULL a, ULL b) {return b ? gcd(b, a % b) : a;}

    ULL mulmod(ULL x,ULL y,ULL p)
    {
        __int128 tmp=(__int128)x*(__int128)y;
        return (ULL)(tmp%p);
    }

    ULL powmod(ULL b, ULL e, ULL m) 
    {
        ULL r = 1;
        while (e) 
        {
            if (e & 1) r = mulmod(r, b, m);
            b = mulmod(b, b, m);
            e >>= 1;
        }
        return r;
    }

    bool test(ULL n)
    {
        if (n < 3) return n==2;
        // ! The array a[] should be modified if the range of x changes.
        static const ULL a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23,  ULLONG_MAX};//works for 1e18
        ULL r = 0, d = n-1, x;
        while (~d & 1) d >>= 1, r++;
        for (int i=0; a[i] < n; i++)
        {
            x = powmod(a[i], d, n);
            if (x == 1 || x == n-1) goto next;
            for(int i=0;i<r;i++)
            {
                x = mulmod(x, x, n);
                if (x == n-1) goto next;
            }
            return false;
            next:;
        }
        return true;
    }

    map<ULL, int> mp;
    mt19937_64 gen(time(NULL));

}
ll is_square(ll x)
{
    ll d=(ll)sqrt(x);
    for(ll i=max(1LL,d-5);i<=d+5;i++) if(i*i==x) return i;
    return -1;
}
int n;
ll a[MAXN],b[MAXN];
int dp[MAXN];
bool valid[MAXN];
int main()
{
    int p=sieve(1000000);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%lld",&a[i]); 
        b[i]=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<p;j++) 
        {
            if(b[i]%prime[j]==0)
            {
                factors.insert(prime[j]);
                while(b[i]%prime[j]==0) b[i]/=prime[j];
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(b[i]==1) continue;
        if(pollardrho::test(b[i]))
        {
            factors.insert(b[i]);
            continue;
        }
        ll x=is_square(b[i]);
        if(x!=-1) 
        {
            factors.insert(x);
            continue;
        }
        ll g=0;
        for(int j=1;j<=n;j++)
        {
            if(j==i) continue;
            ll g=__gcd(b[i],b[j]);
            if(g>1&&g!=b[i])
            {
                factors.insert(g);
                factors.insert(b[i]/g);
                break;
            }
        }
    }
    int res=0;
    for(auto x:factors)
    {
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]%x)
            {
                res^=cnt;
                cnt=0;
            }
            else cnt++;
        }
        res^=cnt;
    }
    if(res) puts("First"); else puts("Second");
    return 0;
}