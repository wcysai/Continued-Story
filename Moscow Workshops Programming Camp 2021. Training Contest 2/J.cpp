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
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,r,c;
string str;
map<char,int> mp;//LRUD
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
int rotate(int dir)
{
    if(dir==0) return 3;
    else if(dir==1) return 2;
    else if(dir==3) return 1;
    else return 0;
}
bool check(int r,int c,int scale,int dir)
{
    int nr=r+dx[dir],nc=c+dy[dir];
    if(nr<=0||nr>(1<<scale)||nc<=0||nc>(1<<(scale+1))) return true;
    if(scale==0) return false;
    if(c<=(1<<(scale-1)))
    {
        return check((1<<(scale-1))+1-c,r,scale-1,rotate(dir));
    }
    else if(c<=((1<<scale)+(1<<(scale-1))))
    {
        if(r<=(1<<(scale-1)))
        {
            return check(r,c-(1<<(scale-1)),scale-1,dir);
        }
        else return check(r-(1<<(scale-1)),c-(1<<(scale-1)),scale-1,dir);
    }
    else return check((1<<(scale+1))+1-c,r,scale-1,rotate(dir));
}
int main()
{
    scanf("%d",&n);
    scanf("%d%d",&r,&c);
    cin>>str;
    mp['L']=0; mp['R']=1; mp['U']=2; mp['D']=3;
    for(int i=0;i<(int)str.size();i++)
    {
        if(check(r,c,n,mp[str[i]])) printf("Y");
        else printf("N");
        r+=dx[mp[str[i]]]; c+=dy[mp[str[i]]];
    }
    puts("");
    return 0;
}
