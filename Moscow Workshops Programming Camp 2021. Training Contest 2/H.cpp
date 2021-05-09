#include<bits/stdc++.h>
#define maxk 400005
using namespace std;
typedef long long ll;
int n,m,k;
struct Edge
{
    int u,v;
}e[maxk],tmp[maxk];
int fa[maxk];
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
map<int,int> id;
bool check(int N,int M,int t)
{
    if(N-t>k+1)return 0;
    for(int i=1;i<=k;++i)
    {
        if(e[i].u<=M+t)tmp[i].u=(e[i].u-1)%M+1;else tmp[i].u=e[i].u;
        if(e[i].v<=M+t)tmp[i].v=(e[i].v-1)%M+1;else tmp[i].v=e[i].v;
    }
    id.clear();
    int cnt=0;
    for(int i=1;i<=M;++i)id[i]=++cnt;
    for(int i=M+t+1;i<=N;++i)id[i]=++cnt;
    for(int i=1;i<=cnt;++i)fa[i]=i;
    for(int i=1;i<=k;++i)
    {
        int u=id[tmp[i].u],v=id[tmp[i].v];
        if(find(u)!=find(v))
        {
            fa[find(u)]=find(v);
        }
    }
    int block=0;
    for(int i=1;i<=cnt;++i)if(find(i)==i)block++;
    if(!block)assert(0);
    if(block==1)return 1;
    else return 0;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;++i)scanf("%d%d",&e[i].u,&e[i].v),e[i].u++,e[i].v++;
    int N=n+m,M=m;
    ll res=0;
    while(1)
    {
        if(!M)
        {
            puts("-1");
            return 0;
        }
        if(check(N,M,N-M))
        {
            int l=1,r=N-M,ans=N-M;
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(check(N,M,mid))ans=mid,r=mid-1;
                else l=mid+1;
            }
            res+=ans;
            printf("%lld\n",res);
            return 0;
        }
        else
        {
            for(int i=1;i<=k;++i)
            {
                e[i].u=(e[i].u-1)%M+1;
                e[i].v=(e[i].v-1)%M+1;
            }
            res+=N-M;
            int NN=M,MM=N%M;
            N=NN;M=MM;
        }
    }
}