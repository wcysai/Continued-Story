#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
double a,b,c,d;
multiset<pair<double,ll> > s;
ll fact[21];
int main()
{
    fact[0]=1;
    for(int i=1;i<=20;i++) fact[i]=fact[i-1]*i;
    scanf("%d",&n);
    scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
    for(int x1=0;x1<=n;x1++)
        for(int x2=0;x1+x2<=n;x2++)
            for(int x3=0;x1+x2+x3<=n;x3++)
            {
                int x4=n-x1-x2-x3;
                double prob=1.0;
                for(int i=0;i<x1;i++) prob=prob*a;
                for(int i=0;i<x2;i++) prob=prob*b;
                for(int i=0;i<x3;i++) prob=prob*c;
                for(int i=0;i<x4;i++) prob=prob*d;
                ll num=fact[n]/fact[x1]/fact[x2]/fact[x3]/fact[x4];
                s.insert(make_pair(prob,num));
            }
    double ans=0.0;
    while(s.size()>=1)
    {
        auto it=s.begin();
        if(it->S<1)
        {
            s.erase(it);
            continue;
        }
        if(it->S==1) 
        {
            if(s.size()==1) break;
            auto itt=next(it);
            auto p=*it; auto q=*itt;
            s.erase(s.find(p)); s.erase(s.find(q)); 
            ans+=p.F+q.F;
            if(q.S>1) s.insert(make_pair(q.F,q.S-1));
            s.insert(make_pair(p.F+q.F,1LL));
        }
        else
        {
            auto p=*it;
            s.erase(s.find(p));
            ans+=(double)(p.S/2)*(2.0*p.F);
            s.insert(make_pair(2*p.F,p.S/2));
            if(p.S&1) s.insert(make_pair(p.F,1));
        }
    }
    printf("%.15f\n",ans);
    return 0;
}