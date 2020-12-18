#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int a,b,tot;
bool f;
int l[MAXN],r[MAXN],w[MAXN];
int solve(int x,int y)
{
    if(x==0&&y==0) return 0;
    if(x==0&&y%2==0) {f=false; return 0;}
    if(y)
    {
        int now=++tot;
        w[now]=2;
        int curx=x,cury=y-1;
        if(cury%2==0)
        {
            l[now]=solve(curx/2,cury/2);
            r[now]=solve((x+1)/2,cury/2);
        }
        else if(curx%2==0)
        {
            l[now]=solve(curx/2-1,(cury+1)/2);
            r[now]=solve(curx/2+1,(cury-1)/2);
        }
        else
        {
            l[now]=solve((curx-1)/2,(cury+1)/2);
            r[now]=solve((curx+1)/2,(cury-1)/2);
        }
        return now;
    }
    else
    {
        int now=++tot;
        w[now]=1;
        int curx=x-1,cury=y;
        if(cury%2==0)
        {
            l[now]=solve(curx/2,cury/2);
            r[now]=solve((curx+1)/2,cury/2);
        }
        else if(curx%2==0)
        {
            l[now]=solve(curx/2-1,(cury+1)/2);
            r[now]=solve(curx/2+1,(cury-1)/2);
        }
        else
        {
            l[now]=solve((curx-1)/2,(cury+1)/2);
            r[now]=solve((curx+1)/2,(cury-1)/2);
        }
        return now;
    }
    
}
int main()
{
    scanf("%d%d",&a,&b);
    f=true;
    tot=0;
    solve(a,b);
    if(!f) puts("-1");
    else
    {
        for(int i=1;i<=a+b;i++) printf("%d %d %d\n",w[i],l[i],r[i]);
        return 0;
    }
}