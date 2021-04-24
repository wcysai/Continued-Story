#include<bits/stdc++.h>
#define MAXN 2505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,r,m,fact[MAXN],invf[MAXN];
int f[MAXN],g[MAXN];
int comb[MAXN][MAXN];
void add(int &a,int b) {a+=b; if(a>=m) a-=m;}
void dec(int &a,int b) {a-=b; if(a<0) a+=m;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=1LL*a*a%m;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d%d%d",&r,&n,&m);
    comb[0][0]=1%m;
    for(int i=1;i<=2021;i++)
    {
        comb[i][0]=comb[i][i]=1%m;
        for(int j=1;j<i;j++) comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%m;
    }
    if(n==r)
    {
        printf("%d\n",n==1?1%m:0);
        return 0;
    }
    f[0]=f[1]=1%m;
    for(int i=2;i<=n+1;i++)
        for(int j=0;j<=i-2;j++)
            add(f[i],1LL*f[j+1]*f[i-j-2]%m*comb[i-2][j]%m);
    int st=n-r+1;
    for(int i=n-r+1;i<=n;i++)
    {
        g[i]=f[i];
        int num=i-st;
        for(int k=1;k<=num;k++) dec(g[i],1LL*comb[num][k]*f[k+1]%m*g[i-k]%m);
    }
    printf("%d\n",g[n]%m);
    return 0;
}
