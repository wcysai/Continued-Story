#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m;
P p[MAXN];
bool cmp(P x,P y)
{
    if(x.F<=x.S&&(y.F>y.S)) return true;
    if(x.F>x.S&&(y.F<=y.S)) return false;
    if(x.F<=x.S) return x.F<y.F;
    return max(x.F,x.F-x.S+y.F)<max(y.F,y.F-y.S+x.F);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        bool flag=true;
        for(int i=1;i<=n;i++) 
        {
            scanf("%d%d",&p[i].F,&p[i].S);
            p[i].S=min(p[i].S,m);
        }
        sort(p+1,p+n+1,cmp);
        bool f=true;
        ll cur=m;
        for(int i=1;i<=n;i++)
        {
            if(cur<p[i].F)
            {
                f=false;
                break;
            }
            cur-=p[i].F; cur+=p[i].S;
        }
        if(f) puts("YES"); else puts("NO");
    }
    return 0;
}