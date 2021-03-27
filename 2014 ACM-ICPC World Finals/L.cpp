#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN],b[MAXN];
int rightmost[21][2*MAXN];
multiset<int> ms;
vector<P> events[2*MAXN];
void add_interval(int l,int r)
{
    events[l].push_back(P(r,1));
    events[r+1].push_back(P(r,-1));
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++) 
    {
        scanf("%d%d",&a[i],&b[i]);
        if(a[i]<=b[i])
        {
            add_interval(a[i],b[i]);
            add_interval(n+a[i],n+b[i]);
        }
        else
        {
            add_interval(a[i],n+b[i]);
        }
    }
    bool f=true;
    for(int i=1;i<=2*n;i++)
    {
        for(auto p:events[i])
        {
            if(p.S==1) ms.insert(p.F);
            else ms.erase(ms.find(p.F));
        }
        if(!ms.size()) rightmost[0][i]=i-1; else rightmost[0][i]=*(prev(ms.end()));
    }
    for(int i=1;i<=2*n;i++) rightmost[0][i]=max(rightmost[0][i-1],rightmost[0][i]);
    rightmost[0][2*n+1]=2*n;
    for(int i=0;i+1<=20;i++)
    {
        for(int j=1;j<=2*n;j++)
            rightmost[i+1][j]=rightmost[i][rightmost[i][j]+1];    
        rightmost[i+1][2*n+1]=2*n;
        for(int j=1;j<=2*n;j++) rightmost[i+1][j]=max(rightmost[i+1][j-1],rightmost[i+1][j]);
    }
    
    int ans=INF;
    for(int i=1;i<=n;i++)
    {
        //cover [i,n+i-1]
        int cur=i-1,cnt=0;
        if(rightmost[20][i]<n+i-1) continue;
        for(int j=19;j>=0;j--)
        {
            if(rightmost[j][cur+1]<n+i-1)
            {
                cnt+=(1<<j);
                cur=rightmost[j][cur+1];
            }
        }
        ans=min(ans,cnt+1);
    }
    if(ans==INF)
    {
        puts("impossible");
        return 0;
    }
    printf("%d\n",ans);
    return 0;
}