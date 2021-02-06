#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
string str;
ll ans[4][MAXN];//LRUD
int calc_score(int x,int y)
{
    return (max(-x,x)+1)^(max(-y,y)+1);
}
int x[MAXN],y[MAXN];
map<P,int> cnt;
map<char,int> mp;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
int main()
{
    mp['L']=0; mp['R']=1; mp['U']=2; mp['D']=3;
    scanf("%d",&n);
    cin>>str;
    x[0]=0; y[0]=0;
    for(int i=0;i<n;i++)
    {
        x[i+1]=x[i]; y[i+1]=y[i];
        if(str[i]=='L') x[i+1]--;
        else if(str[i]=='R') x[i+1]++;
        else if(str[i]=='U') y[i+1]++;
        else y[i+1]--;
    }
    ll score=0;
    for(int tot=0;tot<4;tot++)
    {
        score=0;
        cnt.clear();
        for(int i=0;i<n;i++)
        {
            cnt[P(x[i],y[i])]++;
            int t=cnt[P(x[i],y[i])];
            score+=t*calc_score(x[i],y[i])+t;
        }
        ans[tot][n]=score;
        for(int i=n-1;i>=1;i--)//delete point i, add point i+1 with a shift
        {
            int t=cnt[P(x[i],y[i])];
            score-=t*calc_score(x[i],y[i])+t;
            cnt[P(x[i],y[i])]--;
            cnt[P(x[i+1]+dx[tot],y[i+1]+dy[tot])]++;
            t=cnt[P(x[i+1]+dx[tot],y[i+1]+dy[tot])];
            score+=t*calc_score(x[i+1]+dx[tot],y[i+1]+dy[tot])+t;
            ans[tot][i]=score;
        }
    }
    for(int i=1;i<=n;i++) printf("%lld\n",ans[mp[str[i-1]]][i]);
    return 0;
}