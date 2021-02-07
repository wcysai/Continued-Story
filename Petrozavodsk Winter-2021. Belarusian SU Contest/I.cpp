#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,ax,ay,bx,by;//abs(ax-by)
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) 
    {
        int x;
        scanf("%d",&x);
        if(x==0) ax++; else ay++;
    }
    for(int i=1;i<=m;i++) 
    {
        int x;
        scanf("%d",&x);
        if(x==0) bx++; else by++;
    }
    int s=0;
    for(int i=1;i<=k;i++)
    {
        int x;
        scanf("%d",&x);
        s=max(s,x);
    }
    int ans=0;
    for(int i=max(0,s-ay);i<=ax;i++)
    {
        int nax=ax-i;
        int nay=ay-(s-i);
        int nbx=bx+i;
        int nby=by+(s-i);
        int res=0;
        int tmp=min(nbx,s);
        res=max(res,max((nax+tmp)-(nby-(s-tmp)),(nby-(s-tmp))-(nax+tmp)));
        tmp=max(0,s-nby);
        res=max(res,max((nax+tmp)-(nby-(s-tmp)),(nby-(s-tmp))-(nax+tmp)));
        ans=max(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}