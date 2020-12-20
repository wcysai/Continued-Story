#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
ll a[MAXN],b[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=m;i++) scanf("%lld",&b[i]);
    ll g=0;
    sort(a+1,a+n+1);
    for(int i=2;i<=n;i++) g=__gcd(g,a[i]-a[i-1]);
    for(int i=1;i<=m;i++) printf("%lld ",__gcd(g,a[1]+b[i]));
}