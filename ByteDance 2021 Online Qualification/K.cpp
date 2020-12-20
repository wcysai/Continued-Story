#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
string r,b;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        cin>>r;
        cin>>b;
        int cnt0=0,cnt1=0;
        for(int i=0;i<n;i++) if(r[i]>b[i]) cnt0++; else if(b[i]>r[i]) cnt1++;
        if(cnt0>cnt1) puts("RED"); else if(cnt1>cnt0) puts("BLUE"); else puts("EQUAL");
    }
    return 0;
}