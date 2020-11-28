#include<bits/stdc++.h>
#define MAXN 55
#define INF 1000000000
#define INV 500000004
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,p[MAXN],q[MAXN];
bool vis[MAXN];
bool iscommutative()
{
    for(int i=1;i<=N;i++) if(p[q[i]]!=q[p[i]]) return false;
    return true;
}
bool iseven()
{
    memset(vis,false,sizeof(vis));
    int cnt=0;
    for(int i=1;i<=N;i++)
    {
        if(!vis[i])
        {
            int now=i;
            while(!vis[now])
            {
                vis[now]=true;
                now=q[now];
            }
            cnt++;
        }
    }
    if((N-cnt)%2==0) return true; else return false;
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++) scanf("%d",&p[i]);
    for(int i=1;i<=N;i++) q[i]=i;
    int ans=0;
    do
    {
        if(iscommutative()&&iseven()) 
        {
            for(int i=1;i<=N;i++) printf("%d ",q[i]);
            puts("");
            ans++;
        }
        
    } while (next_permutation(q+1,q+N+1));
    printf("%d\n",ans);
    
}