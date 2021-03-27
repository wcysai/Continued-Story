#include<bits/stdc++.h>
#define maxn 105
using namespace std;
int n,d;
int x[maxn],y[maxn];
int a[maxn][maxn];
int sqr(int x){return x*x;}
int p[maxn];
int ans;
vector<int> Ans;
int bel[maxn];
int main()
{
    scanf("%d%d",&n,&d);
    for(int i=1;i<=n;++i)scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)if(i!=j&&sqr(x[i]-x[j])+sqr(y[i]-y[j])<=d*d)a[i][j]=1;
    for(int i=1;i<=n;++i)p[i]=i;
    for(int T=1;T<=10000;++T)
    {
        random_shuffle(p+1,p+n+1);
        memset(bel,0,sizeof(bel));
        int tot=0;
        for(int i=1;i<=n;++i)
        {
            int x=p[i];
            bool yes=1;
            for(int j=1;j<i;++j)
            {
                int y=p[j];
                if(!bel[y])continue;
                if(!a[x][y])yes=0;
            }
            if(yes)
            {
                tot++;
                bel[x]=1;
            }
        }
        if(tot>Ans.size())
        {
            Ans.clear();
            for(int i=1;i<=n;++i)if(bel[i])Ans.push_back(i);
        }
    }
    printf("%d\n",Ans.size());
    for(int x:Ans)printf("%d ",x);
}