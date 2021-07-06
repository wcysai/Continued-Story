#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int t[7],a[4];
//-1: + -2: - -3: *
vector<int> v;
int dp[10][10];
int perm[4];
set<int> s;
int solve(int l,int r)
{
    if(l==r) return v[l];
    if(dp[l][r]!=-1) return dp[l][r];
    for(int i=r;i>=l;i--)
    {
        if(v[i]==-1)
        {
            return dp[l][r]=solve(l,i-1)+solve(i+1,r);
        }
        else if(v[i]==-2) 
        {
            return dp[l][r]=solve(l,i-1)-solve(i+1,r);
        }
    }
    for(int i=l;i<=r;i++)
    {
        if(v[i]==-3) return dp[l][r]=solve(l,i-1)*solve(i+1,r);
    }
    assert(0);//should not reach here
}
int go()
{
    v.clear();
    v.push_back(t[0]);
    for(int i=1;i<=5;i+=2)
    {
        if(t[i]==0)//blank
        {
            int x=v.back();
            v.pop_back();
            v.push_back(x*10+t[i+1]);
        }
        else
        {
            v.push_back(-t[i]);
            v.push_back(t[i+1]);
        }
    }
   // for(auto x:v) printf("%d ",x);
    int sz=(int)v.size();
    memset(dp,-1,sizeof(dp));
   // printf("%d\n",solve(0,sz-1));
    return solve(0,sz-1);
}
int main()
{
    scanf("%d%d%d%d",&a[0],&a[1],&a[2],&a[3]);
    for(int i=0;i<4;i++) perm[i]=i;
    do
    {
        for(int i=0;i<4;i++) t[2*i]=a[perm[i]];
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                for(int k=0;k<4;k++)
                {
                    if(i==0&&j==0&&k==0) continue;
                    t[1]=i;
                    t[3]=j;
                    t[5]=k;
                    int res=go();
                    if(res>=0) s.insert(res);
                }
    } while (next_permutation(perm,perm+4));
    printf("%d\n",(int)s.size());
    return 0;
}