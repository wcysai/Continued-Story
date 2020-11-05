#include<bits/stdc++.h>
#define maxn 405
using namespace std;
const int inf = 1000000007;
int n,m;
char a[maxn][maxn];
int ans[maxn][maxn];
const int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int dis[maxn][maxn];
int ax[maxn*maxn],ay[maxn*maxn],used[maxn*maxn],cnt;
void dfs()
{
    int C=cnt;
    for(int i=1;i<=C;++i)if(!used[i])
    {
        int x=ax[i],y=ay[i];
        if(dis[x][y]!=inf)continue;
        if(a[x][y]=='Z')dis[x][y]=min(dis[x][y],min(max(dis[x][y-1],dis[x-1][y])+2,max(dis[x+1][y],dis[x][y+1])+2));
        else dis[x][y]=min(dis[x][y],min(max(dis[x][y-1],dis[x+1][y])+2,max(dis[x-1][y],dis[x][y+1])+2));
        ans[x][y]=min(ans[x][y],dis[x][y]);
        used[i]=1;
        for(int k=0;k<4;++k)
        {
            x+=dx[k];y+=dy[k];
            //cerr<<k<<" "<<x<<" "<<y<<" "<<dis[x][y]<<endl;
            if(dis[x][y]!=inf)
            {
                x-=dx[k];y-=dy[k];
                continue;
            }
            if(a[x][y]=='Z')
            {
                if((dis[x+1][y]!=inf&&dis[x][y+1]!=inf)||(dis[x-1][y]!=inf&&dis[x][y-1]!=inf))
                {
                    ++cnt;
                    ax[cnt]=x;ay[cnt]=y;
                }
            }
            else
            {
                if((dis[x+1][y]!=inf&&dis[x][y-1]!=inf)||(dis[x-1][y]!=inf&&dis[x][y+1]!=inf))
                {
                    ++cnt;
                    ax[cnt]=x;ay[cnt]=y;
                }
            }
            x-=dx[k];y-=dy[k];
        }
        dfs();
        dis[x][y]=inf;
        cnt=C;
        used[i]=0;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%s",a[i]+1);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)ans[i][j]=inf,dis[i][j]=inf;
    if(a[1][1]=='Z')
    {
        ++cnt;ax[cnt]=1;ay[cnt]=1;
    }
    if(a[n][1]=='N')
    {
        ++cnt;ax[cnt]=n;ay[cnt]=1;
    }
    if(a[1][m]=='N')
    {
        ++cnt;ax[cnt]=1;ay[cnt]=m;
    }
    if(a[n][m]=='Z')
    {
        ++cnt;ax[cnt]=n;ay[cnt]=m;
    }
    dfs();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)if(ans[i][j]>=inf)ans[i][j]=-1;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)printf("%d%c",ans[i][j],(j==m)?'\n':' ');
}
