#include<bits/stdc++.h>
#define maxn 2005
using namespace std;
int n,m;
char s[maxn][maxn];
int cnt;
vector<int> R[maxn],C[maxn];
int fa[maxn*maxn],sz[maxn*maxn];
int ans,ansx,ansy;
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%s",s[i]+1);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)if(s[i][j]=='+')
        {
            ++cnt;
            R[i].push_back(cnt);
            C[j].push_back(cnt);
        }
    for(int i=1;i<=cnt;++i)fa[i]=i,sz[i]=1;
    for(int i=1;i<=n;++i)if(R[i].size())
    {
        for(int j=1;j<R[i].size();++j)
        {
            int x=R[i][j],y=R[i][j-1];
            if(find(x)!=find(y))
            {
                int u=find(x),v=find(y);
                fa[u]=v;
                sz[v]+=sz[u];
            }
        }
    }
    for(int i=1;i<=m;++i)if(C[i].size())
    {
        for(int j=1;j<C[i].size();++j)
        {
            int x=C[i][j],y=C[i][j-1];
            if(find(x)!=find(y))
            {
                int u=find(x),v=find(y);
                fa[u]=v;
                sz[v]+=sz[u];
            }
        }
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)if(s[i][j]=='.')
        {
            int t=0;
            if(R[i].size()&&C[j].size())
            {
                if(find(R[i][0])==find(C[j][0]))t+=sz[find(R[i][0])];
                else t+=sz[find(R[i][0])]+sz[find(C[j][0])];
            }
            else if(R[i].size())
            {
                t+=sz[find(R[i][0])];
            }
            else if(C[j].size())
            {
                t+=sz[find(C[j][0])];
            }
            //cerr<<i<<" "<<j<<" "<<t<<endl;
            if(t>ans)
            {
                ans=t;
                ansx=i;ansy=j;
            }
        }
    if(!ans)puts("0");
    else printf("%d\n%d %d\n",ans,ansx,ansy);
}