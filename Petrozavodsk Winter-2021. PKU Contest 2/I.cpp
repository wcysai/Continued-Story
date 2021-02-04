#include<bits/stdc++.h>
#define MAXN 17
#define INF 1000000000
#define MOD 1000000007
#define REV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int dp[(1<<16)];
bool check(int x)// if we can achieve sum <= x
{
    for(int i=0;i<(1<<n);i++) dp[i]=INF;
    dp[0]=0;
    for(int i=0;i<(1<<n);i++)
    {
        if(dp[i]==INF) continue;
        for(int j=0;j<n;j++)
        {
            if(i&(1<<j)) continue;
            int nsum=max(dp[i],0)+a[j];
            if(nsum>x) continue;
            dp[i^(1<<j)]=min(dp[i^(1<<j)],nsum);
        }
    }
    if(dp[(1<<n)-1]!=INF) return true; else return false;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    int l=-100001,r=1600000;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(check(mid)) r=mid; else l=mid;
    }   
    printf("%d\n",r);
    return 0;
}