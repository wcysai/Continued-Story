//team continued story
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int w,h,n;
vector<P> points;
vector<int> xdis,ydis;
vector<int> xpoints[MAXN],ypoints[MAXN];
ll ans[5];
int bit[MAXN+1];
int sum(int i)
{
    int s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    if(i<=0) return; 
    while(i<=MAXN)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
void reset()
{
    memset(bit,0,sizeof(bit));
}
int main()
{
    scanf("%d%d%d",&w,&h,&n);
    for(int i=0;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        xdis.push_back(x); ydis.push_back(y);
        points.push_back(P(x,y));
    }
    sort(xdis.begin(),xdis.end()); sort(ydis.begin(),ydis.end());
    xdis.erase(unique(xdis.begin(),xdis.end()),xdis.end()); ydis.erase(unique(ydis.begin(),ydis.end()),ydis.end());
    //compute 0 neighbours
    ans[0]=1LL*(w+1-(int)xdis.size())*(h+1-(int)ydis.size());
    for(auto p:points)
    {
        int x=p.F,y=p.S;
        int xid=lower_bound(xdis.begin(),xdis.end(),x)-xdis.begin();
        int yid=lower_bound(ydis.begin(),ydis.end(),y)-ydis.begin();
        xpoints[xid].push_back(yid); ypoints[yid].push_back(xid);
    }
    for(int i=0;i<(int)xdis.size();i++) sort(xpoints[i].begin(),xpoints[i].end());
    for(int i=0;i<(int)ydis.size();i++) sort(ypoints[i].begin(),ypoints[i].end());
    for(int i=0;i<(int)xdis.size();i++)
    {
        int st=xpoints[i][0],ed=xpoints[i].back();//empty columns < st and empty columns > ed
        ans[1]+=(ydis[st]-st);
        ans[1]+=(h-ydis[ed]-((int)ydis.size()-1-ed));
    }
    for(int i=0;i<(int)ydis.size();i++)
    {
        int st=ypoints[i][0],ed=ypoints[i].back();//empty rows < st and empty rows > ed
        ans[1]+=(xdis[st]-st);
        ans[1]+=(w-xdis[ed]-((int)xdis.size()-1-ed));
    }
    for(int i=0;i<(int)xdis.size();i++)
    {
        for(int j=0;j<(int)xpoints[i].size()-1;j++)
        {
            int st=xpoints[i][j],ed=xpoints[i][j+1];
            ans[2]+=(ydis[ed]-ydis[st]-1-(ed-st-1));
        }
    }
    for(int i=0;i<(int)ydis.size();i++)
    {
        for(int j=0;j<(int)ypoints[i].size()-1;j++)
        {
            int st=ypoints[i][j],ed=ypoints[i][j+1];
            ans[2]+=(xdis[ed]-xdis[st]-1-(ed-st-1));
        }
    }
    reset();
    for(int i=0;i<(int)xdis.size();i++)
    {
        int st=xpoints[i][0],ed=xpoints[i].back();
        ans[2]+=sum(st); ans[2]+=sum((int)ydis.size())-sum(ed+1);
        for(auto x:xpoints[i])
            if(i==(int)ypoints[x].back()) add(x+1,1); 
    }
    reset();
    for(int i=(int)xdis.size()-1;i>=0;i--)
    {
        int st=xpoints[i][0],ed=xpoints[i].back();
        ans[2]+=sum(st); ans[2]+=sum((int)ydis.size())-sum(ed+1);
        for(auto x:xpoints[i])
            if(i==(int)ypoints[x][0]) add(x+1,1);
    }
    reset();
    for(int i=0;i<(int)xdis.size();i++)
    {
        for(int j=0;j<(int)xpoints[i].size()-1;j++)
            ans[4]+=(sum(xpoints[i][j+1])-sum(xpoints[i][j]+1));
        for(auto x:xpoints[i])
        {
            if(i==(int)ypoints[x][0]) add(x+1,1);
            if(i==(int)ypoints[x].back()) add(x+1,-1);
        }
    }
    ll allpoints=1LL*(w+1)*(h+1)-n;
    ans[3]=allpoints-ans[0]-ans[1]-ans[2]-ans[4];
    printf("%lld %lld %lld %lld %lld\n",ans[0],ans[1],ans[2],ans[3],ans[4]);
    return 0;
}
