#include<bits/stdc++.h>
#define MAXN 25
#define MAXM (1<<18)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int d[MAXN][MAXN];
int s[MAXM][MAXN],t[MAXM][MAXN];
void floyd_warshall()
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
          for(int j=0;j<n;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
int main()
{
    int testcase=0;
    while(scanf("%d%d",&n,&m)==2)
    {
        testcase++;
        for(int i=0;i<n;i++) 
            for(int j=0;j<n;j++)
                d[i][j]=(i==j?0:INF);
        for(int i=0;i<m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            d[u][v]=d[v][u]=min(d[u][v],w);
        }
        floyd_warshall();
        for(int i=0;i<(1<<(n-2));i++)
        {
            if(__builtin_popcount(i)>(n-1)/2) continue;
            for(int j=0;j<n-2;j++)
                s[i][j]=t[i][j]=INF;
        }
        s[0][0]=0;
        for(int i=0;i<(1<<(n-2));i++)
        {
            if(__builtin_popcount(i)>(n-1)/2) continue;
            for(int j=0;j<n-2;j++)
            {
                if(s[i][j]==INF) continue;
                for(int k=0;k<n-2;k++)
                {
                    if(i&(1<<k)) continue;
                    int dist=(i==0?d[0][k+1]:d[j+1][k+1]);
                    s[i^(1<<k)][k]=min(s[i^(1<<k)][k],s[i][j]+dist);
                }
            }
        }
        t[0][0]=0;
        for(int i=0;i<(1<<(n-2));i++)
        {
            if(__builtin_popcount(i)>(n-1)/2) continue;
            for(int j=0;j<n-2;j++)
            {
                if(t[i][j]==INF) continue;
                for(int k=0;k<n-2;k++)
                {
                    if(i&(1<<k)) continue;
                    int dist=(i==0?d[n-1][k+1]:d[j+1][k+1]);
                    t[i^(1<<k)][k]=min(t[i^(1<<k)][k],t[i][j]+dist);
                }
            }
        }
        int ans=INF,k=(n-2)/2;
        if(k==0) ans=2*(d[0][1]+d[1][2]);
        else
        {
            int comb=(1<<k)-1;
            while(comb<(1<<(n-2)))
            {
                int nmask=(1<<(n-2))-1-comb;
                int res1=INF,res2=INF;
                for(int i=0;i<n-2;i++) 
                {
                    if(!(comb&(1<<i))) continue;
                    for(int j=0;j<n-2;j++)
                    {
                        if(!(nmask&(1<<j))) continue;
                        res1=min(res1,s[comb][i]+d[i+1][j+1]+t[nmask][j]);
                    } 
                }
                for(int i=0;i<n-2;i++) 
                {
                    if(!(nmask&(1<<i))) continue;
                    for(int j=0;j<n-2;j++)
                    {
                        if(!(comb&(1<<j))) continue;
                        res2=min(res2,s[nmask][i]+d[i+1][j+1]+t[comb][j]);
                    } 
                }
                ans=min(ans,res1+res2);
                int x=comb&-comb,y=comb+x;
                comb=((comb&~y)/x>>1)|y;
            }
        }
        printf("Case %d: %d\n",testcase,ans);
    }
    return 0;
}