#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,x;
int bit[MAXN+1];
int cnt[MAXN+1];
int sum(int i)
{
    int s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=500000)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
int main()
{
    bool f=false;
    scanf("%d",&n);
    int s=0;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&x);
        if(f) {puts("No"); continue;}
        if(x>500000) {puts("Yes"); continue;}
        if(sum(x)==x)
        {
            if(sum(500000)==x) {puts("Yes"); f=true;}
            else puts("No");
        }
        else
        {
            puts("Yes");
            cnt[x]++; add(x,1);
            while(cnt[x]==2) {cnt[x-1]++; cnt[x]-=2; add(x-1,1); add(x,-2); x--;}
        } 
    }
}