#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
string s;
string str[MAXN];
int fib[MAXN];
bool pre[MAXN][MAXM],suf[MAXN][MAXM];
ll dp[MAXN];
int nxt[MAXM],ex[MAXM];
void get_next(string &str)
{
    int i=0,j,po,len=(int)str.size();
    for(int i=0;i<=len;i++) nxt[i]=0;
    nxt[0]=len;
    while(str[i]==str[i+1]&&i+1<len) i++;
    nxt[1]=i;
    po=1;
    for(i=2;i<len;i++)
    {
        if(nxt[i-po]+i<nxt[po]+po) nxt[i]=nxt[i-po];
        else
        {
            j=nxt[po]+po-i;
            if(j<0) j=0;
            while(i+j<len&&str[j]==str[j+i]) j++;
            nxt[i]=j;
            po=i;
        }
    }
}
void exkmp(string &s1,string &s2)
{
    int i=0,j,po,len=(int)s1.size(),l2=(int)s2.size();
    for(int i=0;i<len;i++) ex[i]=0;
    get_next(s2);
    while(s1[i]==s2[i]&&i<l2&&i<len) i++;
    ex[0]=i;
    po=0;
    for(i=1;i<len;i++)
    {
        if(nxt[i-po]+i<ex[po]+po) ex[i]=nxt[i-po];
        else
        {
            j=ex[po]+po-i;
            if(j<0) j=0;
            while(i+j<len&&j<l2&&s1[j+i]==s2[j]) j++;
            ex[i]=j;
            po=i;
        }
    }
}
ll solve(int n)
{
    if(n==0)
    {
        if(s.size()==1&&s[0]=='0') return 1;
        else return 0;
    }
    if(n==1)
    {
        if(s.size()==1&&s[0]=='1') return 1;
        else return 0;
    }
    if(dp[n]!=-1) return dp[n];
    ll ans=solve(n-1)+solve(n-2);
    int x=n-1,y=n-2;
    if(x>25) x-=2*((x-24)/2);
    if(y>25) y-=2*((y-24)/2);
    for(int i=1;i<(int)min(fib[x]+1,(int)s.size());i++) 
    {
        if((int)s.size()-i>fib[y]) continue;
        if(suf[x][i]&&pre[y][(int)s.size()-i]) ans++;
    }
    return dp[n]=ans;
}
int main()
{
    fib[0]=fib[1]=1;
    for(int i=2;i<=25;i++) fib[i]=fib[i-1]+fib[i-2];
    str[0]="0"; str[1]="1";
    for(int i=2;i<=25;i++) str[i]=str[i-1]+str[i-2];
    int testcase=0;
    while(scanf("%d",&n)==1)
    {
        ++testcase;
        cin>>s;
        int sz=(int)s.size();
        memset(pre,false,sizeof(pre));
        memset(suf,false,sizeof(suf));
        for(int i=0;i<=25;i++)
        {
            pre[i][0]=suf[i][0]=true;
            exkmp(str[i],s);
            for(int j=0;j<min(sz,fib[i]);j++) if(ex[fib[i]-1-j]==j+1) {suf[i][j+1]=true;}
            exkmp(s,str[i]);
            for(int j=0;j<min(sz,fib[i]);j++) if(ex[sz-1-j]==j+1) {pre[i][j+1]=true;}
        }
        memset(dp,-1,sizeof(dp));
        printf("Case %d: %lld\n",testcase,solve(n));
    } 
    return 0;
}