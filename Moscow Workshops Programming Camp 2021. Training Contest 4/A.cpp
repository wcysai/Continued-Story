#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 4005
#define MAXQ 500005
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
int n,v,a,b,c,m,q;
int tri[MAXN][MAXN],sqr[MAXN][MAXN];
int tmptri[MAXN][MAXN],tmpsqr[MAXN][MAXN];
int ans[MAXQ];
struct node
{
    int type;//triangle/square
    int id;
    int x,y;
};
vector<node> query[MAXN];
int main()
{
    scanf("%d%d%d%d%d%d%d",&n,&v,&a,&b,&c,&m,&q);
    for(int i=0;i<q;i++)
    {
        int r,s,x;
        scanf("%d%d%d",&r,&s,&x);
        int len=31-__builtin_clz(x-1);
        query[len].push_back((node){0,i,r+(1<<len)-1,s});
        query[len].push_back((node){0,i,r+x-1,s+x-(1<<len)});
        int need=x-(1<<len);
        if(need!=0)
        {
            int clen=31-__builtin_clz(need-1);
            query[clen].push_back((node){1,i,r+x-1,s});
            query[clen].push_back((node){1,i,r+(1<<len)+(1<<clen)-1,s});
            query[clen].push_back((node){1,i,r+x-1,s+(1<<clen)});
            query[clen].push_back((node){1,i,r+(1<<len)+(1<<clen)-1,s+(1<<clen)});
        }
    }
    tri[1][1]=v;
    for(int i=2;i<=n;i++)
    {
        tri[i][1]=1LL*c*tri[i-1][1]%m;
        for(int j=2;j<=i;j++) tri[i][j]=(1LL*a*tri[i][j-1]+1LL*b*tri[i-1][j-1])%m;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            sqr[i][j]=tri[i][j];
    for(int k=0;k<12;k++)
    {
        for(auto p:query[k])
        {
            if(p.type==0) ans[p.id]=max(ans[p.id],tri[p.x][p.y]);
            else ans[p.id]=max(ans[p.id],sqr[p.x][p.y]);
        }
        int len=1<<(k+1);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=i;j++)
            {
                if(i<len) continue;
                tmptri[i][j]=max(sqr[i][j],max(tri[i-(1<<k)][j],tri[i][j+(1<<k)]));
                tmpsqr[i][j]=max(max(sqr[i][j],sqr[i-(1<<k)][j]),max(sqr[i][j+(1<<k)],sqr[i-(1<<k)][j+(1<<k)]));
            }
        swap(tri,tmptri); swap(sqr,tmpsqr);
    }
    for(int i=0;i<q;i++) printf("%d\n",ans[i]);
    return 0;
}
