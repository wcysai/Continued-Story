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
int n;
vector<int> v;
vector<int> ans;
bool mark[MAXM];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        mark[x]=true;
    }
    for(int i=1;i<=10000000;i++)
    {
        if(!mark[i]) continue;
        bool f=true;
        for(int j=2*i;j<=10000000;j+=i) if(mark[j]) {f=false; break;}
        if(f) ans.push_back(i);
    }
    for(auto x:ans) printf("%d ",x);
    puts("");
    return 0;
}