#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int a[5],b[5],hasa[5],hasb[5];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int x,i=1;i<=n;++i)
        {
            scanf("%d",&x);
            a[x]=1;
        }
        for(int x,i=1;i<=m;++i)
        {
            scanf("%d",&x);
            b[x]=1;
        }
        int ans=0;
        for(int S=0;S<16;++S)
        {
            memset(hasa,0,sizeof(hasa));
            memset(hasb,0,sizeof(hasb));
            for(int i=0;i<4;++i)if(S&(1<<i))
            {
                int x=i/2,y=i%2;
                hasa[x]=1;hasb[y]=1;
            }
            /*for(int i=0;i<2;++i)cerr<<hasa[i]<<" ";
            cerr<<endl;
            for(int i=0;i<2;++i)cerr<<hasb[i]<<" ";
            cerr<<endl;*/
            bool ok=1;
            for(int i=0;i<2;++i)if(hasa[i]!=a[i])ok=0;
            for(int i=0;i<2;++i)if(hasb[i]!=b[i])ok=0;
            if(ok)ans++;
        }
        printf("%d\n",ans);
    }
}