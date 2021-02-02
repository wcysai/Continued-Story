#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int type[MAXN],level[MAXN];
vector<int> has[MAXN];
ll ans[MAXN],tmp[MAXN],s;
vector<int> v;
vector<ll> sum;
vector<P> st;
bool cmp(P p,P q)
{
    if(p.F!=q.F) return p.F<q.F;
    return p.S>q.S;
}
ll eval(P p,int num)
{
    if(v[num-1]>=p.S) return s+1LL*p.F*num-sum[num]; else return s+1LL*p.F*(num-1)-sum[num-1]+p.F-p.S;
}
int get_intersection(P p,P q) //maxi[p]>=maxi[q]
{
    int l=0,r=n;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(eval(p,mid)>=eval(q,mid)) r=mid; else l=mid;
    }
    return r;
}
void add(P p)
{
    while(st.size()>=2)
    {
        P q=st.back(); st.pop_back();
        P r=st.back(); st.pop_back();
        st.push_back(r);
        if(get_intersection(p,q)>get_intersection(q,r)) {st.push_back(q); break;} 
    }
    st.push_back(p);
}
ll query(int x)
{
    int l=-1,r=(int)st.size()-1;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(eval(st[mid],x)<=eval(st[mid+1],x)) l=mid; else r=mid;
    }
    return eval(st[r],x);
}
int main()
{
    scanf("%d",&n);
    s=0;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d",&type[i],&level[i]);
        has[type[i]].push_back(level[i]);
        s+=level[i];
    }
    for(int i=1;i<=100000;i++)
        if(has[i].size()) sort(has[i].begin(),has[i].end());
    for(int i=1;i<=n;i++)
        v.push_back(level[i]);
    sort(v.begin(),v.end());
    sum.resize(v.size()+1);
    sum[0]=0;
    for(int i=0;i<(int)v.size();i++) sum[i+1]=sum[i]+v[i];
    vector<P> lines;
    for(int i=1;i<=100000;i++)
    {
        if(has[i].size()>1)
        {
            int maxi=has[i].back();
            int st=has[i][0];
            lines.push_back(P(maxi,st));
        }
    }
    sort(lines.begin(),lines.end(),cmp);
    for(auto p:lines) add(p);
    for(int i=1;i<=n;i++)
        if(!st.size()) ans[i]=s; else ans[i]=query(i);
    for(int i=2;i<=n;i++) ans[i]=max(ans[i],ans[i-1]);
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
    return 0;
}