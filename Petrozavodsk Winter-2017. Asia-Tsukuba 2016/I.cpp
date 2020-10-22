#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t;
int n,m;
//ax+by=gcd(x,y)
ll extgcd(ll a,ll b,ll &x,ll &y)
{
    ll d=a;
    if(b!=0)
    {
        d=extgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
    {
        x=1;
        y=0;
    }
    return d;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        int g=__gcd(n,m);
        if(g<50000) 
        {
            printf("3\n%d %d\n%d %d\n",0,0,n,m);
            ll x,y;
            extgcd(m,-n,x,y);
            while(x<0||y<0)x+=n,y+=m;
            while(x>n||y>m)x-=n,y-=m;
            printf("%d %d\n",(int)x,(int)y);
        }
        else{
            printf("4\n0 0\n%d %d\n%d %d\n%d %d\n",n-1,m,n/g,m/g,n,m-1);
        }
    }
    return 0;                                                                                                                                                                                           
}