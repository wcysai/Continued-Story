#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 1000005
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
int n,a[MAXN];
bool pref[MAXN],suf[MAXN];
bool flag;
int cnt[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    memset(pref,false,sizeof(pref));
    memset(cnt,0,sizeof(cnt));
    int c=0;
    for(int i=1;i<=n;i++)
    {
        int now=a[i];
        c++;
        if(a[i]<=1000000)
        {
            cnt[now]++;
            while(cnt[now]==2)
            {
                cnt[now]-=2;
                cnt[now-1]++;
                now--;
                c--;
            }
        }
        if((!cnt[1]&&!cnt[0])||(cnt[1]==1&&c==1)) pref[i]=true; else break;
    }
    memset(suf,false,sizeof(suf));
    suf[n]=true;
    memset(cnt,0,sizeof(cnt));
    c=0;
    for(int i=n;i>=1;i--)
    {
        int now=a[i];
        c++;
        if(a[i]<=1000000)
        {
            cnt[now]++;
            while(cnt[now]==2)
            {
                cnt[now]-=2;
                cnt[now-1]++;
                now--;
                c--;
            }
        }
        if((!cnt[1]&&!cnt[0])||(cnt[1]==1&&c==1)) suf[i-1]=true; else break;
    }
    vector<int> ans;
    for(int i=1;i<=n;i++) if(pref[i]&&suf[i]) ans.push_back(i);
    if(ans.size()==n) puts("inf");
    else
    {
        printf("%d\n",(int)ans.size());
        for(auto x:ans) printf("%d ",x);
        puts("");
    }
    return 0;
}
