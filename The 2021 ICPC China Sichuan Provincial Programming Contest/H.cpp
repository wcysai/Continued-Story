#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t;
string str;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        cin>>str;
        int sz=(int)str.size();
        if(sz==7&&str=="ikimasu") str="itte";
        else if(sz>=7&&str.substr(sz-7,7)=="shimasu") str=str.substr(0,sz-7)+"shite";
        else if(sz>=6&&str.substr(sz-6,6)=="gimasu") str=str.substr(0,sz-6)+"ide";
        else if(sz>=6&&str.substr(sz-6,6)=="kimasu") str=str.substr(0,sz-6)+"ite";
        else if(sz>=6&&(str.substr(sz-6,6)=="mimasu"||str.substr(sz-6,6)=="bimasu"||str.substr(sz-6,6)=="nimasu")) str=str.substr(0,sz-6)+"nde";
        else if(sz>=7&&str.substr(sz-7,7)=="chimasu") str=str.substr(0,sz-7)+"tte";
        else if(sz>=6&&str.substr(sz-6,6)=="rimasu") str=str.substr(0,sz-6)+"tte";
        cout<<str<<endl;
    }
    return 0;
}