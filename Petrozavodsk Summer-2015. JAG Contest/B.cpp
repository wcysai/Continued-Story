#include<bits/stdc++.h>
#define MAXN 605
#define MAXM 180005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a,b;
int w[MAXN];
short f[MAXN][MAXM],g[MAXN][MAXM],pref[MAXN][MAXM],preg[MAXN][MAXM];
int pre[MAXM],suf[MAXM];
bool has[MAXN];
vector<int> v;
int main()
{
    scanf("%d%d%d%d",&n,&k,&a,&b);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    int s=0;
    for(int i=1;i<=k;i++) s+=w[i];
    for(int i=k;i<=n;i++)
        for(int j=0;j<=180000;j++)
            f[i][j]=g[i][j]=k+1;
    f[k][s]=0;
    for(int t=k+1;t<=n;t++)
    {
        for(int i=0;i<=180000;i++) 
        {
            f[t][i]=f[t-1][i],g[t][i]=g[t-1][i];
            pref[t][i]=preg[t][i]=-1;
        }
        for(int i=0;i<=180000;i++) //adding
        {
            if(i>=w[t]&&f[t-1][i-w[t]]<g[t][i]) 
            {
                g[t][i]=f[t-1][i-w[t]];
                preg[t][i]=t;
            }
        }
        for(int i=180000;i>=0;i--)//deleting
            for(int j=g[t][i]+1;j<=g[t-1][i];j++)
            {
                if(i>=w[j]&&j<f[t][i-w[j]]) 
                {
                    f[t][i-w[j]]=j;
                    pref[t][i-w[j]]=j;
                }
            }
    }
    pre[0]=(f[n][0]<=k?0:-INF);
    for(int i=1;i<=180000;i++)  if(f[n][i]<=k) pre[i]=i; else pre[i]=pre[i-1];
    suf[180001]=INF;
    for(int i=180000;i>=0;i--) if(f[n][i]<=k) suf[i]=i; else suf[i]=suf[i+1];
    int ans=-INF,x,y;
    for(int i=a;i<=b;i++)
    {
        int res=min(i-pre[i],suf[i]-i);
        if(res>ans)
        {
            x=i;
            if(i-pre[i]==res) y=pre[i]; else y=suf[i];
            ans=res;
        }
    }
    printf("%d\n",x);
    for(int i=1;i<=k;i++) has[i]=true;
    int cur=n,sum=y,state=0;
    while(cur>k)
    {
        if(state==0)
        {
            if(pref[cur][sum]==-1) cur--;
            else {int id=pref[cur][sum]; has[id]=false; state=1; sum+=w[id];}
        }
        else
        {
            if(preg[cur][sum]==-1) cur--;
            else {int id=preg[cur][sum]; v.push_back(id); state=0; sum-=w[id]; cur--;}
        }
    }
    for(int i=1;i<=k;i++) if(has[i]) v.push_back(i);
    sort(v.begin(),v.end());
    for(auto x:v) printf("%d ",x);
    puts("");
    return 0;
}