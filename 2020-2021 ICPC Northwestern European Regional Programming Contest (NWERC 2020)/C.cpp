#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,d,s;
int main()
{
    scanf("%d%d%d%d",&n,&k,&d,&s);
    int sum=n*d-k*s;
    if(sum<0||100*(n-k)<sum) puts("impossible");
    else printf("%.10f\n",(double)sum/(double)(n-k));
    return 0;
}