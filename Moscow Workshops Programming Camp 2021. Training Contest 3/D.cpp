//team continued story
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int t,p,a,m;
vector<int> v;
int pow_mod(int a,int i,int m=p)
{
    if(a==0) return 0;
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=1LL*a*a%m;
        i>>=1;
    }
    return s;
}
bool g_test(int g,int p)
{
    for(int i=0;i<(int)v.size();i++)
        if(pow_mod(g,(p-1)/v[i],p)==1)
            return 0;
    return 1;
}
int primitive_root(int p)
{
    int tmp=p-1;
    for(int i=2;i<=tmp/i;i++)
    {
        if(tmp%i==0)
        {
            v.push_back(i);
            while(tmp%i==0) tmp/=i;
        }
    }
    if(tmp!=1) v.push_back(tmp);
    int g=1;
    while(true)
    {
        if(g_test(g,p)) return g;
        ++g;
    }
}
ll get_ans(int x,int y,int p)
{
    ll res=x+1LL*(y-x)*p;
    while(res<=0) res+=1LL*p*(p-1);
    while(res>1LL*p*(p-1)) res-=1LL*p*(p-1);
    return res;
}
bool check(ll ans)
{
    ll x=ans%p,y=ans%(p-1);
    return (pow_mod(x,y,p)+pow_mod(x,m,p))%p==a;
}
unordered_map<int,int> umap;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&p,&a,&m);
        bool f=false;
        if(p<50)
        {
            for(int x=0;x<=p-1;x++)
                for(int y=0;y<=p-2;y++)
                {
                    if(f) break;
                    if((pow_mod(x,y,p)+pow_mod(x,m,p))%p==a)
                    {
                        f=true;
                        printf("YES %lld\n",get_ans(x,y,p));
                        assert(check(get_ans(x,y,p)));
                    }
                }
        }
        else
        {
            v.clear();
            int g=primitive_root(p);
            if(pow_mod(g,m,p)==a)
            {
                for(int i=2;i<p-1;i++) if(__gcd(i,p-1)==1) {g=pow_mod(g,i,p-1); break;}
                assert(g_test(g,p)&&pow_mod(g,m,p)!=a);
            }
            umap.clear();
            int inv=pow_mod(g,p-2,p);
            int block=40000;
            int c=(a-pow_mod(g,m,p)+p)%p;
            assert(c!=0);
            int x=pow_mod(g,block,p),y=c;
            for(int i=0;i<40000;i++)
            {
                if(umap.find(y)==umap.end()) umap[y]=i;
                y=1LL*y*inv%p;
            }
            y=1;
            int ans=-1;
            for(int i=0;i<=30000;i++)
            {
                if(umap.find(y)!=umap.end())
                {
                    ans=i*block+umap[y];
                    break;
                }
                y=1LL*y*x%p;
            }
            assert(ans!=-1);
            printf("YES %lld\n",get_ans(g,ans,p));
            assert(check(get_ans(g,ans,p)));
            f=true;
        }
        if(!f) puts("NO");
    }
    return 0;
}
