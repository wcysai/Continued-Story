#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<P> v;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        v.push_back(P(x,0));
    }
    for(int i=0;i<m;i++)
    {
        int x;
        scanf("%d",&x);
        v.push_back(P(x,1));
    }
    sort(v.begin(),v.end());
    priority_queue<P,vector<P>,greater<P> > q1,q2;
    for(int i=0;i<m;i++) q1.push(P(INF,1));
    for(int i=0;i<n;i++) q2.push(P(INF,1));
    //always matching to the left
    ll ans=0;
    for(int i=0;i<(int)v.size();i++)
    {
        if(v[i].S==0)//pump
        {   
            ans+=q1.top().F+v[i].F; 
            q2.push(P(-q1.top().F-v[i].F*2,0));//cost to revert back and make sign of i minus
            if(q1.top().S==0) q1.pop();
            q2.push(P(-v[i].F,1));//make valid for matching
        }
        else//engine
        {
            ans+=q2.top().F+v[i].F;
            q1.push(P(-q2.top().F-v[i].F*2,0));//cost to revert back and make sign of i minus
            if(q2.top().S==0) q2.pop();
            q1.push(P(-v[i].F,1));
        }
    }
    printf("%lld\n",ans);
    return 0;
}