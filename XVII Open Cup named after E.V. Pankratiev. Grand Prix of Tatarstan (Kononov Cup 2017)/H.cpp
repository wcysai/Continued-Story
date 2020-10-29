#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define abs afskoa
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot;
int type[MAXN];
vector<vector<int> >v;
int dp[MAXN][MAXN];
int abs(int x) {return max(-x,x);}             
int solve(int st,int ed,vector<int> &v)
{
    int l=INF,r=-INF,ans=0;
    multiset<int> ms;
    vector<P> tmp;
    for(int i=0;i<(int)v.size();i++)
    {
        int lb=v[i],rb=m-v[i]+1;
        if(lb>rb) swap(lb,rb);
        l=min(l,lb); r=max(r,lb);
        tmp.push_back(P(lb,rb));
        ms.insert(lb);
    }
    ans=abs(st-l)+(r-l)+abs(ed-r);
    ans=min(ans,abs(st-r)+(r-l)+abs(ed-l));
    sort(tmp.begin(),tmp.end());
    for(int i=0;i<(int)tmp.size();i++)
    {
        ms.erase(ms.find(tmp[i].F));
        ms.insert(tmp[i].S);
        int r=*(--ms.end()),l=*ms.begin();
        ans=min(ans,abs(st-l)+(r-l)+abs(ed-r));
        ans=min(ans,abs(st-r)+(r-l)+abs(ed-l));
    }
    return ans;
}                                                                                                                                                                        
int main()
{   
    scanf("%d%d",&n,&m);
    int x,y;
    scanf("%d%d",&x,&y);
    type[tot++]=1;
    vector<int> tmp;
    tmp.push_back(x); v.push_back(tmp); tmp.clear();
    for(int i=0;i<n-1;i++)
    {   
        int t,pos;
        scanf("%d%d",&t,&pos);
        if(t==1)
        {   
            if(tmp.size())
            {   
                type[tot++]=2;
                v.push_back(tmp);
                tmp.clear();
            }
            type[tot++]=1;
            tmp.push_back(pos); v.push_back(tmp); tmp.clear();
        }
        else
        {   
            tmp.push_back(pos);
        }
    }
    if(tmp.size())
    {   
        type[tot++]=2;
        v.push_back(tmp);
        tmp.clear();
    }
    type[tot++]=1; tmp.push_back(y); v.push_back(tmp); tmp.clear();
    int cur=1,ans=0,last=v[0][0];
    while(cur<(int)v.size())
    {
        if(type[cur]==1)
        {
            ans+=max(v[cur][0]-last,last-v[cur][0]);
            last=v[cur][0];
            cur++;
        }
        else
        {
            int nxt=v[cur+1][0];
            ans+=solve(last,nxt,v[cur]);
            cur+=2;
            last=nxt;
        }
    } 
    printf("%d\n",ans);
    return 0; 
}
