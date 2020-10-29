#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000210433
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int inc(int a,int b) {a+=b; return a>=MOD?a-MOD:a;}
int dec(int a,int b) {a-=b; return a<0?a+MOD:a;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int inv(int x) {return pow_mod(x,MOD-2);}
const int g=3;
int two[31];
int dbit(int x)
{
    while(x!=(x&-x)) x+=(x&-x);
    return x;
}
int rev(int x,int r)
{
    int ans=0;
    for(int i=0;i<r;i++)
        if(x&(1<<i)) ans+=1<<(r-i-1);
    return ans;
}
void ntt(vector<int> &v,int n,int on)
{
    int r=0,cnt=0,t=n;
    while(t>1) {cnt++; t/=2;}
    for(;;r++) if((1<<r)==n) break;
    for(int i=0;i<n;i++)
    {
        int tmp=rev(i,r);
        if(i<tmp) swap(v[i],v[tmp]);
    }
    for(int s=1;s<=r;s++)
    {
        int m=1<<s;
        int wn=pow_mod(g,(MOD-1)/m);
        for(int k=0;k<n;k+=m)
        {
            int w=1;
            for(int j=0;j<m/2;j++)
            {
                int t,u;
                t=1LL*w*v[k+j+m/2]%MOD;
                u=v[k+j];
                v[k+j]=(u+t);
                if(v[k+j]>=MOD) v[k+j]-=MOD;
                v[k+j+m/2]=u+MOD-t;
                if(v[k+j+m/2]>=MOD) v[k+j+m/2]-=MOD;
                w=1LL*w*wn%MOD;
            }
        }
    }
    if(on==-1)
    {
        for(int i=1;i<n/2;i++) swap(v[i],v[n-i]);
        for(int i=0;i<n;i++) v[i]=1LL*v[i]*two[cnt]%MOD;
    }
}
int normalize(vector<int> &a)
{
    int n=(int)a.size();
    int t=1;
    while(t<n) t*=2;
    a.resize(t);
    return t;
}
vector<int> multiply_mod(vector<int> &a,vector<int> &b,int eq=0)
{
    vector<int> aa,bb,c;
    if(eq)
    {
        aa=a;
        int n=2*normalize(aa);
        if(aa.size()<n) aa.resize(n);
        ntt(aa,n,1);
        c.resize(n);
        for(int i=0;i<n;i++) c[i]=1LL*aa[i]*aa[i]%MOD;
        ntt(c,n,-1);
        if(c.size()>(1<<10)) c.resize(1<<10);
        return c;
    }    
    aa=a; bb=b;
    int n=2*max(normalize(aa),normalize(bb));
    if(aa.size()<n) aa.resize(n); if(bb.size()<n) bb.resize(n);
    c.resize(n);
    ntt(aa,n,1); ntt(bb,n,1);
    for(int i=0;i<n;i++) c[i]=1LL*aa[i]*bb[i]%MOD;
    ntt(c,n,-1);
    if(c.size()>(1<<10)) c.resize(1<<10);
    return c;
}
vector<int> fa,fb;
void get_inv(vector<int> &a,int n,vector<int> &ret)
{
    assert(a[0]!=0);
    if(n==1)
    {
        ret.resize(1);
        ret[0]=inv(a[0]);
        return;
    }
    get_inv(a,(n+1)>>1,ret);
    fa=a; fb=ret;
    fa=multiply_mod(fb,fb,1);
    fa=multiply_mod(fa,a);
    fa.resize(n); fb.resize(n); ret.resize(n);
    for(int i=0;i<n;i++)
    {
        ret[i]=inc(fb[i],fb[i]);
        ret[i]=dec(ret[i],fa[i]);
    }
    fa.clear(); fb.clear();
}
vector<int> get_pow(vector<int> &v,int i)
{
    vector<int> a=v;
    vector<int> s;
    s.resize(1); s[0]=1;
    while(i)
    {
        if(i&1) s=multiply_mod(s,a);
        if(s.size()>(1<<10)) s.resize((1<<10));
        a=multiply_mod(a,a,1);
        if(a.size()>(1<<10)) a.resize(1<<10);
        i>>=1;
    }
    return s;
}
int n,A,m;
ll shift=0;
set<pair<P,P> >s;
vector<int> poly; 
void add_interval(P p,P q,int type)//1: add -1:dec
{
    int dif=q.S-q.F,len=p.S-p.F+1;
    if(type==1)
    {
        vector<int> tmp,tmp2;
        tmp.resize(dif+1);
        for(int i=0;i<=dif;i++) tmp[i]=1; 
        tmp=get_pow(tmp,len);
        poly=multiply_mod(poly,tmp);
        shift+=1LL*len*q.F;
    }
    else
    {
        vector<int> tmp,tmp2;
        tmp.resize(dif+1);
        for(int i=0;i<=dif;i++) tmp[i]=1; 
        tmp=get_pow(tmp,len);
        get_inv(tmp,(1<<10),tmp2);
        poly=multiply_mod(poly,tmp2);
        shift-=1LL*len*q.F;
    }
}
int main()
{
    for(int i=1;i<=30;i++) two[i]=pow_mod(1<<i,MOD-2);
    poly.resize(1); poly[0]=1; 
    scanf("%d%d%d",&n,&A,&m);
    s.insert(make_pair(P(1,n),P(0,1000)));
    add_interval(P(1,n),P(0,1000),1);
    for(int i=0;i<m;i++)
    {
        int type;
        scanf("%d",&type);
        vector<pair<pair<P,P>,int> >op;
        if(type==1)
        {
            int l,r,c,d;
            scanf("%d%d%d%d",&l,&r,&c,&d);
            for(auto p:s)
            {
                int lb=p.F.F,rb=p.F.S,tc=p.S.F,td=p.S.S;
                if(rb<l||lb>r) continue;
                op.push_back(make_pair(p,-1));
                if(lb<l) op.push_back(make_pair(make_pair(P(lb,l-1),P(tc,td)),1));
                if(rb>r) op.push_back(make_pair(make_pair(P(r+1,rb),P(tc,td)),1));
            }
            op.push_back(make_pair(make_pair(P(l,r),P(c,d)),1));
            for(auto p:op) 
            {
                if(p.S==-1) s.erase(s.find(p.F)); else s.insert(p.F);
                add_interval(p.F.F,p.F.S,p.S);
            }
        }
        else scanf("%d",&A);
        if(shift>A) puts("0"); else printf("%d\n",poly[A-shift]);
    }
    return 0;
}