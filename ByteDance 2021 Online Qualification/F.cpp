#include<bits/stdc++.h>
#define MAXN 105
#define MAXT 305
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,T,C,s[MAXN];
vector<int> testcases[MAXN];
int cnt[MAXN];
vector<int> G[MAXN];
bool valid[MAXN];
bool tested[MAXT];
int taskcnt[MAXT][MAXN];
vector<int> ind;
void refresh()
{
    ind.clear();
    for(int i=1;i<=N;i++)
    {
        if(valid[i])
        {
            for(auto x:testcases[i]) if(!tested[x]) ind.push_back(x);
        }
    }
    sort(ind.begin(),ind.end());
    ind.erase(unique(ind.begin(),ind.end()),ind.end());
}
void dfs(int v)
{
    valid[v]=false;
    for(auto to:G[v])
    {
        if(valid[to]==false) continue;
        dfs(to);
    }
}
int test(int x)
{
    assert(x>C);
    printf("%d\n",C-x);
    C=x;
    fflush(stdout);
    int y;
    scanf("%d",&y);
    return y;
}
void answer(int x)
{
    printf("%d\n",x);
    fflush(stdout);
    exit(0);
}
int main()
{
    scanf("%d%d",&N,&T);
    for(int i=1;i<=N;i++) 
    {
        scanf("%d",&s[i]);
        int x;
        scanf("%d",&x);
        for(int j=0;j<x;j++)
        {
            int y;
            scanf("%d",&y);
            testcases[i].push_back(y);
            taskcnt[y][i]++;
        }
        sort(testcases[i].begin(),testcases[i].end());
        cnt[i]=testcases[i].size();
    }
    for(int i=1;i<=N;i++)
    {
        int d;
        scanf("%d",&d);
        for(int j=0;j<d;j++)
        {
            int x;
            scanf("%d",&x);
            G[x].push_back(i);
        }
    }
    memset(valid,true,sizeof(valid));
    memset(tested,false,sizeof(tested));
    refresh();
    int score=0;
    while(ind.size())
    {
        int x=ind[0];
        int outcome=test(x);
        tested[x]=true;
        if(outcome==0)
        {
            for(int i=1;i<=N;i++)
            {
                if(taskcnt[x][i]>0&&valid[i])
                {
                    valid[i]=false;
                    dfs(i);
                }
            }
            refresh();
        }
        else
        {
            ind.erase(ind.begin());
            for(int i=1;i<=N;i++)
            {
                if(taskcnt[x][i]>0)
                {
                    cnt[i]-=taskcnt[x][i];
                    if(cnt[i]==0) score+=s[i];
                }
            }
        }
    }
    answer(score);
    return 0;
}