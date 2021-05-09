#include<bits/stdc++.h>
#define maxn 505
using namespace std;
typedef long long ll;
const ll inf = 1000000000;
int n;
ll a[maxn][maxn],b[maxn][maxn];
ll ans[5][2][2][2];//field, left-side, right-side, core
ll dp[maxn][maxn];
ll umax(ll a,ll b,ll c)
{
    return max(max(a,b),c);
}
ll work1(int l,int r,int c)
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)b[i][j]=a[i][j];
    if(!l)
    {
        for(int i=2;i<n;++i)b[i][i]=-inf;
    }
    if(!r)
    {
        for(int i=2;i<n;++i)b[i][n-i+1]=-inf;
    }
    if(!c)
    {
        b[(n+1)/2][(n+1)/2]=-inf;
    }
    for(int i=0;i<=n+1;++i)
        for(int j=0;j<=n+1;++j)dp[i][j]=-inf;
    dp[1][1]=0;
    for(int j=1;j<=n;++j)
        for(int i=1;i<=n;++i)
        {
            if(i==1&&j==1)continue;
            dp[i][j]=umax(dp[i-1][j-1],dp[i][j-1],dp[i+1][j-1])+b[i][j];
        }
    return dp[1][n];
}
ll work2(int l,int r,int c)
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)b[i][j]=a[i][j];
    if(!r)
    {
        for(int i=2;i<n;++i)b[i][i]=-inf;
    }
    if(!l)
    {
        for(int i=2;i<n;++i)b[i][n-i+1]=-inf;
    }
    if(!c)
    {
        b[(n+1)/2][(n+1)/2]=-inf;
    }
    for(int i=0;i<=n+1;++i)
        for(int j=0;j<=n+1;++j)dp[i][j]=-inf;
    dp[1][n]=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        {
            if(i==1&&j==n)continue;
            dp[i][j]=umax(dp[i-1][j],dp[i-1][j-1],dp[i-1][j+1])+b[i][j];
        }
    return dp[n][n];
}
ll work3(int l,int r,int c)
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)b[i][j]=a[i][j];
    if(!l)
    {
        for(int i=2;i<n;++i)b[i][i]=-inf;
    }
    if(!r)
    {
        for(int i=2;i<n;++i)b[i][n-i+1]=-inf;
    }
    if(!c)
    {
        b[(n+1)/2][(n+1)/2]=-inf;
    }
    for(int i=0;i<=n+1;++i)
        for(int j=0;j<=n+1;++j)dp[i][j]=-inf;
    dp[n][n]=0;
    for(int j=n;j>=1;--j)
        for(int i=1;i<=n;++i)
        {
            if(i==n&&j==n)continue;
            dp[i][j]=umax(dp[i+1][j+1],dp[i][j+1],dp[i-1][j+1])+b[i][j];
        }
    return dp[n][1];
}
ll work4(int l,int r,int c)
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)b[i][j]=a[i][j];
    if(!r)
    {
        for(int i=2;i<n;++i)b[i][i]=-inf;
    }
    if(!l)
    {
        for(int i=2;i<n;++i)b[i][n-i+1]=-inf;
    }
    if(!c)
    {
        b[(n+1)/2][(n+1)/2]=-inf;
    }
    for(int i=0;i<=n+1;++i)
        for(int j=0;j<=n+1;++j)dp[i][j]=-inf;
    dp[n][1]=0;
    for(int i=n;i>=1;--i)
        for(int j=1;j<=n;++j)
        {
            if(i==n&&j==1)continue;
            dp[i][j]=umax(dp[i+1][j],dp[i+1][j-1],dp[i+1][j+1])+b[i][j];
        }
    return dp[1][1];
}
int main()
{
    scanf("%d",&n);
    ++n;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)scanf("%lld",&a[i][j]);
    ll tmp=a[1][1]+a[1][n]+a[n][1]+a[n][n];
    a[1][1]=a[1][n]=a[n][1]=a[n][n]=0;
    for(int l=0;l<2;++l)
        for(int r=0;r<2;++r)
            for(int c=0;c<=min(l,r);++c)
            {
                ans[1][l][r][c]=work1(l,r,c);
                ans[2][l][r][c]=work2(l,r,c);
                ans[3][l][r][c]=work3(l,r,c);
                ans[4][l][r][c]=work4(l,r,c);
                //printf("ans[1][%d][%d][%d]=%lld\n",l,r,c,ans[1][l][r][c]);
            }
    ll res=0;
    for(int x1=0;x1<2;++x1)
        for(int x2=0;x2<2;++x2)
            for(int x3=0;x3<2;++x3)
                for(int x4=0;x4<2;++x4)
                    for(int cb=1;cb<=4;++cb)
                    {
                        res=max(res,ans[1][x1][x2^1][(cb==1)?1:0]+ans[2][x2][x3^1][(cb==2)?1:0]+ans[3][x3][x4^1][(cb==3)?1:0]+ans[4][x4][x1^1][(cb==4)?1:0]);
                    }
    printf("%lld\n",res+tmp);
}