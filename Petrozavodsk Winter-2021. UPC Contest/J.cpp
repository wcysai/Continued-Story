#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
int T;
ULL k;
vector< pair< ULL,int> > fact[3];
namespace pollardrho 
{
    ULL gcd(ULL a, ULL b) {return b ? gcd(b, a % b) : a;}

    ULL mulmod(ULL x,ULL y,ULL p)
    {
        ULL z=(long double)x/p*y;
        ULL res=(ULL)x*y-(ULL)z*p;
        return (res+p)%p;
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
        static const ULL a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23,  ULLONG_MAX};
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

    void PollardRho(ULL n) 
    {
        ULL c, x, y, d;
        while (n % 2 == 0) 
        {
            mp[2]++;
            n /= 2;
        }
        if (n == 1) return;

        if (test(n)) 
        {
            mp[n]++;
            return;
        }

        d = n;
        static int counter = 0;
        while (d == n) 
        {
            x = y = 2;
            d = 1;
            c = gen() % (n - 1) + 1;
            while (d == 1) 
            {
                counter++;
                x = (mulmod(x, x, n) + c) % n;
                y = (mulmod(y, y, n) + c) % n;
                y = (mulmod(y, y, n) + c) % n;
                d = gcd(x > y ? x - y : y - x, n);
            }
        }
        PollardRho(d);
        PollardRho(n / d);
    }

    void work(ULL n,int id) 
    {
        PollardRho(n);
        for(auto p:mp) fact[id].push_back(p);
        mp.clear();
    }
}
ULL lst[100005];
int cnt;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		fact[0].clear();
		fact[1].clear();
		scanf("%llu",&k);
		pollardrho::work(k,0);
		pollardrho::work(k+1,1);
		cnt=0;
		for(auto p:fact[0])lst[++cnt]=p.first;
		for(auto p:fact[1])lst[++cnt]=p.first;
		sort(lst+1,lst+cnt+1);
		cnt=unique(lst+1,lst+cnt+1)-lst-1;
		printf("%d\n",cnt);
	}
}