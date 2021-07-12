#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int ans[MAXN];
vector<int> v;
void solve(int cur,vector<int> &v)
{
    set<int> s;
    for(auto x:v) s.insert(x);
    for(auto x:v) ans[x]=min(ans[x],cur);
    if(cur>=8) return;
    for(int i=0;i<(int)v.size();i++)
    {
        for(int j=i;j<(int)v.size();j++)
        {
            if(v[i]+v[j]>=1024) continue;
            vector<int> tmp=v;
            if(s.count(v[i]+v[j])) continue;
            if(ans[v[i]+v[j]]<cur-1) continue;
            tmp.push_back(v[i]+v[j]);
            solve(cur+1,tmp);
        }
    }
    for(int i=0;i<(int)v.size();i++)
    {
        for(int j=i+1;j<(int)v.size();j++)
        {
            vector<int> tmp=v;
            tmp.push_back(max(v[i]-v[j],v[j]-v[i]));
            if(s.count(max(v[i]-v[j],v[j]-v[i]))) continue;
            if(ans[max(v[i]-v[j],v[j]-v[i])]<cur-1) continue;
            solve(cur+1,tmp);
        }
    }
}
int main()
{
    for(int i=2;i<=1000;i++) ans[i]=INF;
    for(int i=1;i<(1<<10);i++)
    {
        if(__builtin_popcount(i)>=5) continue;
        v.clear();
        for(int j=0;j<10;j++) if(i&(1<<j)) v.push_back(1<<(j+1));
        v.push_back(1);
        solve(__builtin_popcount(i),v);
        printf("i=%d\n",i);
    }
    freopen("hardcode.txt","w",stdout);
    for(int i=2;i<=1000;i++)
    {
        printf("%d,",ans[i]);
        if(i%50==0) puts("");
    }
    return 0;
}