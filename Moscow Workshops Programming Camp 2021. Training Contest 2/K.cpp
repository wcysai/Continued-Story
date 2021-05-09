#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define x1 sbcjb
#define y1 ntcjb
#define x2 cjbsb
#define y2 cjbnt
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,m,q,a[MAXN];
string str[MAXN];
struct query
{
    int x,y,id,delta;
};
vector<query> qq;
int cnt[MAXN][105];
ll ans[MAXN];
vector<vector<int> > prefsum[105];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) cin>>str[i];
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        qq.push_back((query){x2,y2,i,1});
        qq.push_back((query){x1-1,y2,i,-1});
        qq.push_back((query){x2,y1-1,i,-1});
        qq.push_back((query){x1-1,y1-1,i,1});
    }
    for(int i=1;i<=100;i++) 
    {
        prefsum[i].clear();
        vector<int> tmp; tmp.clear();
        for(int j=0;j<=i;j++) tmp.push_back(0);
        prefsum[i].push_back(tmp);
    }
    for(int i=1;i<=n;i++)
    {
        int len=(int)str[i].size();
        for(int j=1;j<=100;j++) cnt[i][j]=cnt[i-1][j];
        cnt[i][len]++;
        vector<int> tmp; tmp.clear();
        tmp.resize(len);
        int s=0;
        auto v=prefsum[len].back();
        for(int j=1;j<=len;j++)
        {
            s+=str[i][j-1]-'0';
            tmp[j-1]=v[j-1]+s;
        }
        prefsum[len].push_back(tmp);
    }
    for(int i=0;i<(int)qq.size();i++)
    {
        auto p=qq[i];
        ll res=0;
        for(int j=1;j<=100;j++)
        {
            if(cnt[p.x][j]==0) continue;
            int m=p.y/j,rem=p.y%j;
            res+=1LL*m*prefsum[j][cnt[p.x][j]][j-1]+(rem==0?0:prefsum[j][cnt[p.x][j]][rem-1]);
        }
        ans[p.id]+=res*p.delta;
    }
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
    return 0;
}
