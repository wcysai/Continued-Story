#include<bits/stdc++.h>
#define MAXN 30
#define MAXM 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int d[MAXN][MAXN];
vector<string> v[MAXN];
vector<int> save[MAXN];
string str;
int cnt[MAXM],pos[MAXM];
bool f;
void init()
{
    int tot=0;
    for(int i=0;i<n;i++)
    {
        for(auto s:v[i])
        {
            tot++; cnt[tot]=(int)s.size(); pos[tot]=i;
            if(!f)
            {
                for(int j=0;j<(int)s.size();j++)
                    save[s[j]-'a'].push_back(tot);
            }
        }
    }
    f=true;
}
int main()
{
    scanf("%d",&n);
    f=false;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&m);
        for(int j=0;j<m;j++)
        {
            string str;
            cin>>str;
            v[i].push_back(str);
        }
    }
    for(int i=0;i<n;i++)
    {
        init();
        for(int j=0;j<n;j++) d[j][i]=INF;
        queue<P> que;
        que.push(P(i,0));
        while(que.size())
        {
            P p=que.front(); que.pop();
            int v=p.F,dis=p.S;
            if(d[v][i]!=INF) continue;
            d[v][i]=dis;
            for(auto x:save[v])
            {
                cnt[x]--;
                if(cnt[x]==0&&d[pos[x]][i]==INF) 
                {
                    que.push(P(pos[x],dis+1));
                }
            }
        }
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            printf("%d%c",(d[i][j]==INF?-1:d[i][j]),(j==n-1?'\n':' '));
    return 0;
}