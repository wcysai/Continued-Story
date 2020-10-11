#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q;
string str;
map<P,P> mp;
int shiftx=0,shifty=0;
//mp[(x,y)]: where starting in (x-shiftx,y-shifty) ends up at 
void go(int dx,int dy) //L:(-1,0) R:(1,0) U:(0,1) D:(0,-1)
{
    if(mp.find(P(-dx+shiftx,-dy+shifty))!=mp.end())
    {
        P p=mp[P(-dx+shiftx,-dy+shifty)];
        shiftx+=dx; shifty+=dy;
        mp[P(-dx+shiftx,-dy+shifty)]=p;
    }
    else
    {
        P p=P(-dx+shiftx,-dy+shifty);
        shiftx+=dx; shifty+=dy;
        mp[P(-dx+shiftx,-dy+shifty)]=p;
    }
}
int main()
{
    scanf("%d",&n);
    cin>>str;
    for(int i=n-1;i>=0;i--)
    {
        if(str[i]=='L') go(-1,0);
        else if(str[i]=='R') go(1,0);
        else if(str[i]=='U') go(0,1);
        else go(0,-1);
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(mp.find(P(x+shiftx,y+shifty))!=mp.end())
        {
            P p=mp[P(x+shiftx,y+shifty)];
            printf("%d %d\n",p.F,p.S);
        } 
        else printf("%d %d\n",x+shiftx,y+shifty);
    }
}