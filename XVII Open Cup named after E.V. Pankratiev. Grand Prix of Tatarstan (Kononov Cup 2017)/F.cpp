#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
char str[MAXN][MAXN],sstr[MAXN][MAXN];
string s[MAXN];
string save[MAXN];
int rk[MAXN];
vector<pair<string,int> > v;
string get_max()
{
    v.clear();
    for(int i=1;i<=m;i++)
    {
        s[i]="";
        for(int j=1;j<=n;j++) s[i]+=str[j][i];
        v.push_back(make_pair(s[i],i));
    }
    sort(v.begin(),v.end(),greater<pair<string,int> >());
    string ans="";
    int tot=0;
    for(int i=0;i<(int)v.size();i++) 
    {
        ans+=v[i].F;
        if(i==0||v[i].F!=v[i-1].F) 
        {
            rk[v[i].S]=++tot;
            save[tot]=v[i].F;
        } 
        else rk[v[i].S]=tot;
    }
    vector<string> vv;
    for(int j=n;j>=2;j--)
    {
        vv.clear();
        for(int i=1;i<=m;i++)
        {
            string tmp="";
            for(int k=j;k<=n;k++) tmp+=str[k][i];
            for(int k=0;k<(int)v.size();k++) if(v[k].S!=i) tmp+=(char)(105-rk[v[k].S]); 
            for(int k=1;k<j;k++) tmp+=str[k][i];
            vv.push_back(tmp);
        }
        sort(vv.begin(),vv.end(),greater<string>());
        string tmp=vv[0],res="";
        for(int i=0;i<n-j+1;i++) res+=tmp[i];
        for(int i=n-j+1;i<n-j+m;i++) res+=save[105-(int)tmp[i]];
        for(int i=n-j+m;i<(int)tmp.size();i++) res+=tmp[i];
        ans=max(ans,res);
    }
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
    string ans=get_max();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            sstr[j][i]=str[i][j];
    swap(n,m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            str[i][j]=sstr[i][j];
    ans=max(ans,get_max());
    cout<<ans<<endl;
    return 0;
}