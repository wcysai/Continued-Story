#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 6005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n;
vector<int> G[MAXN];
int match[MAXN];
bool used[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
int res;
bool dfs(int v)
{
    used[v]=true;
    for(int i=0;i<G[v].size();i++)
    {
        int u=G[v][i],w=match[u];
        if(w<0||!used[w]&&dfs(w))
        {
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}
int main()
{
    scanf("%lld",&n);
    ll need=min(n/2,3000LL);
    memset(match,-1,sizeof(match));
    string ans="1"; res=0;
    for(int i=1;i<=need;i++)
    {
        for(ll j=n;j>n-i+1;j--) if(j%i==0) add_edge(i,n-j+1+need);
        for(int j=1;j<=i;j++) if((n-i+1)%j==0) add_edge(j,need+i);
        if(match[i]<0)
        {
            if(dfs(i)) res++;
        }
        if(match[need+i]<0)
        {
            if(dfs(need+i)) res++;
        }
        if(res==i) ans+="1"; else ans+="0";
        assert(res<=i);
    }
    if(2LL*(int)ans.size()>n+1)
    {
        string tmp=ans;
        reverse(tmp.begin(),tmp.end());
        ans.pop_back();
        ans=ans+tmp;
        puts("2");
        printf("%d",(int)ans.size());
        for(int i=0;i<(int)ans.size();i++) printf(" %c",ans[i]);
        puts("");
        return 0;
    }
    ll zeros=n+1-2*(int)ans.size();
    if(zeros)
    {
        puts("63");
        for(int i=1;i<=60;i++)
        {
            int last=(i==1?0:i);
            printf("2 %d %d\n",last,last);
        }
        vector<int> v; v.clear();
        for(int i=0;i<=60;i++)
        {
            if(zeros&(1LL<<i))
            {
                int id=(i==0?0:i+1);
                v.push_back(id);
            }
        }
        assert(v.size());
        printf("%d",(int)v.size());
        for(auto x:v) printf(" %d",x);
        puts("");
        printf("%d",2*(int)ans.size()+1);
        for(int i=0;i<(int)ans.size();i++) printf(" %c",ans[i]);
        printf(" 62");
        for(int i=(int)ans.size()-1;i>=0;i--) printf(" %c",ans[i]);
        puts("");
        return 0;
    }
    else
    {
        string tmp=ans;
        reverse(tmp.begin(),tmp.end());
        ans=ans+tmp;
        puts("2");
        printf("%d",(int)ans.size());
        for(int i=0;i<(int)ans.size();i++) printf(" %c",ans[i]);
        puts("");
        return 0;
    }
}