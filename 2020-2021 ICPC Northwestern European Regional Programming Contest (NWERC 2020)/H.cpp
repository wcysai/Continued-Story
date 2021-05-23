#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,t[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&t[i]);
    sort(t+1,t+n+1);
    if(n%2==0)
    {
        for(int i=1;i<=n/2;i++) 
        {
            printf("%d ",t[n/2+1-i]);
            printf("%d ",t[n/2+i]);
        }
    }
    else
    {
        printf("%d ",t[n/2+1]);
        for(int i=1;i<=n/2;i++) 
        {
            printf("%d ",t[n/2+1-i]);
            printf("%d ",t[n/2+1+i]);
        }
    }
    return 0;
}