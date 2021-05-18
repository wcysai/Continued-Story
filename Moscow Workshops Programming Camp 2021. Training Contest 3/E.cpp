#include<bits/stdc++.h>
#define MAXN 18
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<double> vec;
typedef vector<vec> mat;
int n,m,k;
int f[MAXN][MAXN];
double p;
double pv,ph;//proportion of vertical tiles when covering vertical/horizontal dominoes
ll dp[2*MAXN][MAXN][(1<<8)][65];
void add(ll &a,ll b) {a+=b;}
void calculate_dp()
{
    memset(dp,0,sizeof(dp));
    dp[0][0][0][0]=1;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int mask=0;mask<(1<<n);mask++)
            {
                for(int cnt=0;cnt<=64;cnt++)
                {
                    if(!dp[i][j][mask][cnt]) continue;
                    if(mask&(1<<j)||f[j][i]==1) {add(dp[i][j+1][mask&(~(1<<j))][cnt],dp[i][j][mask][cnt]); continue;}
                    //place a horizontal tile
                    if(i!=m-1&&f[j][i+1]!=1) add(dp[i][j+1][mask|(1<<j)][cnt],dp[i][j][mask][cnt]);
                    //place a vertical tile
                    if(j!=n-1&&!f[j+1][i]&&!(mask&(1<<(j+1)))) add(dp[i][j+1][mask|(1<<(j+1))][cnt+1],dp[i][j][mask][cnt]);
                }
            }
        }
        for(int mask=0;mask<(1<<n);mask++)
            for(int cnt=0;cnt<=64;cnt++)
                dp[i+1][0][mask][cnt]=dp[i][n][mask][cnt];
    }
}
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<A.size();i++)
        for(int k=0;k<B.size();k++)
            for(int j=0;j<B[0].size();j++)
                C[i][j]=(C[i][j]+A[i][k]*B[k][j]);
    return C;
}
mat get_pow(mat A,ll n)
{
    mat B(A.size(),vec(A.size()));
    for(int i=0;i<A.size();i++)
        B[i][i]=1;
    while(n>0)
    {
        if(n&1) B=mul(B,A);
        A=mul(A,A);
        n>>=1;
    }
    return B;
}
int main()
{
    scanf("%d%d",&n,&k);
    int need=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            scanf("%d",&f[i][j]);
            if(!f[i][j]) need++;
        }
    //calculate original
    m=n;
    calculate_dp();
    ll x=0,y=0;
    for(int cnt=0;cnt<=64;cnt++)
    {
        x+=dp[m][0][0][cnt]*cnt;
        y+=dp[m][0][0][cnt]*need/2;
    }
    p=(double)x/(double)y;
    if(k==0)
    {
        printf("%.10f\n",p);
        return 0;
    }
    //calculate horizontal
    for(int i=0;i<n;i++)
        for(int j=n;j<2*n;j++)
            f[i][j]=f[i][j-n];
    m=2*n; 
    calculate_dp();
    x=0; y=0;
    for(int cnt=0;cnt<=64;cnt++)
    {
        x+=dp[m][0][0][cnt]*cnt;
        y+=dp[m][0][0][cnt]*need;
    }
    ph=(double)x/(double)y;
    for(int i=0;i<n;i++)
        for(int j=0;j<i;j++)
        {
            swap(f[i][j],f[j][i]);
            swap(f[i][n+j],f[j][n+i]);
        }
    calculate_dp();
    x=0; y=0;
    for(int cnt=0;cnt<=64;cnt++)
    {
        x+=dp[m][0][0][cnt]*cnt;
        y+=dp[m][0][0][cnt]*need;
    }
    pv=1.0-(double)x/(double)y;
    mat A(2,vec(2));
    A[0][0]=pv; A[0][1]=1.0-pv; A[1][0]=ph; A[1][1]=1.0-ph;    
    A=get_pow(A,k-1);
    mat b(2,vec(1));
    b[0][0]=pv; b[1][0]=ph;
    b=mul(A,b);
    double ans=p*b[0][0]+(1.0-p)*b[1][0];
    printf("%.10f\n",ans);
    return 0;
}   