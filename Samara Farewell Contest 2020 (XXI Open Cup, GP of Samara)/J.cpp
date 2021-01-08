#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN],d[MAXN];
int main()
{
    scanf("%d",&n);
    int cnt=0,x=0;
    ll s1=0,s2=0;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d",&a[i],&b[i]);
        s1+=a[i]; 
        if(b[i]>0) {d[i]=a[i]-b[i]+1; s2+=a[i]; x=max(x,d[i]);}
        else cnt++;
    }
    if(cnt>=2)
    {
        printf("%d %lld\n",x,s2);
    }
    else if(cnt==1)
    {
        printf("%d %lld\n",x+1,s1);
    }
    else
    {
        vector<int> v;
        for(int i=1;i<=n;i++) v.push_back(a[i]-b[i]+1);
        sort(v.begin(),v.end());
        printf("%d %lld\n",min(x,v[v.size()-2]+1),s2);
    }
}