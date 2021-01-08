#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
int n;
struct node
{
    ll q,w,e;
}a[MAXN];
bool cmp(node x,node y)
{
    return x.q<y.q;
}
set<P> s;
multiset<ll> res;
void serase(set<P>::iterator it)
{
    if(it!=s.begin())
    {
        auto pre=prev(it);
        res.erase(res.find(pre->S+it->F-2));
    }
    if(next(it)!=s.end())
    {
        auto nxt=next(it);
        res.erase(res.find(it->S+nxt->F-2));
    }
    if(it!=s.begin()&&next(it)!=s.end())
    {
        auto pre=prev(it);
        auto nxt=next(it);
        res.insert(pre->S+nxt->F-2);
    }
}
void sinsert(set<P>::iterator it)
{
    if(it!=s.begin())
    {
        auto pre=prev(it);
        res.insert(pre->S+it->F-2);
    }
    if(next(it)!=s.end())
    {
        auto nxt=next(it);
        res.insert(it->S+nxt->F-2);
    }
    if(it!=s.begin()&&next(it)!=s.end())
    {
        auto pre=prev(it);
        auto nxt=next(it);
        res.erase(res.find(pre->S+nxt->F-2));
    }
}
void add(ll x,ll y)
{
    if(s.size()==0)
    {
        s.insert(P(x,y));
        return;
    }
    auto it=s.lower_bound(P(x+1,0));
    if(it!=s.begin())
    {
        it--;
        if(it->S<=y) return;
        it++;
    } 
    it=s.lower_bound(P(x,0));
    while(it!=s.end())
    {
        if(it->F>=x&&it->S>=y)
        {
           serase(it);
           it=s.erase(it);
        }
        else break;
    }
    s.insert(P(x,y));
    it=s.lower_bound(P(x,y));
    sinsert(it);
}
ll get_ans()
{
    if(!res.size()) return -INF-1;
    auto it=res.end(); it--;
    return *it;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i].q,&a[i].w,&a[i].e);
    a[++n]=(node){INF+1,0,0};
    a[++n]=(node){0,INF+1,0};
    a[++n]=(node){0,0,INF+1};
    sort(a+1,a+n+1,cmp);
    ll ans=-INF;
    int now=1; ll cur=0;
    while(now<=n-1)
    {
        cur=a[now].q;
        while(now<=n&&a[now].q==cur) {add(a[now].w,a[now].e); now++;}
        ans=max(ans,a[now].q-1+get_ans());
    }
    if(ans>=1000000000000LL) puts("Infinity"); else printf("%lld\n",ans);
}