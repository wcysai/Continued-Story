#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 755
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,k,s,res;
bool has[MAXN][MAXN];
vector<int> trams[MAXN];
bool adj[MAXN][MAXN];
bool valid[MAXN];
int d[MAXN][MAXN],nd[MAXN][MAXN];
int cdist[MAXN];
vector<int> sus,ans;
vector<int> cur;
void add_clique(int id)
{
    for(int i=1;i<=n;i++) 
    {
        if(has[id][i]) cdist[i]=0; 
        else
        {
            cdist[i]=INF;
            for(int j=1;j<=n;j++)
            {
                if(has[id][j]) cdist[i]=min(cdist[i],d[i][j]+1);
            }
        } 
    }
    res=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            d[i][j]=d[j][i]=min(d[i][j],cdist[i]+cdist[j]);
            if(d[i][j]<INF) res=max(res,d[i][j]);
        }
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        sus.clear(); ans.clear();
        scanf("%d%d",&n,&k);
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n;j++)
                has[i][j]=false; 
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                d[i][j]=(i==j?0:INF);
        for(int i=1;i<=k;i++)
        {
            int x;
            scanf("%d",&x);
            for(int j=0;j<x;j++)
            {
                int y;
                scanf("%d",&y);
                has[i][y]=true;
            }
        }
        for(int i=1;i<=k;i++) valid[i]=true;
        scanf("%d",&s);
        for(int i=0;i<s;i++)
        {
            int x;
            scanf("%d",&x);
            sus.push_back(x);
            valid[x]=false;
        }
        cur.clear();
        for(int i=1;i<=k;i++) if(valid[i]) cur.push_back(i);
        int sz=(int)cur.size();
        for(int i=0;i<sz;i++) add_clique(cur[i]);
        ans.push_back(res);
        for(int i=(int)sus.size()-1;i>=0;i--) 
        {
            add_clique(sus[i]);
            ans.push_back(res);
        }
        reverse(ans.begin(),ans.end());
        for(auto x:ans) printf("%d\n",x);
    }
    return 0;
}