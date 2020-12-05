#include<bits/stdc++.h>
#define MAXN 55
#define MAXM 4005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,sz;
int a[MAXM],b[MAXM],c[MAXM];
vector<int> dis;
int cnt[MAXN][MAXN][MAXM];//cnt(i,j,k): number of cars with a=i,b=j,cost=k
int f[MAXN][MAXN][MAXM];//f(i,j,k): maximum gain with interval [l,r], minimum=k
int pref[MAXN][MAXN][MAXM];//position of choice of minimum for f(i,j,k) to achieve minimum
int g[MAXN][MAXN][MAXM];//g(i,j,k): maximum gain with interval [l,r], minimum>=k
int preg[MAXN][MAXN][MAXM];//choice of value for g(i,j,k) to achieve minimum
int cost[MAXN];
int query_cnt(int l,int r,int p,int c)//a in [l,p], b in [p,r], cost in [c,sz]
{
    return cnt[p][r][sz]-cnt[l-1][r][sz]-cnt[p][p-1][sz]-cnt[p][r][c-1]+cnt[l-1][p-1][sz]+cnt[l-1][r][c-1]+cnt[p][p-1][c-1]-cnt[l-1][p-1][c-1];
}
void recover_cost(int l,int r,int c,int flag=0)
{
    if(l>r) return;
    if(flag==1) {recover_cost(l,r,preg[l][r][c]); return;}
    int pos=pref[l][r][c];
    cost[pos]=dis[c-1];
    recover_cost(l,pos-1,c,1); recover_cost(pos+1,r,c,1);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) 
    {
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
        dis.push_back(c[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    for(int i=1;i<=m;i++)
    {
        c[i]=lower_bound(dis.begin(),dis.end(),c[i])-dis.begin()+1;
        cnt[a[i]][b[i]][c[i]]++;
    }
    sz=(int)dis.size();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=sz;k++)
                cnt[i][j][k]+=cnt[i][j][k-1];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=sz;k++)
                cnt[i][j][k]+=cnt[i-1][j][k];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=sz;k++)
                cnt[i][j][k]+=cnt[i][j-1][k];
    memset(pref,-1,sizeof(pref));
    memset(preg,-1,sizeof(preg));
    for(int i=1;i<=n;i++) 
    {
        for(int j=1;j<=sz;j++)
        {
            f[i][i][j]=query_cnt(i,i,i,j)*dis[j-1];
            pref[i][i][j]=i;
        }
        g[i][i][sz]=f[i][i][sz],preg[i][i][sz]=sz;
        for(int j=sz-1;j>=1;j--) 
        {
            if(f[i][i][j]>g[i][i][j+1])
            {
                g[i][i][j]=f[i][i][j];
                preg[i][i][j]=j;
            }
            else
            {
                g[i][i][j]=g[i][i][j+1];
                preg[i][i][j]=preg[i][i][j+1];
            }
        }
    }
    for(int len=2;len<=n;len++)
        for(int i=1;i+len-1<=n;i++)
        {
            int j=i+len-1;
            for(int k=1;k<=sz;k++)//calculate f(i,j,k)
            {
                f[i][j][k]=0; pref[i][j][k]=i;
                for(int p=i;p<=j;p++)//enumerate position of minimum
                {
                    if(g[i][p-1][k]+g[p+1][j][k]+query_cnt(i,j,p,k)*dis[k-1]>f[i][j][k])
                    {
                        f[i][j][k]=g[i][p-1][k]+g[p+1][j][k]+query_cnt(i,j,p,k)*dis[k-1];
                        pref[i][j][k]=p;
                    }
                }
            }
            g[i][j][sz]=f[i][j][sz],preg[i][j][sz]=sz;
            for(int k=sz-1;k>=1;k--) 
            {
                if(f[i][j][k]>g[i][j][k+1])
                {
                    g[i][j][k]=f[i][j][k];
                    preg[i][j][k]=k;
                }
                else
                {
                    g[i][j][k]=g[i][j][k+1];
                    preg[i][j][k]=preg[i][j][k+1];
                }
            }
        }
    int ans=0,id=0;
    for(int i=1;i<=sz;i++) if(f[1][n][i]>ans) {ans=f[1][n][i]; id=i;}
    recover_cost(1,n,id);
    printf("%d\n",ans);
    for(int i=1;i<=n;i++) printf("%d ",cost[i]);
    puts("");
    return 0;
}