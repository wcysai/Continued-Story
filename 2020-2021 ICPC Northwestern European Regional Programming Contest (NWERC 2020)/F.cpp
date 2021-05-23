#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 cjbsb
#define y1 sbcjb
#define x2 ntcjb
#define y2 cjbnt
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef pair<P,P> PP;
int n,x[MAXN],vl[MAXN],id[MAXN];
int pre[MAXN],suf[MAXN];
bool deleted[MAXN];
vector<int> ans;
struct node
{
    P p,q;
};
set<node> s;
void del(int x)
{
    if(deleted[x]) return;
    deleted[x]=true;
    pre[suf[x]]=pre[x];
    suf[pre[x]]=suf[x];
}
inline bool operator < (node x,node y)
{
    int x1=x.p.F,y1=x.p.S,x2=y.p.F,y2=y.p.S;//x1/y1<x2/y2
    if(1LL*x1*y2==1LL*x2*y1) return x.q<y.q;
    return 1LL*x1*y2<1LL*x2*y1;
}
int main()
{
    memset(deleted,false,sizeof(deleted));
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&vl[i]);
    for(int i=1;i<=n;i++) pre[i]=i-1,suf[i]=i+1;
    suf[0]=1; pre[n+1]=n;
    memset(deleted,false,sizeof(deleted));
    for(int i=1;i<=n-1;i++)
    {
        int dv=vl[i+1]-vl[i],dx=x[i+1]-x[i];
        if(dv>=0) continue;
        s.insert((node){P(dx,-dv),P(i,i+1)});
    }
    while(s.size())
    {
        node pt=*s.begin();
        P p=pt.q;
        s.erase(s.begin());
        if(deleted[p.F]||deleted[p.S]) continue;
        int l=pre[p.F],r=suf[p.S];
        del(p.F); del(p.S);
        if(l!=0&&r!=n+1)
        {
            int dv=vl[r]-vl[l],dx=x[r]-x[l];
            if(dv<0) 
            {
                s.insert((node){P(dx,-dv),P(l,r)});
            }
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++) if(!deleted[i]) cnt++;
    printf("%d\n",cnt);
    for(int i=1;i<=n;i++) if(!deleted[i]) printf("%d ",i);
    return 0;
}