#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 505
#define INF 8000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,q;
int w[MAXN][MAXN],p[MAXN][MAXN];
int len[MAXN*MAXN],ww[MAXN*MAXN],area[MAXN*MAXN];
multiset<int> save[1005];
multiset<P> gr;
vector<int> ch;
void solve(int i,int j,int pp,int sgn)
{
    ch.clear();
    ch.push_back(p[i][j]); ch.push_back(pp);
    if(i>1) ch.push_back(p[i-1][j]); 
    if(i<n) ch.push_back(p[i+1][j]); 
    if(j>1) ch.push_back(p[i][j-1]); 
    if(j<n) ch.push_back(p[i][j+1]); 
    sort(ch.begin(),ch.end());
    ch.erase(unique(ch.begin(),ch.end()),ch.end());
    for(auto x:ch)
    {
        if(area[x]==0) continue;
        if(len[x]<=1000)
        {
            if(sgn==-1) save[len[x]].erase(save[len[x]].find(ww[x])); else save[len[x]].insert(ww[x]);
        }
        else
        {
            if(sgn==-1) gr.erase(gr.find(P(len[x],ww[x]))); else gr.insert(P(len[x],ww[x]));
        }
    }
}
ll calc(ll A,ll B,ll C)
{
    ll ans=-INF;
    for(int i=0;i<=1000;i++)
    {
        if(save[i].size())
        {
            int x=*(prev(save[i].end()));
            ans=max(ans,A*x+B*i+C*x*i);
            x=*save[i].begin();
            ans=max(ans,A*x+B*i+C*x*i);
        }
    }
    for(auto x:gr)
    {
        ans=max(ans,A*x.S+B*x.F+C*x.F*x.S);
    }
    return ans;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        gr.clear();
        for(int i=0;i<n*n;i++) len[i]=ww[i]=area[i]=0;
        for(int i=0;i<=1000;i++) save[i].clear();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&w[i][j]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&p[i][j]);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                ww[p[i][j]]+=w[i][j];
                area[p[i][j]]++;
                if(i<n&&p[i][j]!=p[i+1][j])
                {
                    len[p[i][j]]++;
                    len[p[i+1][j]]++;
                }
                if(j<n&&p[i][j]!=p[i][j+1])
                {
                    len[p[i][j]]++;
                    len[p[i][j+1]]++;
                }
            }
        }
        for(int i=0;i<n*n;i++)
        {
            if(area[i]==0) continue;
            if(len[i]<=1000) save[len[i]].insert(ww[i]);
            else gr.insert(P(len[i],ww[i]));
        }
        scanf("%d",&q);
        for(int _=0;_<q;_++)
        {
            int i,j,pp;
            ll A,B,C;
            scanf("%d%d%d%lld%lld%lld",&i,&j,&pp,&A,&B,&C);
            int ori=p[i][j];
            solve(i,j,pp,-1);
            if(i>1&&p[i-1][j]!=p[i][j]) {len[p[i][j]]--; len[p[i-1][j]]--;}
            if(i<n&&p[i+1][j]!=p[i][j]) {len[p[i][j]]--; len[p[i+1][j]]--;}
            if(j>1&&p[i][j-1]!=p[i][j]) {len[p[i][j]]--; len[p[i][j-1]]--;}
            if(j<n&&p[i][j+1]!=p[i][j]) {len[p[i][j]]--; len[p[i][j+1]]--;}
            ww[p[i][j]]-=w[i][j];
            area[p[i][j]]--;
            p[i][j]=pp;
            if(i>1&&p[i-1][j]!=p[i][j]) {len[p[i][j]]++; len[p[i-1][j]]++;}
            if(i<n&&p[i+1][j]!=p[i][j]) {len[p[i][j]]++; len[p[i+1][j]]++;}
            if(j>1&&p[i][j-1]!=p[i][j]) {len[p[i][j]]++; len[p[i][j-1]]++;}
            if(j<n&&p[i][j+1]!=p[i][j]) {len[p[i][j]]++; len[p[i][j+1]]++;}
            ww[p[i][j]]+=w[i][j];
            area[p[i][j]]++;
            solve(i,j,ori,1);
            printf("%lld\n",calc(A,B,C));
        }
    }
    return 0;
}