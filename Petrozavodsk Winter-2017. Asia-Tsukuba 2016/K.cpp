#include<bits/stdc++.h>
#define MAXN 45
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll compute_val(string &str)
{
    ll k=(1LL<<40);
    int n=(int)str.size(),i=0;
    ll ans=0;
    while(i<=n-1&&str[i]==str[0])
    {
        if(str[i]=='W') ans+=k; else ans-=k;
        i++;
    }
    k>>=1;
    while(i<=n-1)
    {
        if(str[i]=='W') ans+=k; else ans-=k;
        k>>=1;
        i++;
    }
    return ans;
}
int n;
vector<pair<ll,int> > v;
string str;
map<ll,int> mp;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        cin>>str;
        v.push_back(make_pair(compute_val(str),(int)str.size()));
    }
    for(int i=0;i<(1<<(n/2));i++)
    {
        ll res=0;
        int cnt=0;
        for(int j=0;j<(n/2);j++)
            if(i&(1<<j)) res+=v[j].F,cnt+=v[j].S;
        mp[res]=max(mp[res],cnt);
    }
    int ans=0;
    for(int i=0;i<(1<<(n-n/2));i++)
    {
        ll res=0; 
        int cnt=0;
        for(int j=n/2;j<n;j++)
            if(i&(1<<(j-n/2))) res+=v[j].F,cnt+=v[j].S;
        if(mp.find(-res)!=mp.end()) ans=max(ans,cnt+mp[-res]);
    }
    printf("%d\n",ans); 
}