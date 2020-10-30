#include<bits/stdc++.h>
#define MAXN 20
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int k;
string str;
vector<int> get_perm(int k,string &str)
{
    assert(str[0]=='+');
    if(k==0)
    {
        vector<int> v;
        v.push_back(1);
        return v;
    }
    string s=str.substr(0,(1<<(k-1)));
    string t=str.substr(1<<(k-1),1<<(k-1));
    vector<int> l=get_perm(k-1,s);
    for(int i=0;i<(1<<(k-1));i++) t[i]='+'+'-'-t[i];
    bool flag=false;
    if(t[0]=='-') t[0]='+',flag=true;
    vector<int> r=get_perm(k-1,t);
    vector<int> v;
    if(!flag)
    {
        for(auto x:l) v.push_back(x);
        for(auto x:r) v.push_back((1<<(k-1))+x);
    }
    else
    {
        int y=r[0];
        for(auto x:l) if(x==y) v.push_back((1<<(k-1))+y); else v.push_back(x);
        for(auto x:r) if(x==y) v.push_back(y); else v.push_back((1<<(k-1))+x);
    }
    return v;
}
int main()
{
    scanf("%d",&k);
    cin>>str;
    if(str[0]!='+')
    {
        puts("Impossible");
        return 0;
    }
    vector<int> v=get_perm(k,str);
    for(auto x:v) printf("%d ",x);
    return 0;
}