#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> x,y;
ll solve_same(vector<int> &x)
{
    int pos=x[n/2];
    ll ans=0;
    for(int i=0;i<n;i++) ans+=max(x[i]-pos,pos-x[i]);
    return ans;
}
ll solve_diff(vector<int> &x)
{
    vector<int> tmp;
    for(int i=0;i<n;i++) tmp.push_back(x[i]-i);
    sort(tmp.begin(),tmp.end());
    return solve_same(tmp);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        x.push_back(u); y.push_back(v);
    }
    sort(x.begin(),x.end()); sort(y.begin(),y.end());
    ll ans=solve_same(x)+solve_diff(y);
    ans=min(ans,solve_same(y)+solve_diff(x));
    printf("%lld\n",ans);
    return 0;
}