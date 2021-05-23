#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 cjbsb
#define y1 sbcjb
#define x2 ntcjb
#define y2 cjbnt
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<P> v;
ll get_sqrt(ll x)
{
    int y=(int)sqrt(x);
    for(int i=max(0,y-2);i<=y+2;i++) if(1LL*i*i==x) return i;
    return -1;
}
ll query(int x,int y)
{
    printf("%d %d\n",x,y);
    fflush(stdout);
    ll res;
    scanf("%lld",&res);
    return res;
}
void get_dragon_ball()
{
    ll d=query(0,0);
    vector<P> v; v.clear();
    for(int i=0;1LL*i*i<=d;i++)
    {
        ll x=get_sqrt(d-1LL*i*i);
        if(x!=-1&&i>=0&&i<=1000000&&x>=0&&x<=1000000) v.push_back(P(i,x));
    }
    if(v.size()>=142) 
    {
        vector<P> tmp; tmp.clear();
        ll d1=query(0,1),d2=query(1,0);
        for(auto p:v)
            if(1LL*p.F*p.F+1LL*(p.S-1)*(p.S-1)==d1||1LL*p.F*p.F+1LL*(p.S-1)*(p.S-1)==d2) tmp.push_back(p);
        swap(v,tmp);
    }
    for(auto p:v) if(query(p.F,p.S)==0) return; 
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) get_dragon_ball();
    return 0;
}