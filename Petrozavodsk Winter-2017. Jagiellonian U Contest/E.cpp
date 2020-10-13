#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define y1 daokoako
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,s;
struct zone
{
    ll t,y;
    ll lo(ll curt) const {return y-curt+t;}
    ll hi(ll curt) const {return y+curt-t;}
};

bool operator<(zone a,zone b)
{
    return a.y<b.y;
}
set<zone> st;
struct event
{
    enum
    {
        QUERY,THUNDER,MERGE
    }type;
    ll t;
    union
    {
        struct 
        {
            ll y;
            int i;
        };
        struct 
        {
            ll y0,y1;
        };
        struct 
        {
            zone z;
        };
    };
};
bool operator<(event a,event b)
{
    if(a.t==b.t) return a.type<b.type;
    return a.t>b.t;
}
priority_queue<event> E;
char buff[3];
ll merge_time(zone a,zone b)
{
    assert(a.y<b.y);
    ll t=b.y+b.t-a.y+a.t;
    return t/2;
}
zone merge_zone(zone a,zone b,ll t)
{
    zone z;
    z.t=a.t+b.t-t;
    z.y=b.y+z.t-b.t;
    return z;
}
bool process_merge(zone a,zone b,ll ct,set<zone>::iterator &it,set<zone>::iterator oth)
{
    ll et=merge_time(a,b);
    assert(et>=ct);
    if(et==ct)
    {
        st.erase(it);
        st.erase(oth);
        it=st.insert(merge_zone(a,b,et)).F;
        return true;
    }
    return false;
}
void push_merge(zone z,ll t)
{
    event e;
    e.type=event::MERGE;
    e.t=t; e.z=z;
    E.push(e);
}
void consider_merge(const set<zone>::iterator &it,const event &e)
{
    if(it!=st.begin())
    {
        ll et=merge_time(*prev(it),*it);
        assert(et>e.t);
        push_merge(*prev(it),et);
        push_merge(*it,et);
    }
    if(next(it)!=st.end())
    {
        ll et=merge_time(*it,*next(it));
        assert(et>e.t);
        push_merge(*it,et);
        push_merge(*next(it),et);
    }
}
set<zone>::iterator create_zone(ll lo,ll hi,ll t,const event &e)
{
    auto it=st.insert(zone{t-(hi-lo)/2,(lo+hi)/2}).F;
    consider_merge(it,e);
    return it;
}
bool alive[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            event e;
            e.type=event::THUNDER;
            ll r;
            scanf("%lld%lld%lld",&e.t,&e.y0,&r);
            e.y1=e.y0+r;
            e.y0-=r;
            e.y0*=2; e.y1*=2; e.t*=2;
            E.push(e);
        }
        scanf("%d",&s);
        for(int i=0;i<s;i++)
        {
            event e;
            e.type=event::QUERY;
            scanf("%lld%lld",&e.t,&e.y);
            e.i=i;
            e.y*=2; e.t*=2;
            E.push(e);
        }
        st.clear();
        st.insert(zone{0,0});
        while(!E.empty())
        {
            event e=E.top();
            E.pop();
            set<zone>::iterator it;
            zone z;
            switch(e.type)
            {
                case event::QUERY:
                    it=st.upper_bound(zone{e.t,e.y});
                    alive[e.i]=0;
                    if(it!=st.end()&&it->lo(e.t)<=e.y) alive[e.i]=1;
                    if(it!=st.begin()&&prev(it)->hi(e.t)>=e.y) alive[e.i]=1;
                    break;
                case event::THUNDER:
                    it=st.upper_bound(zone{e.t,e.y1});
                    while(it!=st.end()&&it->lo(e.t)<e.y1) ++it;
                    if(it==st.begin()) break; 
                    --it;
                    z=*it;
                    if(z.hi(e.t)<=e.y0) break;
                    if(z.lo(e.t)<=e.y0&&z.hi(e.t)>=e.y1)
                    {
                        st.erase(it);
                        create_zone(z.lo(e.t),e.y0,e.t,e);
                        create_zone(e.y1,z.hi(e.t),e.t,e);
                    }
                    else
                    {
                        if(z.hi(e.t)>=e.y1)
                        {
                            st.erase(it);
                            it=create_zone(e.y1,z.hi(e.t),e.t,e);
                            if(it==st.begin()) break;
                            --it;
                        }
                        bool flag=0;
                        while(it->lo(e.t)>e.y0)
                        {
                            if(it==st.begin())
                            {
                                st.erase(it);
                                flag=1;
                                break;
                            }
                            --it;
                            st.erase(next(it));
                        }
                        if(flag) break;
                        z=*it;
                        if(z.hi(e.t)>e.y0)
                        {
                            st.erase(it);
                            create_zone(z.lo(e.t),e.y0,e.t,e);
                        }
                    }
                    break;
                case event::MERGE:
                    it=st.find(e.z);
                    if(it!=st.end())
                    {
                        while(it!=st.begin()&&process_merge(*prev(it),*it,e.t,it,prev(it)));
                        while(next(it)!=st.end()&&process_merge(*it,*next(it),e.t,it,next(it)));
                        consider_merge(it,e);
                    }
                    break;
                default:
                    assert(0);
            }
        }
        for(int i=0;i<s;i++) printf("%c",alive[i]?'@':'*');
        puts("");
    }
    return 0;
}