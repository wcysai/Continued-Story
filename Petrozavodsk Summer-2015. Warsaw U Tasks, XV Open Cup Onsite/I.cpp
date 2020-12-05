#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a,b,q;
string s[MAXN],t[MAXN];
vector<P> v;
int main()
{
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d%d%d",&n,&m,&a,&b);
        for(int i=0;i<n;i++) cin>>s[i];
        for(int i=0;i<a;i++) cin>>t[i];
        v.clear();
        for(int i=0;i<a;i++)
            for(int j=0;j<b;j++)
                if(t[i][j]=='x') v.push_back(P(i,j));
        bool f=true;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(s[i][j]=='x')
                {
                    for(int k=0;k<(int)v.size();k++)
                    {
                        int dx=v[k].F-v[0].F,dy=v[k].S-v[0].S;
                        if(i+dx>=n||i+dx<0||j+dy>=m||j+dy<0||s[i+dx][j+dy]!='x') {f=false; break;}
                        s[i+dx][j+dy]='.';
                    }
                }
                if(!f) break;
            }
            if(!f) break;
        }
        if(f) puts("TAK"); else puts("NIE");
    }
    return 0;
}