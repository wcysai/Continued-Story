#include <bits/stdc++.h>
#define MAXN 1000005
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
string s,t;
vector<int> a,b;
void canonize(vector<int> &a)
{
    while(a.size()&&a.back()==0) a.pop_back();
}
void print(vector<int> &a)
{
    canonize(a);
    if(!a.size()) a.push_back(0);
    for(int i=(int)a.size()-1;i>=0;i--) printf("%d",a[i]);
    puts("");
}
vector<int> add(vector<int> a,vector<int> b)
{
    vector<int> c;
    int n=(int)a.size();
    int m=(int)b.size();
    int carry=0;
    for(int i=0;i<max(n,m);i++)
    {
        int x=(i>=n?0:a[i]);
        int y=(i>=m?0:b[i]);
        c.push_back((carry+x+y)%10);
        carry=(carry+x+y)/10;
    }
    if(carry) c.push_back(carry);
    return c;
}
vector<int> dec(vector<int> a,vector<int> b)
{
    canonize(a); canonize(b);
    vector<int> c; c.clear();
    int n=(int)a.size();
    int m=(int)b.size();
    assert(n>=m);
    int lend=0;
    for(int i=0;i<n;i++)
    {
        int x=(i>=n?0:a[i]);
        int y=(i>=m?0:b[i]);
        int val=x-lend-y;
        if(val>=0) {c.push_back(val); lend=0;}
        else {c.push_back(10+val); lend=1;}
    }
    assert(!lend);
    canonize(c);
    return c;
}
bool is_less(vector<int> &a,vector<int> &b)
{
    int n=(int)a.size();
    int m=(int)b.size();
    if(n!=m) return n<m;
    for(int i=n-1;i>=0;i--)
    {
        if(a[i]>b[i]) return false;
        if(a[i]<b[i]) return true;
    }
    return true;
}
vector<int> solve_not_greater(vector<int> a,vector<int> b)//maximum value each position not greater than a,not greater than b
{
    while(b.size()<a.size()) b.push_back(0);
    vector<int> c;
    bool less=false;
    int val;
    for(int i=(int)b.size()-1;i>=0;i--)
    {
        if(less) val=a[i]; 
        else
        {
            val=min(a[i],b[i]);
            if(val<b[i]) less=true;
        } 
        c.push_back(val);
    }
    reverse(c.begin(),c.end());
    canonize(c);
    return c;
}
vector<int> solve_not_smaller(vector<int> a,vector<int> b)//minimum value each position not greater than a,not less than b
{
    while(b.size()<a.size()) b.push_back(0);
    vector<bool> valid;
    valid.resize(b.size());
    for(int i=0;i<b.size();i++)
    {
        if(b[i]>a[i]) valid[i]=false;
        else if(b[i]<a[i]) valid[i]=true;
        else if(i==0) valid[i]=true;
        else valid[i]=valid[i-1];
    }
    assert(valid[b.size()-1]);
    vector<int> c;
    bool greater=false;
    int val;
    for(int i=(int)b.size()-1;i>=0;i--)
    {
        if(greater) val=0; 
        else
        {
            if(i==0||valid[i-1]) val=b[i]; else val=b[i]+1;
            if(val>b[i]) greater=true;
        } 
        c.push_back(val);
    }
    reverse(c.begin(),c.end());
    canonize(c);
    return c;
}
int main()
{
    cin>>s;
    cin>>t;
    n=(int)s.size(); m=(int)t.size();
    for(int i=0;i<n;i++) a.push_back(s[n-1-i]-'0');
    for(int i=0;i<m;i++) b.push_back(t[m-1-i]-'0');
    vector<int> c=add(a,b);
    int sz=(int)c.size();
    vector<int> ans=dec(solve_not_smaller(c,a),a);
    vector<int> tmp=dec(solve_not_smaller(c,b),b);
    if(is_less(tmp,ans)) ans=tmp;
    tmp=dec(b,solve_not_greater(c,b));
    if(is_less(tmp,ans)) ans=tmp;
    tmp=dec(b,solve_not_greater(c,b));
    if(is_less(tmp,ans)) ans=tmp;
    print(ans);
    return 0;
}