#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
string str;
int cost[MAXN];
int pre[MAXN],suf[MAXN],l[MAXN],r[MAXN];
bool deleted[MAXN];
void del(int x)
{
    if(deleted[x]) return;
    pre[suf[x]]=pre[x];
    suf[pre[x]]=suf[x];
    deleted[x]=true;
}
int main()
{
    memset(deleted,false,sizeof(deleted));
    scanf("%d%d",&n,&k);
    cin>>str;
    for(int i=1;i<=n-1;i++) pre[i]=i-1,suf[i]=i+1;
    for(int i=0;i<=n;i++) l[i]=r[i]=i;
    cost[0]=cost[n]=INF;
    suf[0]=1; pre[n]=n-1;
    priority_queue<P,vector<P>,greater<P> > pque;
    for(int i=1;i<=n-1;i++) 
    {
        cost[i]=(str[i-1]=='a'?0:1)+(str[i]=='c'?0:1);
        pque.push(P(cost[i],i));
    }
    int ans=0;
    //index (to be) changed is in [l[i],r[i]] with same parity with l[i]
    while(pque.size())
    {
        P p=pque.top(); pque.pop();
        if(k<p.F) break;
        if(deleted[p.S]) continue;
        ans++; 
        k-=p.F;
        l[p.S]=l[pre[p.S]]; r[p.S]=r[suf[p.S]];
        cost[p.S]=cost[pre[p.S]]+cost[suf[p.S]]-cost[p.S];
        pque.push(P(cost[p.S],p.S));
        del(pre[p.S]); del(suf[p.S]);
    };
    printf("%d\n",ans);
    for(int j=1;j<=n-1;j++)
    {
        //printf("x=%d l=%d r=%d\n",x,l[x],r[x]);
        if(deleted[j]) continue;
        for(int i=l[j]+1;i<r[j];i+=2) 
            str[i-1]='a',str[i]='c';
    }
    cout<<str<<endl;
    return 0;
}