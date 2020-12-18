#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 wcy(time(NULL));
int main()
{
    freopen("D.in","w",stdout);
    printf("%d\n",300000);
    for(int i=1;i<=300000;i++)
    {
        for(int j=0;j<8;j++)
        {
            int x=wcy()%2;
            if(x) printf("W"); else printf("R");
        }
        puts("");
    }
}