#include<bits/stdc++.h>
#define maxn 500005
using namespace std;
int n;
int a[maxn],Log[maxn];
int orv[maxn][22];
int g[maxn];
int getor(int l,int r)
{
    int k=Log[r-l+1];
    return orv[l][k]|orv[(r-(1<<k))+1][k];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)Log[i]=log2(i);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)orv[i][0]=a[i];
    for(int j=1;j<=20;++j)
    {
        for(int i=1;i+(1<<j)-1<=n;++i)orv[i][j]=orv[i][j-1]|orv[i+(1<<(j-1))][j-1];
    }
    for(int l=1;l<=n;++l)
    {
        int r=l;
        while(r<=n)
        {
            int L=r,R=n,ans=r;
            int x=getor(l,r);
            while(L<=R)
            {
                int M=(L+R)>>1;
                if(getor(l,M)==x)ans=M,L=M+1;
                else R=M-1;
            }
            g[r-l+1]=max(g[r-l+1],x);
            r=ans+1;
        }
    }
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        ans=max(ans,g[i]);
        printf("%d\n",ans);
    }
}