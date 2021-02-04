#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 2000005
#define INF 1000000000
#define REV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,tot,num,cnt,a[MAXN];
int weight[MAXN],ed[MAXM];
multiset<pair<int,P> > event;
set<int> points;
int root[MAXM],lson[MAXM],rson[MAXM],sum[MAXM];
bool crucial[MAXM];
int st[MAXN][18];
int pre[MAXN];
void init(int n,int *arr)
{
    pre[1]=0;
    for(int i=2;i<=n;i++)
    {
        pre[i]=pre[i-1];
        if ((1<<pre[i]+1)==i) ++pre[i];
    }
    for(int i=n;i>=1;--i)
    {
        st[i][0]=arr[i];
        for(int j=1;(i+(1<<j)-1)<=n;++j)
            st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
    }
}
int st_query(int l,int r)
{
    int len=r-l+1,k=pre[len];
    return min(st[l][k],st[r-(1<<k)+1][k]);
}
void merge(int k)
{
    sum[k]=sum[lson[k]]+sum[rson[k]];
    if(crucial[lson[k]]||crucial[rson[k]]) crucial[k]=true; else crucial[k]=false;
}
void update1(int &k,int last,int l,int r,int p)//make some point crucial
{
    k=++tot;
    sum[k]=sum[last];
    if(l==r) {sum[k]++; crucial[k]=true; return;}
    lson[k]=lson[last];rson[k]=rson[last];
    int mid=(l+r)/2;
    if(p<=mid) update1(lson[k],lson[last],l,mid,p);
    else update1(rson[k],rson[last],mid+1,r,p);
    merge(k);
}
void update2(int &k,int last,int l,int r,int p)//add 1 to some point
{
    k=++tot;
    sum[k]=sum[last];
    if(l==r) {sum[k]++; return;}
    lson[k]=lson[last];rson[k]=rson[last];
    int mid=(l+r)/2;
    if(p<=mid) update2(lson[k],lson[last],l,mid,p);
    else update2(rson[k],rson[last],mid+1,r,p);
    merge(k);
}
int query(int &k,int l,int r,int x,int y)
{
    if(!k) return 0;
    if(l>y||r<x) return 0;
    if(l>=x&&r<=y) return mx[k];
    int mid=(l+r)/2;
    return max(query(lson[k],l,mid,x,y),query(rson[k],mid+1,r,x,y));
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        event.insert(make_pair(2*a[i],P(i,0)));
    }
    init(n,a);
    while(event.size())
    {
        auto it=event.begin();
        num++;
        int w=it->F;
        weight[num]=w;
        while(event.size()&&event.begin()->F==w)
        {
            auto it=event.begin();
            if(it->S.S==0)
            {
                update1(root[++cnt],root[cnt-1],1,n,it->S.F);
                points.insert(it->S.F);
                auto it1=points.lower_bound(it->S.F);
                if(it1!=points.begin())
                {
                    int l=*prev(it1),r=*it1;
                    int mini=st_query(l+1,r-1);
                    int need=weight-min(a[l],a[r])
                }
            }
            event.erase(event.begin());
            update()
        }

    }
    for(int i=1;i<=q;i++)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
    }
}