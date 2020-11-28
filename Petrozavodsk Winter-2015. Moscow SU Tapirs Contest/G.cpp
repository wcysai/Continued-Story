#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define INV 500000004
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,p[MAXN],fact[MAXN];
bool vis[MAXN];
int num[MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int main()
{
    fact[0]=1;
    for(int i=1;i<=500000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    scanf("%d",&N);
    for(int i=1;i<=N;i++) scanf("%d",&p[i]);
    bool iseven=false;
    for(int i=1;i<=N;i++) vis[i]=false;
    for(int i=1;i<=N;i++)
    {
        if(!vis[i])
        {
            int now=i,cnt=0;
            while(!vis[now])
            {
                vis[now]=true;
                cnt++;
                now=p[now];
            }
            num[cnt]++;
        }
    }
    int ans=1;
    for(int i=1;i<=N;i++) 
    {
        if(num[i])
        {
            if(i%2==0) iseven=true;
            if(i%2==1&&num[i]>1) iseven=true;
            ans=1LL*ans*fact[num[i]]%MOD*pow_mod(i,num[i])%MOD;
        }
    }
    if(iseven) ans=1LL*ans*INV%MOD;
    printf("%d\n",ans);
    return 0;
}