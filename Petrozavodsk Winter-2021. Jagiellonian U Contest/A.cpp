#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define MAXK 1005
#define INF 1000000000
#define MOD1 1000000007
#define MOD2 998244353
#define BASE1 233
#define BASE2 19260817
#define F first
#define S second
#define is_same dsakodas
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int tot,n,m,k;
char s[MAXN],t[MAXN];
P hs[MAXN],ht[MAXN];
int p1[MAXN],p2[MAXN];
bool is_same(int l1,int r1,int l2,int r2)
{
    P p,q;
    p.F=(hs[r1].F-1LL*hs[l1-1].F*p1[r1-l1+1])%MOD1;
    if(p.F<0) p.F+=MOD1;
    q.F=(ht[r2].F-1LL*ht[l2-1].F*p1[r2-l2+1])%MOD1;
    if(q.F<0) q.F+=MOD1;
    if(p.F!=q.F) return false;
    p.S=(hs[r1].S-1LL*hs[l1-1].S*p2[r1-l1+1])%MOD2;
    if(p.S<0) p.S+=MOD2;
    q.S=(ht[r2].S-1LL*ht[l2-1].S*p2[r2-l2+1])%MOD2;
    if(q.S<0) q.S+=MOD2;
    if(p.S!=q.S) return false;
    return true;
}
int max_prolong(int x,int y)
{
    int len=min(n-x,m-y);
    int l=0,r=len+1;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(is_same(x+1,x+mid,y+1,y+mid)) l=mid; else r=mid;
    }
    return l;
}
int dp[MAXK][2*MAXK];
int pre[MAXK][2*MAXK];
//dp[i][d] - with i steps, the maximum x such that (x,x+d) is reachable 
int main()
{
    p1[0]=1;
    for(int i=1;i<=1000000;i++) p1[i]=1LL*p1[i-1]*BASE1%MOD1;
    p2[0]=1;
    for(int i=1;i<=1000000;i++) p2[i]=1LL*p2[i-1]*BASE2%MOD2;
    scanf("%d",&tot);
    while(tot--)
    {
        scanf("%d%d%d",&n,&m,&k);
        scanf("%s",s+1); 
        scanf("%s",t+1);
        for(int i=1;i<=max(n,m);i++)
        {
            if(i<=n)
            {
                hs[i].F=(1LL*hs[i-1].F*BASE1+(s[i]-'a'+1))%MOD1;
                hs[i].S=(1LL*hs[i-1].S*BASE2+(s[i]-'a'+1))%MOD2;
            }
            if(i<=m)
            {
                ht[i].F=(1LL*ht[i-1].F*BASE1+(t[i]-'a'+1))%MOD1;
                ht[i].S=(1LL*ht[i-1].S*BASE2+(t[i]-'a'+1))%MOD2;
            }
        }
        int need=m-n;
        if(max(need,-need)>k) {puts("NO"); continue;}
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<=k;i++)
            for(int j=1000-i;j<=1000+i;j++)
                pre[i][j]=-2;
        dp[0][1000]=max_prolong(0,0);
        int now=-1;
        for(int i=0;i<=k;i++)
        {
            if(dp[i][1000+need]==n) {now=i; break;}
            for(int j=1000-i;j<=1000+i;j++)
            {
                if(dp[i][j]==-1) continue;
                int d=j-1000,x=dp[i][j];
                if(x<n)
                {
                    int delta=max_prolong(x+1,x+d);
                    if(delta+x+1>dp[i+1][j-1])
                    {
                        dp[i+1][j-1]=delta+x+1;
                        pre[i+1][j-1]=-1;
                    }
                }
                if(x+d<m)
                {
                    int delta=max_prolong(x,x+d+1);
                    if(delta+x>dp[i+1][j+1])
                    {
                        dp[i+1][j+1]=delta+x;
                        pre[i+1][j+1]=1;
                    }
                }
                if(x<n&&x+d<m)
                {
                    int delta=max_prolong(x+1,x+d+1);
                    if(delta+x+1>dp[i+1][j])
                    {
                        dp[i+1][j]=delta+x+1;
                        pre[i+1][j]=0;
                    }
                }
            }
        }
        if(dp[k][1000+need]==n) now=k;
        if(now==-1)
        {
            puts("NO");
            continue;
        }
        puts("YES");
        printf("%d\n",now);
        int i=now,d=1000+need;
        while(i)
        {
            assert(pre[i][d]!=-2);
            int x=dp[i][d];
            if(pre[i][d]==-1)
            {
                int pos=dp[i-1][d+1];
                printf("DELETE %d\n",pos+1);
                i--; d++;
            }
            else if(pre[i][d]==1)
            {
                int pos=dp[i-1][d-1];
                printf("INSERT %d %c\n",pos+1,t[pos+(d-1000-1)+1]);
                i--; d--;
            }
            else
            {
                int pos=dp[i-1][d];
                printf("REPLACE %d %c\n",pos+1,t[pos+d-1000+1]);
                i--;
            }
        }
    }
    return 0;
}