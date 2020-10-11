#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c[MAXN];
ll tmp[MAXN],d=0;
bool check(int x)
{
    for(int i=0;i<=n-1;i++) if(i<x) tmp[i]=c[i]; else {tmp[i]=0; tmp[0]+=c[i];}
    d=0;
    for(int i=x-1;i>=1;i--)
    {
        ll need=max(0LL,1+d-tmp[i]);
        if(tmp[i]-(d+1)>0) tmp[0]+=tmp[i]-(d+1);
        d+=need;
        if(d+1>INF) return false;
    }
    if(tmp[0]>=d+1) return true; else return false;
}
int main()
{
    scanf("%d",&n);
    ll s=0;
    for(int i=0;i<=n-1;i++)
    {
        scanf("%d",&c[i]);
        s+=c[i];
    }
    if(s==1)
    {
        int p=-1;
        for(int i=0;i<=n-1;i++) if(c[i]) {p=i; break;}
        if(p==0) puts("1"); else printf("%d\n",p);
        return 0;
    }
    int l=0,r=200000;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(check(mid)) l=mid; else r=mid;
    }
    printf("%d\n",l);
}