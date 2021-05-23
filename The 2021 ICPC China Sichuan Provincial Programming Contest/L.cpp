#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string str;
int main()
{
    cin>>str;
    if(str[0]>='a'&&str[0]<='z') str[0]=str[0]+'A'-'a';
    str="Welcome to "+str+".";
    cout<<str<<endl;
}