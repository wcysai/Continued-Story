#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXM 15
#define MAXN 1005
#define maxn 130
#define maxm 16
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int perm[MAXM][MAXN];
int rk[MAXM][MAXN];
bool ans[MAXN];
bool pused[MAXM];
bool used[MAXN];
set<int> valid;
void dfs(int now)
{
    if(now==m+1) return;
    for(int i=1;i<=m;i++)
    {
        if(pused[i]) continue;
        pused[i]=true;
        int cur=1;
        while(used[perm[i][cur]]) cur++;
        used[perm[i][cur]]=true;
        ans[perm[i][cur]]=true;
        dfs(now+1);
        used[perm[i][cur]]=false;
        pused[i]=false;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&perm[i][j]);
    memset(used,false,sizeof(used));
    memset(pused,false,sizeof(pused));
    dfs(1);
    vector<int> res;
    for(int i=1;i<=n;i++) if(ans[i]) res.push_back(i);
    printf("%d\n",(int)res.size());
    for(auto x:res) printf("%d ",x);
    return 0;
}