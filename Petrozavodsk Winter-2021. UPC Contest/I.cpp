#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a[MAXN],b[MAXN];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&b[i]);
            b[i]-=a[i];
        }
        if(n==1) {puts("YES"); continue;}
        if(b[1]==0) {puts("NO"); continue;}
        if(n==2&&b[2]>0) {puts("NO"); continue;}
        int s=0;
        for(int i=2;i<=n;i++)
        {
            s+=b[i];
            s=min(s,n-2);
        }
        int need=n-1-s;
        if(b[1]<need) {puts("NO"); continue;}
        puts("YES");
    }
    return 0;
}