#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 10000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,tot,cnt,a[MAXN],root[MAXN];
int lson[MAXM],rson[MAXM],sum[MAXM];
void pushup(int k)
{
    sum[k]=sum[lson[k]]+sum[rson[k]];
}
void build(int &k,int l,int r)
{
    k=++tot;
    if(l==r) {sum[k]=0; return;}
    int mid=(l+r)/2;
    build(lson[k],l,mid); build(rson[k],mid+1,r);
    pushup(k);
}
void update(int &k,int last,int l,int r,int p)
{
    k=++tot;
    sum[k]=sum[last];
    if(l==r)
    {
        if(sum[k]) sum[k]=0; else sum[k]=1;
        return;
    }
    lson[k]=lson[last]; rson[k]=rson[last];
    int mid=(l+r)/2;
    if(p<=mid) update(lson[k],lson[last],l,mid,p);
    else update(rson[k],rson[last],mid+1,r,p);
    pushup(k);
}
int query(int &k,int l,int r,int x,int y)
{
    if(!k) return 0;
    if(l>y||r<x) return 0;
    if(l>=x&&r<=y) return sum[k];
    int mid=(l+r)/2;
    return query(lson[k],l,mid,x,y)+query(rson[k],mid+1,r,x,y);
}
string str;
int main()
{
    scanf("%d\n",&n);
    cnt=0;
    build(root[cnt],1,n);
    for(int i=0;i<n;i++)
    {
        getline(cin,str);
        cnt++;
        int res=-1;
        for(int j=0;j<(int)str.size();j++)
        {
            if(str[j]=='+'||str[j]=='-')
            {
                res=0;
            }
            else if(str[j]==' ')
            {
                if(res==-1) continue;
                int last;
                if(!root[cnt]) last=root[cnt-1]; else last=root[cnt];
                update(root[cnt],last,1,n,res+1);
                res=-1;
            }
            else res=res*10+(str[j]-'0');
        }
        if(res!=-1)
        {
            int last;
            if(!root[cnt]) last=root[cnt-1]; else last=root[cnt];
            update(root[cnt],last,1,n,res+1);
        }
    }
    int x=0;
    for(int i=0;i<n;i++)
    {
        int d;
        scanf("%d",&d);
        x=(x+query(root[d],1,n,x+1,n))%n;
    }
    printf("%d\n",x);
    return 0;
}