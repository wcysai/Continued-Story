#include<bits/stdc++.h>
#define MAXN 305
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<double,double> P;
string str;
int n;
double val[26];
int cur;
P solve(int l,int r)// pair(derivative,value)
{
    if(l==r)
    {
        if(str[l]=='a'+cur) return P(1.0,val[str[l]-'a']);
        else return P(0.0,val[str[l]-'a']);
    }
    int cnt=0;
    for(int i=l;i<=r;i++)
    {
        if(str[i]=='(') cnt++;
        else if(str[i]==')') cnt--;
        if(str[i]=='+'&&cnt==0)
        {
            P p=solve(l,i-1),q=solve(i+1,r);
            P ret;
            ret.F=p.F+q.F; ret.S=p.S+q.S;
            return ret;
        }
    }
    P p=solve(l+4,r-1);
    return make_pair(cos(p.S)*p.F,sin(p.S));
}
int main()
{
    cin>>str;
    n=str.size();
    for(int i=0;i<26;i++) scanf("%lf",&val[i]);
    for(int i=0;i<26;i++)
    {
        cur=i;
        printf("%.10f%c",solve(0,n-1).F,i==25?'\n':' ');
    }
    return 0;
}