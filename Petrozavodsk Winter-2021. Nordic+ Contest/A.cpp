#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MDO 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,p[MAXN],d[MAXN];
int delta[MAXN],sum[MAXN];
int need[MAXN];
int get_num(int id)
{
    if(id==0) return max(0,p[1]-2);
    else if(id==k) return max(0,n-p[k]-1);
    else return max(0,(p[id+1]-p[id])/2-1);  
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++) scanf("%d",&p[i]);
    for(int i=1;i<=k;i++) scanf("%d",&d[i]);
    if(n==1)
    {
        puts("0");
        return 0;
    }
    int mini=INF;
    for(int i=1;i<=k;i++) 
    {
        delta[i]=d[i]-p[i];
        sum[i]=delta[i]+sum[i-1];
        mini=min(mini,sum[i]);
    }
    int st;
    if(mini<0) st=-mini; else st=0;
    for(int i=0;i<=k;i++) sum[i]+=st;
    int ans=0;
    for(int i=0;i<=k;i++) ans+=sum[i];
    int now=0;
    while(true)
    {
        if(now<=k&&min(get_num(now),sum[now]))
        {
            int d=min(get_num(now),sum[now]);
            sum[now]-=d;
            if(now==0) p[1]-=d;
            else if(now==k) p[k]+=d;
            else 
            {
                p[now]+=d;
                p[now+1]-=d;
            }
            if(now>0) now--;
            else now++;
        }
        else if(now==k) break;
        else now++;
    }
    for(int i=0;i<=k;i++)
    {
        if(sum[i])
        {
            puts("impossible");
            return 0;
        }
    }
    printf("%d\n",ans);
    return 0;
}