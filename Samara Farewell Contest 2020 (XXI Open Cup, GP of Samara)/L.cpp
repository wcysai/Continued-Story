#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
int f[MAXN];
vector<P> id[MAXN];
vector<int> res;
void construct(int cur,int curtime)
{
    if(!id[cur].size()) return;
    while(id[cur].size()&&id[cur].back().S>=curtime) id[cur].pop_back();
    while(id[cur].size()&&id[cur].back().F==0) {res.push_back(id[cur].back().S); id[cur].pop_back();}
    if(id[cur].size()) construct(cur-1,id[cur].back().S);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=k;i++) f[i]=INF;
    for(int i=1;i<=n;i++)
    {
        if(f[a[i]]>f[a[i]-1]) {f[a[i]]=f[a[i]-1]; id[a[i]].push_back(P(-1,i));}
        if(f[a[i]-1]!=INF) {f[a[i]-1]++; id[a[i]-1].push_back(P(0,i));}
    }
    int ans=INF,pos=-1;
    for(int i=0;i<=k-1;i++) 
    {
        if(f[i]<ans)
        {
            ans=f[i];
            pos=i;
        }
    }
    printf("%d\n",ans); 
    construct(pos,n+1);
    reverse(res.begin(),res.end());
    for(auto x:res) printf("%d ",x);
    puts("");
    return 0;
}