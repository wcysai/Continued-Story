#include<bits/stdc++.h>
#define maxn 405
using namespace std;
int n;
int d[maxn*2],t1[maxn*2],t2[maxn*2],t3[maxn*2];
int s1[maxn*2],s2[maxn*2],s3[maxn*2];
int ban[3][maxn][maxn];
void solve(int id,int *s,int *t,int *ss,int *tt)
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=n;++k)if(k!=j)
            {
                int L1=0,R1=0,L2=0,R2=0;
                if(j<=i)
                {
                    L1=s[i-1]-s[j-1],R1=s[i-1]-s[j-1]+t[i];
                }
                else
                {
                    L1=s[i+n-1]-s[j-1],R1=s[i+n-1]-s[j-1]+t[i+n];
                }
                if(k<=i)
                {
                    L2=ss[i-1]-ss[k-1],R2=ss[i-1]-ss[k-1]+tt[i];
                }
                else
                {
                    L2=ss[i+n-1]-ss[k-1],R2=ss[i+n-1]-ss[k-1]+tt[i+n];
                }
                if(L1>L2)swap(L1,L2),swap(R1,R2);
                //if(id==1&&i==2&&j==1&&k==5)cerr<<"!!!!!!!!!!!!!!!"<<L1<<" "<<R1<<" "<<L2<<" "<<R2<<endl;
                if(R1>L2)ban[id][j][k]=1;
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&d[i]);
    for(int i=1;i<=n;++i)scanf("%d",&t1[i]);
    for(int i=1;i<=n;++i)scanf("%d",&t2[i]);
    for(int i=1;i<=n;++i)scanf("%d",&t3[i]);
    for(int i=1;i<=n;++i)
    {
        t1[i+n]=t1[i];t2[i+n]=t2[i];t3[i+n]=t3[i];d[i+n]=d[i];
    }
    for(int i=1;i<=2*n;++i)
    {
        s1[i]=s1[i-1]+t1[i]+d[i];
        s2[i]=s2[i-1]+t2[i]+d[i];
        s3[i]=s3[i-1]+t3[i]+d[i];
    }
    solve(0,s1,t1,s2,t2);
    solve(1,s2,t2,s3,t3);
    solve(2,s1,t1,s3,t3);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)if(j!=i)
        {
            for(int k=1;k<=n;++k)if(k!=i&&k!=j)
            {
                if(!ban[0][i][j]&&!ban[1][j][k]&&!ban[2][i][k])
                {
                    printf("%d %d %d\n",i,j,k);
                    return 0;
                }
            }
        }
    }
    puts("impossible");
}