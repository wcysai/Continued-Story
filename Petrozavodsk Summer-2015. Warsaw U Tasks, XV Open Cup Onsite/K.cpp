#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<200> bs;
int n,m,d[MAXN][MAXM];
mt19937 wcy(time(NULL));
bs save[MAXN];
bool valid[MAXN];
int tmp[MAXM],cnt[MAXN];
vector<int> v;
int curans;
vector<int> curv;
int dp[MAXN],pre[MAXN];
bool cmp(int x,int y)
{
    return cnt[x]<cnt[y];
}
bool cmp2(int x,int y)
{
    for(int i=1;i<=m;i++) if(d[x][i]!=d[y][i]) return d[x][i]>d[y][i];
    return x<y;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&d[i][j]);
    curans=0;
    for(int i=0;i<40;i++)
    {
        int id=wcy()%n+1;
        for(int j=1;j<=n;j++)
        {
            valid[j]=true;
            save[j].reset(); cnt[j]=0;
            if(j==id) continue;
            int dif=d[id][1]-d[j][1];
            for(int k=1;k<=m;k++) tmp[k]=0;
            bool f=false;
            for(int k=1;k<=m;k++) {tmp[k]=d[id][k]-d[j][k]-dif; if(tmp[k]<0) f=true;}
            if(f) for(int k=1;k<=m;k++) tmp[k]++;
            for(int k=1;k<=m;k++) if(tmp[k]!=0&&tmp[k]!=1) {valid[j]=false; break;}
            for(int k=1;k<=m;k++) if(tmp[k]==1) {save[j].set(k-1); cnt[j]++;} 
        }
        v.clear();
        for(int j=1;j<=n;j++) dp[j]=pre[j]=0;
        for(int j=1;j<=n;j++) if(valid[j]) {v.push_back(j);}
        sort(v.begin(),v.end(),cmp);
        for(int j=0;j<(int)v.size();j++)
        {
            dp[j]=1; pre[j]=-1;
            for(int k=0;k<j;k++) if((dp[k]+1>dp[j])&&((save[v[k]]&save[v[j]])==save[v[k]])) {dp[j]=dp[k]+1; pre[j]=k;}
        }
        int curres=0,curid=0;
        for(int j=0;j<(int)v.size();j++) if(dp[j]>curres) {curres=dp[j]; curid=j;}
        if(curres>curans)
        {
            vector<int> tmpv; tmpv.clear();
            while(true)
            {
                tmpv.push_back(v[curid]);
                if(dp[curid]==1) break;
                curid=pre[curid];
            }
            curans=curres;
            curv=tmpv;
        }
    }
    printf("%d\n",curans);
    sort(curv.begin(),curv.end(),cmp2);
    for(auto x:curv) printf("%d ",x);
    return 0;
}