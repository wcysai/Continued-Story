#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int dp[MAXN][MAXN][7];
int tmp[MAXN][MAXN];
vector<P> v;
string str;
//R,G,B,C,M,Y,K
map<char,int> id;
string t="RGBCMYK";
int solve(int l,int r,int c);
int canerase(int l,int r)
{
    if(tmp[l][r]!=-1) return tmp[l][r];
    if(l==r)
    {
        if(v[l].S>=m) return tmp[l][r]=1;
        else return tmp[l][r]=0;
    }
    for(int i=l;i<r;i++) 
        for(int c=0;c<7;c++)
            if(solve(l,i,c)+solve(i+1,r,c)>=m) return tmp[l][r]=1;
    if(v[l].F==v[r].F)
    {
        if(v[l].S+v[r].S+solve(l+1,r-1,v[l].F)>=m) return tmp[l][r]=1;
    } 
    return tmp[l][r]=0;    
}
int solve(int l,int r,int c)
{
    if(dp[l][r][c]!=-1) return dp[l][r][c];
    
    if(l==r)
    {
        if(v[l].F==c)
        {
            return dp[l][r][c]=v[l].S;
        }
        else 
        {
            return dp[l][r][c]=(v[l].S>=m?0:-INF);
        }
    }
    dp[l][r][c]=canerase(l,r)?0:-INF;
    for(int i=l;i<r;i++) 
        dp[l][r][c]=max(dp[l][r][c],solve(l,i,c)+solve(i+1,r,c));    
    if(v[l].F==v[r].F&&v[l].F==c)
    {
        dp[l][r][c]=max(dp[l][r][c],v[l].S+v[r].S+solve(l+1,r-1,c));
    } 
    return dp[l][r][c];
}
int main()
{
    id['R']=0; id['G']=1; id['B']=2; id['C']=3; id['M']=4; id['Y']=5; id['K']=6;
    cin>>str;
    scanf("%d",&m);
    n=(int)str.size();
    int c=-1,cnt=0;
    for(int i=0;i<n;i++)
    {
        if(c!=id[str[i]])
        {
            if(cnt) v.push_back(P(c,cnt));
            c=id[str[i]]; cnt=1;
        }
        else cnt++;
    }
    v.push_back(P(c,cnt));
    memset(dp,-1,sizeof(dp));
    memset(tmp,-1,sizeof(tmp));
    int sz=(int)v.size();
    if(canerase(0,sz-1)) puts("Yes"); else puts("No");
    return 0;
}