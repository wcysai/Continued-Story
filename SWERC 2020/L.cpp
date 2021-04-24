#include<bits/stdc++.h>
#define MAXN 50005
#define MAXM 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,c[MAXM];
vector<int> customer[MAXN],restaurant[MAXN];
map<int,int> mp[MAXN];
priority_queue<P,vector<P>,greater<P> > pque[MAXN];
int match[MAXN];
string str;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d\n",&c[i]);
    for(int i=1;i<=n;i++)
    {
        getline(cin,str);
        int res=0;
        for(int j=0;j<(int)str.size();j++)
        {
            if(str[j]>='0'&&str[j]<='9') res=res*10+str[j]-'0';
            else 
            {
                customer[i].push_back(res);
                res=0;
            }
        }
        if(res) customer[i].push_back(res);
        reverse(customer[i].begin(),customer[i].end());
    }
    for(int i=1;i<=m;i++)
    {
        getline(cin,str);
        int res=0;
        for(int j=0;j<(int)str.size();j++)
        {
            if(str[j]>='0'&&str[j]<='9') res=res*10+str[j]-'0';
            else 
            {
                restaurant[i].push_back(res);
                res=0;
            }
        }
        if(res) restaurant[i].push_back(res);
        for(int j=0;j<(int)restaurant[i].size();j++) mp[i][restaurant[i][j]]=(int)restaurant[i].size()-j;
    }
    queue<int> que;
    for(int i=1;i<=n;i++) que.push(i);
    while(que.size())
    {
        int v=que.front(); que.pop();
        if(customer[v].size())
        {
            int u=customer[v].back();
            customer[v].pop_back();
            match[v]=u;
            pque[u].push(P(mp[u][v],v));
            if(pque[u].size()>c[u])
            {
                P p=pque[u].top(); pque[u].pop();
                match[p.S]=0;
                que.push(p.S);
            }
        }
    }
    for(int i=1;i<=n;i++) if(match[i]) printf("%d\n",i);
    return 0;
}