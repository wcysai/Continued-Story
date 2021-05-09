#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 255
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,p[4];
double dp[MAXN][MAXN][MAXN];//dp[i][j][k]: interval between AB is i,interval between BC is j,interval between CD is k
double f[MAXN][MAXN];//f[i][j]: C not appeared, interval between AB is i,interval between BD is j
double g[MAXN][MAXN];//g[i][j]: B not appeared, interval between AC is i,interval between CD is j
double ans[MAXN];//ans[i]: BC not appeared, interval between AD is i
double solve_dp(int i,int j,int k)
{
    if(i<0||j<0||k<0) return 0.0;
    if(i==0&&j==0&&k==0) return 1.0;
    if(dp[i][j][k]!=-1.0) return dp[i][j][k];
    dp[i][j][k]=0.0;
    //A case
    dp[i][j][k]+=0.01*p[0]*solve_dp(i-1,j,k);
    //B case
    dp[i][j][k]+=0.01*p[1]*max(solve_dp(i-1,j,k),solve_dp(i,j-1,k));
    //C case
    dp[i][j][k]+=0.01*p[2]*max(solve_dp(i,j-1,k),solve_dp(i,j,k-1));
    //D case
    dp[i][j][k]+=0.01*p[3]*solve_dp(i,j,k-1);
    return dp[i][j][k];
}
double solve_f(int i,int j)
{
    if(i<0||j<0) return 0.0;
    if(i==0&&j==0) return 1.0;
    if(f[i][j]!=-1.0) return f[i][j];
    f[i][j]=0.0;
    //A case
    f[i][j]+=0.01*p[0]*solve_f(i-1,j);
    //B case
    f[i][j]+=0.01*p[1]*max(solve_f(i-1,j),solve_f(i,j-1));
    //C case
    double tmp=0.0;
    for(int k=1;k<=j;k++) tmp=max(tmp,solve_dp(i,k-1,j-k));
    f[i][j]+=0.01*p[2]*tmp;
    //D case
    f[i][j]+=0.01*p[3]*solve_f(i,j-1);
    return f[i][j];
}
double solve_g(int i,int j)
{
    if(i<0||j<0) return 0.0;
    if(i==0&&j==0) return 1.0;
    if(g[i][j]!=-1.0) return g[i][j];
    g[i][j]=0.0;
    //A case
    g[i][j]+=0.01*p[0]*solve_g(i-1,j);
    //B case
    double tmp=0.0;
    for(int k=1;k<=i;k++) tmp=max(tmp,solve_dp(k-1,i-k,j));
    g[i][j]+=0.01*p[1]*tmp;
    //C case
    g[i][j]+=0.01*p[2]*max(solve_g(i-1,j),solve_g(i,j-1));
    //D case
    g[i][j]+=0.01*p[3]*solve_g(i,j-1);
    return g[i][j];
}
double solve_ans(int i)
{
    if(i<0) return 0.0;
    if(i==0) return 1.0;
    if(ans[i]!=-1.0) return ans[i];
    ans[i]=0.0;
    //A case
    ans[i]+=0.01*p[0]*solve_ans(i-1);
    //B case
    double tmp=0.0;
    for(int k=1;k<=i;k++) tmp=max(tmp,solve_f(k-1,i-k));
    ans[i]+=0.01*p[1]*tmp;
    //C case
    tmp=0.0;
    for(int k=1;k<=i;k++) tmp=max(tmp,solve_g(k-1,i-k));
    ans[i]+=0.01*p[2]*tmp;
    //D case
    ans[i]+=0.01*p[3]*solve_ans(i-1);
    return ans[i];
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<=3;i++) scanf("%d",&p[i]);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            for(int k=0;k<=n;k++)
                dp[i][j][k]=-1.0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            f[i][j]=g[i][j]=-1.0;
    for(int i=0;i<=n;i++) ans[i]=-1.0;
    printf("%.10f\n",solve_ans(n));
    return 0;
}
