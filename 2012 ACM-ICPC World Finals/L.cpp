#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<ll> a,b;
bool check_asingle(vector<ll> a,vector<ll> b)
{
    ll cur=a[0];
    while(b.size()>1)
    {
        if(b.back()>cur) return false;
        b.pop_back();
        if(b.size()==1) break;
        ll x=b.back(); b.pop_back();
        ll y=b.back(); b.pop_back();
        b.push_back(x+y);
    }
    if(b.back()>cur) return false; else return true;
}
bool check_bsingle(vector<ll> a,vector<ll> b)
{
    ll cur=b[0];
    while(a.size()>1)
    {
        if(a.back()>cur) return true;
        ll x=a.back(); a.pop_back();
        ll y=a.back(); a.pop_back();
        a.push_back(x+y);
        if(a.back()>cur) return true;
        a.pop_back();
    }   
    if(a.size()==0) return false;
    else if(a.back()>cur) return true;
    return false;
}
bool check(vector<ll> a,vector<ll> b)
{
    if(a.size()==0) return false;
    if(b.size()==0) return true;
    if(a.size()==1) return check_asingle(a,b);
    if(b.size()==1) return check_bsingle(a,b);
    while(a.size()>1&&b.size()>1)
    {
        ll x=a.back(); a.pop_back();
        ll y=a.back(); a.pop_back();
        if(x+y<b.back()) return false;
        a.push_back(x+y);
        x=b.back(); b.pop_back();
        y=b.back(); b.pop_back();
        if(x+y<a.back()) return true;
        b.push_back(x+y);
    }
    if(a.size()==1) return check_asingle(a,b);
    if(b.size()==1) return check_bsingle(a,b);
    assert(0);
    return true;
}
int main()
{
    int testcase=0;
    while(scanf("%d%d",&n,&m)==2)
    {
        testcase++;
        a.clear(); b.clear();
        for(int i=0;i<n;i++)
        {
            ll x;
            scanf("%lld",&x);
            a.push_back(x);
        }
        sort(a.begin(),a.end());
        for(int i=0;i<m;i++)
        {
            ll x;
            scanf("%lld",&x);
            b.push_back(x);
        }
        sort(b.begin(),b.end());
        bool canwin=false;
        if(check(a,b)) canwin=true;
        if(a.back()>b.back())
        {
            b.pop_back();
            if(!check(b,a)) canwin=true;
        }
        if(canwin) printf("Case %d: Takeover Incorporated\n",testcase);
        else printf("Case %d: Buyout Limited\n",testcase);
    }
    return 0;
}