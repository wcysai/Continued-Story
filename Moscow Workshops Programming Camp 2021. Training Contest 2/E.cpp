#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
mt19937 wcy(time(NULL));
string str;
int query(int x)
{
    printf("? %d\n",x);
    fflush(stdout);
    cin>>str;
    return (str[0]=='<'?0:1);
}
void answer(int x)
{
    printf("= %d\n",x);
    fflush(stdout);
}
int get_inter(int l,int r,int s,int t)
{
    return max(0,min(r,t)-max(l,s)+1);
}
int get_intersect(int l,int r,int s,int t)
{
    if(s<=t) return get_inter(l,r,s,t); else return get_inter(l,r,1,t)+get_inter(l,r,s,n);
}
int calc(int l,int r,int s,int t)
{
    int len=get_intersect(l,r,s,t);
    return r-l+1-len/2;
}
int get_element(int l,int r,int s,int t,int k)//find k-th element in [l,r]
{
    int lb=l,rb=r+1;
    while(rb-lb>1)
    {
        int mid=(lb+rb)/2;
        if(calc(l,mid,s,t)<=k) lb=mid; else rb=mid;
    }
    return lb;
}
int main()
{
    scanf("%d%d",&n,&k);
    int t=0;
    while((1<<(t+1))<=n) t++;
    int rem=n-(1<<t);
    for(int i=0;i<k;i++)
    {
        int st=wcy()%n+1; //[st,st+2*rem-1] are paired up
        if((n-st)%2==0) {st++; if(st>n) st-=n;}
        int ed=st+2*rem-1;
        if(ed>n) ed-=n;
        if(!rem) st=ed=0;
        int l=1,r=n;
        for(int j=t-1;j>=0;j--)
        {
            //find the 2^j-th element
            int x=get_element(l,r,st,ed,(1<<j));
            if(!query(x+1)) r=x; else l=x+1;
        }
        if(l==r) answer(l);
        else
        {
            assert(r-l==1);
            if(!query(r)) answer(l); else answer(r);
        }
    }
    return 0;
}