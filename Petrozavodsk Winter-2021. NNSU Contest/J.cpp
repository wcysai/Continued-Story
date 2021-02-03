#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000000000000031LL
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN];
vector<P> op;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    op.push_back(P(1,n));
    sort(a+1,a+n+1);
    for(int i=1;i<=n-1;i++)
    {
        if(a[i]==b[i]) continue;
        int id=-1,maxi=-INF,mini=INF;
        for(int j=i;j<=n;j++)
        {
            maxi=max(maxi,a[j]);
            mini=min(mini,a[j]);
            if(a[j]==b[i]) {id=j; break;}
        }
        assert(b[i]==mini||b[i]==maxi);
        if(b[i]==mini)
        {
            op.push_back(P(i,id));
            sort(a+i,a+id+1);
        }
        else
        {
            op.push_back(P(id,i));
            sort(a+i,a+id+1,greater<int>());
        }
    }
    printf("%d\n",(int)op.size());
    for(auto p:op) if(p.F<=p.S) printf("%d %d I\n",p.F,p.S); else printf("%d %d D\n",p.S,p.F);
    return 0;
}