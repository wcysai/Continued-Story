#include<bits/stdc++.h>
#define MAXN 1000000
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,p,g;
vector<int> a,b;
vector<int> aa;
int pow_mod(int a,int i)
{
    int s=1;
    while(i>0)
    {
        if(i&1) s=1LL*s*a%p;
        a=1LL*a*a%p;
        i>>=1;
    }
    return s;
}
bool g_test(int g,int p)
{
    for(int i=0;i<aa.size();i++)
        if(pow_mod(g,(p-1)/aa[i])==1)
            return 0;
    return 1;
}
int primitive_root(int p)
{
    int tmp=p-1;
    for(int i=2;i<=tmp/i;i++)
        if(tmp%i==0)
        {
            aa.push_back(i);
            while(tmp%i==0)
                tmp/=i;
        }
    if(tmp!=1)
    {
        aa.push_back(tmp);
    }
    int g=1;
    while(true)
    {
        if(g_test(g,p))
            return g;
        ++g;
    }
}
int pw[MAXN],ind[MAXN];
void add(int &a,int b) {a+=b; if(a>=p) a-=p;}
void dec(int &a,int b) {a-=b; if(a<0) a+=p;}
vector<int> kmp(string &a,string &b) // a=pattern, b=text
{
    int n=a.size();
    vector<int> next(n+1,0);
    for(int i=1;i<n;++i)
    {
        int j=i;
        while(j>0)
        {
            j=next[j];
            if(a[j]==a[i])
            {
                next[i+1]=j+1;
                break;
            }
        }
    }
    vector<int> p;//p=positions
    int m=b.size();
    for(int i=0,j=0;i<m;++i)
    {
        if(j<n&&b[i]==a[j])
        {
            j++;
        }
        else
        {
            while(j>0)
            {
                j=next[j];
                if(b[i]==a[j])
                {
                    j++;
                    break;
                }
            }
        }
        if(j==n)
        {
            p.push_back(i-n+1);
        }
    }
    return p;
}
vector<int> cyclic_shift(string &s,string &t)
{
    string ss=s+s;
    ss.pop_back();
    return kmp(t,ss);
}
vector<P> ans;
int main()
{
    scanf("%d%d%d",&n,&k,&p);
    g=primitive_root(p);
    pw[0]=1; ind[1]=0;
    for(int i=1;i<p-1;i++) pw[i]=1LL*pw[i-1]*g%p,ind[pw[i]]=i;
    int sx=0,sy=0;
    for(int i=0;i<n;i++) 
    {
        int x;
        scanf("%d",&x);
        a.push_back(x%p);
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    n=(int)a.size();
    for(int i=0;i<k;i++)
    {
        int x;
        scanf("%d",&x);
        b.push_back(x);
    }
    for(auto x:a) add(sx,x);
    for(auto y:b) add(sy,y);
    if((int)b.size()==1)
    {
        ans.push_back(P(0,b[0]));
    }
    if(n!=k)
    {
        printf("%d\n",(int)ans.size());
        for(auto p:ans) printf("%d %d\n",p.F,p.S);
        return 0;
    }
    if(n%p==0)
    {
        for(int i=1;i<p;i++)
            for(int j=0;j<p;j++)
                ans.push_back(P(i,j));
    }
    else
    {
        int inv=pow_mod(n,p-2);
        for(auto &x:a) dec(x,1LL*sx*inv%p);
        for(auto &y:b) dec(y,1LL*sy*inv%p); 
        int cntx=0,cnty=0;
        string s(p-1,'0'),t(p-1,'0');
        for(auto x:a) if(x==0) cntx++; else s[ind[x]]='1';
        for(auto y:b) if(y==0) cnty++; else t[ind[y]]='1';
        if(cntx==cnty)
        {
            vector<int> v=cyclic_shift(t,s);
            for(auto x:v) ans.push_back(P(pw[x],1LL*(sy-1LL*sx*pw[x]%p+p)*inv%p));
        }
    }
    printf("%d\n",(int)ans.size());
    for(auto p:ans) printf("%d %d\n",p.F,p.S);
    return 0;
}