#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 11
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
int n,m;
ll t;
typedef bitset<100> bs;
bs a[64][MAXN*MAXN];
int dx[8]={-1,1,0,0,-1,1,-1,1};
int dy[8]={-1,-1,-1,1,0,0,1,1};
string str[MAXN];
int get_id(int x,int y)
{
    return x*m+y;
}
void print(bs &x)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(x.test(get_id(i,j))) printf("*"); else printf(".");
        }
        puts("");
    }
}
int main()
{
    scanf("%d%d%lld",&n,&m,&t);
    for(int i=0;i<n;i++) cin>>str[i];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int id=i*m+j;
            a[0][id].reset();
            if(i&1)
            {
                for(int k=2;k<8;k++)
                {
                    int nx=i+dx[k],ny=j+dy[k];
                    if(nx<0||nx>=n||ny<0||ny>=m) continue;
                    a[0][id].set(get_id(nx,ny));
                }
            }
            else
            {
                for(int k=0;k<6;k++)
                {
                    int nx=i+dx[k],ny=j+dy[k];
                    if(nx<0||nx>=n||ny<0||ny>=m) continue;
                    a[0][id].set(get_id(nx,ny));
                }
            }
        }
    }
    for(int k=0;k<62;k++)
    {
        for(int i=0;i<n*m;i++)
        {
            a[k+1][i].reset();
            for(int j=0;j<n*m;j++)
                if(a[k][i].test(j))
                    a[k+1][i]^=a[k][j];
        }
    }
    bs init;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(str[i][j]=='*') init.set(get_id(i,j));
    for(int i=62;i>=0;i--)
    {
        if(t&(1LL<<i))
        {
            bs tmp;
            for(int j=0;j<n*m;j++) if(init.test(j)) tmp^=a[i][j];
            swap(tmp,init);
        }
    }
    print(init);
    return 0;
}
