#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int n,x;
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        bool f=false;
        scanf("%d",&x);
        for(int i=1;i*i<=x;i++)
        {
            if(x%i) continue;
            int j=x/i;
            if(j<=2*i) {f=true; break;}
        }
        if(f) puts("1"); else puts("0");
    }
    return 0;
}