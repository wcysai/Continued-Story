#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,x[MAXN],y[MAXN],id[MAXN];
bool cmp(int u,int v)
{
    return P(x[u],y[u])<P(x[v],y[v]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<=n;i++) id[i]=i;
    sort(id+1,id+n+1,cmp);
    printf("%d\n",2*n-1);
    for(int i=1;i<=n;i++) printf("%d ",id[i]);
    for(int i=n-1;i>=1;i--) printf("%d ",id[i]);
    puts("");
}