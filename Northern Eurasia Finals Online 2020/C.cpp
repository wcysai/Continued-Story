#include<bits/stdc++.h>
#define F first
#define S second
#define INF 1000000000
#define MOD 1000000007
#define MAXN 25
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,p[MAXN];
vector<int> G[MAXN];
vector<int> combine(vector<int> &x,vector<int> &y)
{
    vector<int> tmp=x;
    for(int i=0;i<(int)y.size();i++)
    {
        tmp.push_back(y[i]);
        if(i&1) for(int j=0;j<(int)x.size();j++) tmp.push_back(x[j]);
        else for(int j=(int)x.size()-1;j>=0;j--) tmp.push_back(x[j]);
    }
    return tmp;
}
vector<int> dfs(int v)
{
    vector<int> tmp; tmp.clear();
    for(auto to:G[v])
    {
        vector<int> cur=dfs(to);
        if(!tmp.size()) tmp=cur;
        else tmp=combine(tmp,cur);
    }
    if(v!=1) {reverse(tmp.begin(),tmp.end()); tmp.push_back(v); reverse(tmp.begin(),tmp.end());}
    return tmp;
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;i++) 
    {
        scanf("%d",&p[i]);
        G[p[i]].push_back(i);
    }
    vector<int> ans=dfs(1);
    printf("%d\n",(int)ans.size());
    for(auto x:ans) printf("%d ",x);
    puts("");
    return 0;
}
