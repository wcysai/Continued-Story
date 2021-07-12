#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n,K,a[MAXN];
ll dp[MAXN][3][11][11];
char dj[MAXN][3][11][11];
char dk[MAXN][3][11][11];
char dl[MAXN][3][11][11];
void upd(int ni,int nj,int nk,int nl,int x,int y,int z,ll val)
{
    if(val>dp[ni][nj][nk][nl])
    {
        dp[ni][nj][nk][nl]=val;
        dj[ni][nj][nk][nl]=x;
        dk[ni][nj][nk][nl]=y;
        dl[ni][nj][nk][nl]=z;
    }
}
int main()
{
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<=10;k++)
                for(int l=0;l<=10;l++)
                    dp[i][j][k][l]=-INF;
    dp[1][0][0][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<=K;k++)
            {
                for(int l=0;l<=K;l++)
                {
                    if(dp[i][j][k][l]==-INF) continue;
                    if(j==0)
                    {
                        upd(i+1,0,k,l,0,0,0,dp[i][j][k][l]);
                        upd(i+1,1,k,l,1,0,0,dp[i][j][k][l]+a[i]);
                        upd(i+1,2,k,l,2,0,0,dp[i][j][k][l]+a[i]);
                        if(k<K)
                        {
                            upd(i+1,1,k+1,l,1,1,0,dp[i][j][k][l]);
                            upd(i+1,2,k+1,l,2,1,0,dp[i][j][k][l]);
                        }
                        if(l<K)
                        {
                            upd(i+1,0,k,l+1,0,0,1,dp[i][j][k][l]+a[i]);
                        }
                    }
                    else if(j==1)
                    {
                        upd(i+1,1,k,l,0,0,0,dp[i][j][k][l]+a[i]);
                        upd(i+1,2,k,l,1,0,0,dp[i][j][k][l]+a[i]);
                        if(k<K)
                        {
                            upd(i+1,1,k+1,l,0,1,0,dp[i][j][k][l]);
                        }
                    }
                    else
                    {
                        upd(i+1,2,k,l,0,0,0,dp[i][j][k][l]);
                        if(l<K) upd(i+1,2,k,l+1,0,0,1,dp[i][j][k][l]+a[i]);
                    }
                }
            }
        }
    }
    ll ans=0;
    int ni=-1,nj=-1,nk=-1,nl=-1;
    vector<int> in,out;
    for(int k=0;k<=K;k++)
    {
        if(dp[n+1][2][k][k]>ans)
        {
            ans=dp[n+1][2][k][k];
            ni=n+1; nj=2; nk=k; nl=k;
        }
    }
    printf("%lld ",ans);
    int L,R;
    while(ni>1)
    {
        int x=dj[ni][nj][nk][nl];
        int y=dk[ni][nj][nk][nl];
        int z=dl[ni][nj][nk][nl];
        ni--; nj-=x; nk-=y; nl-=z;
        if(x)
        {
            if(x==2)
            {
                L=R=ni;
            }
            else if(x==1)
            {
                if(nj==1) R=ni;
                else L=ni;
            }
        }
        if(y) in.push_back(ni);
        if(z) out.push_back(ni);
    }
    printf("%d\n",(int)in.size());
    assert(in.size()==out.size());
    for(int i=0;i<(int)in.size();i++) printf("%d %d\n",in[i],out[i]);
    printf("%d %d\n",L,R);
    return 0;
}