#include<bits/stdc++.h>
#define MAXV 500005
#define MAXE 1000005
#define INF 1000000000
#define INF2 1000000000000LL
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
mt19937 wcy(time(NULL));
int main()
{
    freopen("F.in","w",stdout);
    int n=250000;
    printf("%d\n",n);
    for(int i=0;i<n;i++)
    {
        int x,y;
        x=wcy()%500000+1,y=wcy()%500000+1;
        if(x>y) swap(x,y);
        ll w;
        w=wcy()%INF2+1;
        printf("%d %d %lld\n",x,y,w);
    }
}