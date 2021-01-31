#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 200005
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k;
P a[MAXN];
P p[MAXN];
int calc(int num)
{
    int sum=0,cnt=0;
    int l=1,r=n;
    for(int i=1;i<=num;i++)
    {
        if(cnt==0)
        {
            r--;
            cnt++; sum+=m;
        }
        else 
        {
            int need=(sum+cnt-1)/cnt;
            if(a[r].F>=need) sum+=m;
            r--; cnt++;
        }
    }
    for(int i=1;i<=n-num;i++)
    {
        if(cnt==0)
        {
            l++;
            cnt++; sum+=m;
        }
        else 
        {
            int need=(sum+cnt-1)/cnt;
            if(a[l].F>=need) sum+=m;
            l++; cnt++;
        }
    }
    return sum/m;
}
void construct(int num)
{
    for(int i=1;i<=num;i++) printf("%d ",a[n+1-i].S);
    for(int i=1;i<=n-num;i++) printf("%d ",a[i].S);
    exit(0);
}
void construct_perm(int num,int num2)
{
    for(int i=1;i<=num;i++) p[i]=a[n+1-i];
    int tot=0;
    for(int i=num+1;i<=n;i++)
    {
        if(i==n-num2)
        {
            p[i]=a[n-num];
        }
        else
        {
            tot++;
            p[i]=a[i];
        }
    }
}
int calc2(int num,int num2)
{
    construct_perm(num,num2);
    int sum=0,cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(cnt==0)
        {
            cnt++; sum+=m;
        }
        else 
        {
            int need=(sum+cnt-1)/cnt;
            if(p[i].F>=need) sum+=m;
            cnt++;
        }
    }
    return sum/m;
}
void construct2(int num,int num2)
{
    construct_perm(num,num2);
    for(int i=1;i<=n;i++) printf("%d ",p[i].S);
    exit(0);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i].F);
        a[i].S=i;
    }
    sort(a+1,a+n+1);
    if(k%m!=0) {puts("impossible"); return 0;}
    k/=m;
    assert(calc(0)>=calc(n));
    int res=calc(0);
    if(res==k)
    {
        construct(0);
    }
    else if(res<k) {puts("impossible"); return 0;}
    res=calc(n);
    if(res==k)
    {
        construct(n);
    }
    else if(res>k) {puts("impossible"); return 0;}
    int l=0,r=n;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        int res=calc(mid);
        if(res==k) construct(mid);
        else if(res<k) r=mid;
        else l=mid;
    }
    int tmp=l;
    //construct(l)>k construct(l+1)<k
    //positions: a_n,a_{n-1},..,a_{n-l+1},a_1,a_2,...,a_{n-l}
    //move a_{n-l} before
    l=0; r=n-tmp;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        int res=calc2(tmp,mid);
        if(res==k) construct2(tmp,mid);
        else if(res<k) r=mid;
        else l=mid;
    }
    return 0;
}