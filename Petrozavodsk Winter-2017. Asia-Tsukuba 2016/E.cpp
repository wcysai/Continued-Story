#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string str;
int n;
char ch[8]={'0','1','+','-','*','(',')','='};
vector<char> v;
string t;
bool flag;
int f[10],ans;
bool used[10];
//Q,E,T,F,N,B
int dp[10][40][40];
int solve(int type,int l,int r)
{
    if(r<0||l>=n)
    {
        if(type==5) return 0; else return -INF;
    }
    if(dp[type][l][r]!=INF) return dp[type][l][r];
    if(type==0)
    {
        if(l>r) return dp[type][l][r]=-INF;
        int res=-INF;
        for(int j=l;j<=r;j++) 
        {
            if(t[j]=='=')
            {
                int x=solve(1,l,j-1),y=solve(1,j+1,r);
                if(x!=-INF&&y!=-INF)
                {
                    if(x==y) return dp[type][l][r]=1; else return dp[type][l][r]=0;
                }
            }
        }
        return dp[type][l][r]=-INF;
    }
    else if(type==1)
    {
        if(l>r) return -INF;
        if(solve(2,l,r)!=-INF) return dp[type][l][r]=solve(2,l,r);
        for(int j=l;j<=r;j++)
        {
            if(t[j]=='+')
            {
                if(solve(1,l,j-1)!=-INF&&solve(2,j+1,r)!=-INF) return dp[type][l][r]=solve(1,l,j-1)+solve(2,j+1,r);
            }
        }
        for(int j=l;j<=r;j++)
        {
            if(t[j]=='-')
            {
                if(solve(1,l,j-1)!=-INF&&solve(2,j+1,r)!=-INF) return dp[type][l][r]=solve(1,l,j-1)-solve(2,j+1,r);
            }
        }
        return dp[type][l][r]=-INF;
    }
    else if(type==2)
    {
        if(l>r) return dp[type][l][r]=-INF;
        if(solve(3,l,r)!=-INF) return dp[type][l][r]=solve(3,l,r);
        for(int j=l;j<=r;j++)
        {
            if(t[j]=='*')
            {
                if(solve(2,l,j-1)!=-INF&&solve(3,j+1,r)!=-INF) return dp[type][l][r]=solve(2,l,j-1)*solve(3,j+1,r);
            }
        }
        return dp[type][l][r]=-INF;
    }
    else if(type==3)
    {
        if(l>r) return dp[type][l][r]=-INF;
        if(solve(4,l,r)!=-INF) return dp[type][l][r]=solve(4,l,r);
        if(t[l]=='-'&&solve(3,l+1,r)!=-INF) return dp[type][l][r]=-solve(3,l+1,r);
        if(t[l]=='('&&t[r]==')'&&solve(1,l+1,r-1)!=-INF) return dp[type][l][r]=solve(1,l+1,r-1);
        return dp[type][l][r]=-INF;
    }
    else if(type==4)
    {
        if(l>r) return dp[type][l][r]=-INF;
        if(l==r&&t[l]=='0') return dp[type][l][r]=0;
        if(t[l]!='1') return dp[type][l][r]=-INF;
        if(t[l]=='1'&&solve(5,l+1,r)!=-INF) return dp[type][l][r]=(1<<(r-l))+solve(5,l+1,r);
        return dp[type][l][r]=-INF;
    }
    else
    {
        if(l>r) return dp[type][l][r]=0;
        if(t[l]!='0'&&t[l]!='1') return dp[type][l][r]=-INF;
        if(solve(5,l+1,r)!=-INF&&t[l]=='0') return dp[type][l][r]=solve(5,l+1,r);
        if(solve(5,l+1,r)!=-INF&&t[l]=='1') return dp[type][l][r]=(1<<(r-l))+solve(5,l+1,r);
        return dp[type][l][r]=-INF;
    } 
}
void check()
{
    t=str;
    for(int i=0;i<n;i++)
    {
        if((t[i]>='a'&&t[i]<='z')||(t[i]>='A'&&t[i]<='Z'))
        {
            for(int j=0;j<(int)v.size();j++) if(v[j]==t[i]) {t[i]=ch[f[j]]; break;}
        }
    }
    for(int i=0;i<6;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
                dp[i][j][k]=INF;
    if(solve(0,0,n-1)==1) ans++;
}
void dfs(int now)
{
    if(now==(int)v.size())
    {
        check();
        return;
    }
    for(int i=0;i<8;i++)
    {
        if(!used[i])
        {
            f[now]=i;
            used[i]=true;
            dfs(now+1);
            used[i]=false;
        }
    }
}  
int main()
{
    cin>>str;
    n=(int)str.size();
    for(int i=0;i<n;i++)
    {
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')) v.push_back(str[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    if(v.size()>8)