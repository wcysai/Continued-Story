#include<bits/stdc++.h>
#define maxn 20005
using namespace std;
int T;
int k,n,a[maxn],node,cnt;
vector<int> h[maxn];
int ch[maxn][10];
int g[maxn][10];
void dfs(int &u,int dep,int ansh)
{
    u=++node;
    h[dep].push_back(u);
    if(dep==ansh)
    {
        for(int i=1;i<k;++i)g[u][i]=a[++cnt];
    }
    else
    {
        dfs(ch[u][1],dep+1,ansh);
        for(int i=1;i<k;++i)
        {
            g[u][i]=a[++cnt];
            dfs(ch[u][i+1],dep+1,ansh);
        }
    }
}
int main()
{
    scanf("%d",&T);
    for(int Cas=1;Cas<=T;++Cas)
    {
        scanf("%d%d",&k,&n);
        memset(ch,0,sizeof(ch));
        memset(g,0,sizeof(g));
        for(int i=0;i<=n;++i)h[i].clear();
        for(int i=1;i<=n;++i)scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        printf("Case #%d:\n",Cas);
        if(n%(k-1)!=0)
        {
            puts("INVALID");
            continue;
        }
        int kpw=1,ansh=-1;
        for(int h=0;h<=20;++h)
        {
            kpw*=k;
            if((kpw-1)>n)break;
            if((kpw-1)==n)
            {
                ansh=h;
                break;
            }
        }
        if(ansh==-1)
        {
            puts("INVALID");
            continue;
        }
        int rt=0;
        node=cnt=0;
        dfs(rt,0,ansh);
        for(int i=0;i<=n;++i)if(h[i].size())
        {
            for(int u:h[i])
            {
                for(int j=1;j<k;++j)
                {
                    printf("%d",g[u][j]);
                    if(j==k-1)printf("; ");
                    else printf(" ");
                }
            }
            puts("");
        }
    }
}