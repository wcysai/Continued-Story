#include<bits/stdc++.h>
#define MAXN 405
#define MAXM 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int color[MAXN][MAXN];
bool has[MAXN][MAXN];
int cnt[MAXN];
int V;
vector<int> G[MAXN];
int match[MAXN];
bool used[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
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
int bipartite_matching()
{
    int res=0;
    memset(match,-1,sizeof(match));
    for(int v=1;v<=V;v++)
    {
        if(match[v]<0)
        {
            memset(used,0,sizeof(used));
            if(dfs(v))
            {
                res++;
            }
        }
    }
    return res;
} 
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++)
    {
        for(int j=1;j<=n-i;j++)
        {
            int x;scanf("%d",&x);
            color[i][i+j]=color[i+j][i]=x;
        }
    }
    memset(color,0,sizeof(color));
    memset(has,false,sizeof(has));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) 
        {
            if(i==j) continue;
            if(has[i][color[i][j]])
            {
                puts("No");
                return 0;
            }
            has[i][color[i][j]]=true;
            cnt[color[i][j]]++;
        }
    }
    if(m%2==0) {puts("No"); return 0;}
    for(int i=1;i<=m;i++)
    {
        assert(cnt[i]%2==0);
        if(n-cnt[i]>m+1-n)
        {
            puts("No");
            return 0;
        }
        cnt[i]=(m+1-n-(n-cnt[i]))/2;
    }
    V=2*(m+1);
    for(int i=n+1;i<=m+1;i++)
    {
        printf("i=%d\n",i);
        for(int j=1;j<=2*(m+1);j++) G[j].clear();
        for(int j=1;j<=m+1;j++)
        {
            if(i==j) continue;
            if(color[i][j]) add_edge(j,m+1+color[i][j]);
            else
            {
                for(int k=1;k<=m;k++) 
                {
                    if(!has[j][k]) 
                    {
                        if(j<=i||cnt[k]>0) add_edge(j,m+1+k);
                    }
                }
            }
        }
        if(bipartite_matching()!=m)
        {
            puts("No");
            return 0;
        }
        for(int j=1;j<=m+1;j++)
        {
            if(i==j) continue;
            if(!color[i][j])
            {
                color[i][j]=color[j][i]=match[j]-(m+1);
                has[i][color[i][j]]=has[j][color[i][j]]=true;
                if(j>i) cnt[color[i][j]]--;
            }
        }
    }
    puts("Yes");
    for(int i=1;i<=m+1;i++)
    {
        for(int j=1;i+j<=m+1;j++)
            printf("%d ",color[i][i+j]);
        puts("");
    }
    return 0;
}