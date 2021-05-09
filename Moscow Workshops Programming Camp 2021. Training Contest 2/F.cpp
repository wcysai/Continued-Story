#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 sbcjb
#define x2 cbcjb
#define y1 cjbsb
#define y2 cjbcb
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
double x1,y1,x2,y2;
bool intersect(double l1,double r1,double l2,double r2)
{
    if(r1<l2||r2<l1) return false;
    return true;
}
int main()
{
    scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
    ll ans=0;
    if(y2-y1>5)
    {
        int k=(int)floor((y2-y1-5.0)/2.0);
        set<int> s; s.clear();
        int res=0;
        s.insert((int)floor(x1-0.001)); s.insert((int)floor(x1+0.001));
        s.insert((int)floor(x2-0.001)); s.insert((int)floor(x2+0.001));
        res+=(int)s.size();
        s.clear();
        s.insert((int)floor(x1-0.5-0.001)); s.insert((int)floor(x1-0.5+0.001));
        s.insert((int)floor(x2-0.5-0.001)); s.insert((int)floor(x2-0.5+0.001));
        res+=(int)s.size();
        y2-=2.0*k;
        ans+=1LL*k*res;
    }
    if(x2-x1>5)
    {
        int k=(int)floor((x2-x1-5.0)/1.0);
        set<int> s; s.clear();
        int res=0;
        s.insert((int)floor(y1-0.001)); s.insert((int)floor(y1+0.001));
        s.insert((int)floor(y2-0.001)); s.insert((int)floor(y2+0.001));
        res=(int)s.size();
        x2-=1.0*k;
        ans+=1LL*k*(int)res;
    }
    for(int i=(int)floor(y1-2-0.001);i<=(int)ceil(y2+2+0.001);i++)
    {
        for(int j=(int)floor(x1-2-0.001);j<=(int)ceil(x2+2+0.001);j++)
        {
            double l=j,r=j+1.0;
            if(i%2==1) l+=0.5,r+=0.5;
            //intersect (i,i+1) with (y1,y2); (l,r) with (x1,x2)
            if(y1>=i&&y1<=i+1&&intersect(l,r,x1,x2)) ans++;
            else if(y2>=i&&y2<=i+1&&intersect(l,r,x1,x2)) ans++;
            else if(intersect(i,i+1,y1,y2)&&x1>=l&&x1<=r) ans++;
            else if(intersect(i,i+1,y1,y2)&&x2>=l&&x2<=r) ans++;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
