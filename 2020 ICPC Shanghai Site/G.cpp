#include<bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#define MAXN 505
#define MAXM 16
#define MAXD 366
#define MAXW 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,m,w;
string str;
int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int sum[13];
int dp[MAXD][MAXM],ndp[MAXD][MAXM];
int f[MAXM][MAXW],nf[MAXM][MAXW];
int parse(string &str)
{
    int m=(str[5]-'0')*10+(str[6]-'0');
    int d=(str[8]-'0')*10+(str[9]-'0');
    if(m==2&&d==29) return -1;
    return sum[m-1]+d;
}
void upd(int &x,int y) {x=max(x,y);}
vector<pair<int,P> > v;
vector<P> vm;
int main()
{
    scanf("%d",&t);
    sum[0]=0;
    for(int i=1;i<=12;i++) sum[i]=sum[i-1]+months[i];
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&w);
        v.clear();
        for(int i=0;i<n;i++)
        {
            cin>>str;
            int id=parse(str);
            int x,y;
            scanf("%d%d",&x,&y);
            if(id==-1) continue;
            v.push_back(make_pair(id,P(x,y)));
        }
        sort(v.begin(),v.end());
        for(int i=0;i<=365;i++)
            for(int j=0;j<=m;j++)
                dp[i][j]=((i==0&&j==0)?0:-INF);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=365;j++)
                for(int k=0;k<=m;k++)
                    ndp[j][k]=-INF;
            for(int j=0;j<=365;j++)
                for(int k=0;k<=m;k++)
                {
                    if(dp[j][k]==-INF) continue;
                    if(k==m) upd(ndp[j][k],dp[j][k]); else upd(ndp[j][k+1],dp[j][k]);
                    if(j+v[i].S.F<=v[i].F) upd(ndp[j+v[i].S.F][k],dp[j][k]+v[i].S.S);
                }
            swap(dp,ndp);
        }
        vm.clear();
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            vm.push_back(P(x,y));
        }
        for(int i=0;i<=m;i++)
            for(int j=0;j<=w;j++)
                f[i][j]=((i==0&&j==0)?0:-INF);
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<=m;j++)
                for(int k=0;k<=w;k++)
                    nf[j][k]=-INF;
            for(int j=0;j<=i;j++)
            {
                for(int k=0;k<=w;k++)
                {
                    if(f[j][k]==-INF) continue;
                    upd(nf[j][k],f[j][k]);
                    if(k+vm[i].F<=w) upd(nf[j+1][k+vm[i].F],f[j][k]+vm[i].S);
                }
            }
            swap(f,nf);
        }
        int ans=-INF;
        int tmp=-INF;
        for(int i=0;i<=m;i++)
        {
            int res=-INF;
            for(int j=0;j<=365;j++) res=max(res,dp[j][i]);
            for(int j=0;j<=w;j++) tmp=max(tmp,f[i][j]);
            ans=max(ans,res+tmp);
        }
        printf("%d\n",ans);
    }
    return 0;
}