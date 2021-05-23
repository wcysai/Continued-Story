#include<bits/stdc++.h>
#define MAXM 55
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,r,m;
int t[MAXM],d[MAXM];
double prob[MAXM];
double dp[MAXM][MAXN];
const double eps=1e-12;
bool check(double est)
{
    for(int i=0;i<r-n;i++) dp[m+1][i]=0;
    for(int i=m;i>=1;i--)
    {
        for(int j=0;j<r-n;j++)
        {
            double cost=(i==m?n-t[i]:t[i+1]-t[i]);
            double res=(j+d[i]>=r-n?est:dp[i+1][j+d[i]]);
            dp[i][j]=prob[i]*(cost+dp[i+1][j])+(1.0-prob[i])*(min(est,(double)cost+d[i]+res));
        }
    }
    return dp[1][0]+t[1]+eps<est;
}
int main()
{
    scanf("%d%d%d",&n,&r,&m);
    for(int i=1;i<=m;i++) scanf("%d%lf%d",&t[i],&prob[i],&d[i]);
    double l=0.0,r=500000000.0;
    for(int i=0;i<200;i++)
    {
        double mid=(l+r)/2.0;
        if(check(mid)) r=mid; else l=mid;
    }
    printf("%.10f\n",l);
    return 0;
}