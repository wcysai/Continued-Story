#include<bits/stdc++.h>
#define MAXM 1005
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m;
char s[MAXN],t[MAXM];
int dp[MAXM][MAXM];
int nxt[MAXN][26];
void upd(int &a,int b) {a=min(a,b);}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s+1); scanf("%s",t+1);
        n=strlen(s+1); m=strlen(t+1);
        for(int i=0;i<26;i++) nxt[n+1][i]=nxt[n+2][i]=n+1;
        for(int i=n;i>=1;i--)
        {
            for(int j=0;j<26;j++) nxt[i][j]=nxt[i+1][j];
            nxt[i][s[i]-'a']=i;
        }
        for(int i=0;i<=m;i++)
            for(int j=0;j<=m;j++)
                dp[i][j]=n+1;
        dp[0][0]=0;
        for(int i=0;i<m;i++)
            for(int j=0;j<=i;j++)
            {
                upd(dp[i+1][j],dp[i][j]);
                upd(dp[i+1][j+1],nxt[dp[i][j]+1][t[i+1]-'a']);
            }
        int ans=-1;
        for(int i=m;i>=0;i--) if(dp[m][i]<=n) {ans=i; break;}
        printf("%d\n",ans);
    }
    return 0;
}
