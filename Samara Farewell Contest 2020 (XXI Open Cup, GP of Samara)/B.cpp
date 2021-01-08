#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
bool check(double x)
{
    double res=0.0;
    for(int i=1;i<=n;i++) res+=max(b[i]-a[i]*x,d[i]-c[i]*x);
    return res>=0.0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
    double l=1e-9,r=1e9;
    for(int i=0;i<200;i++)
    {
        double mid=(l+r)/2;
        if(check(mid)) l=mid; else r=mid;
    }
    printf("%.10f\n",l);
    return 0;
}