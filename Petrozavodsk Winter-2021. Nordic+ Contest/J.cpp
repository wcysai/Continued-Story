#include <bits/stdc++.h>
#define MAXN 400005
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double PI=acos(-1.0);
namespace fft
{
    struct num
    {
        double x,y;
        num() {x=y=0;}
        num(double x,double y):x(x),y(y){}
    };
    inline num operator+(num a,num b) {return num(a.x+b.x,a.y+b.y);}
    inline num operator-(num a,num b) {return num(a.x-b.x,a.y-b.y);}
    inline num operator*(num a,num b) {return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
    inline num conj(num a) {return num(a.x,-a.y);}

    int base=1;
    vector<num> roots={{0,0},{1,0}};
    vector<int> rev={0,1};
    const double PI=acosl(-1.0);

    void ensure_base(int nbase)
    {
        if(nbase<=base) return;
        rev.resize(1<<nbase);
        for(int i=0;i<(1<<nbase);i++)
            rev[i]=(rev[i>>1]>>1)+((i&1)<<(nbase-1));
        roots.resize(1<<nbase);
        while(base<nbase)
        {
            double angle=2*PI/(1<<(base+1));
            for(int i=1<<(base-1);i<(1<<base);i++)
            {
                roots[i<<1]=roots[i];
                double angle_i=angle*(2*i+1-(1<<base));
                roots[(i<<1)+1]=num(cos(angle_i),sin(angle_i));
            }
            base++;
        }
    }

    void fft(vector<num> &a,int n=-1)
    {
        if(n==-1) n=a.size();
        assert((n&(n-1))==0);
        int zeros=__builtin_ctz(n);
        ensure_base(zeros);
        int shift=base-zeros;
        for(int i=0;i<n;i++)
            if(i<(rev[i]>>shift))
                swap(a[i],a[rev[i]>>shift]);
        for(int k=1;k<n;k<<=1)
        {
            for(int i=0;i<n;i+=2*k)
            {
                for(int j=0;j<k;j++)
                {
                    num z=a[i+j+k]*roots[j+k];
                    a[i+j+k]=a[i+j]-z;
                    a[i+j]=a[i+j]+z;
                }
            }
        }
    }

    vector<num> fa,fb;

    vector<ll> multiply(vector<ll> &a, vector<ll> &b)
    {
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<sz;i++)
        {
            ll x=(i<(int)a.size()?a[i]:0);
            ll y=(i<(int)b.size()?b[i]:0);
            fa[i]=num(x,y);
        }
        fft(fa,sz);
        num r(0,-0.25/sz);
        for(int i=0;i<=(sz>>1);i++)
        {
            int j=(sz-i)&(sz-1);
            num z=(fa[j]*fa[j]-conj(fa[i]*fa[i]))*r;
            if(i!=j) fa[j]=(fa[i]*fa[i]-conj(fa[j]*fa[j]))*r;
            fa[i]=z;
        }
        fft(fa,sz);
        vector<ll> res(need);
        for(int i=0;i<need;i++) res[i]=fa[i].x+0.5;
        return res;
    }
};
map<char,int> mp;
int n,m;
string s,t;
vector<ll> A,B;
vector<ll> tmp1,tmp2,ans;
int main()
{
    mp['n']=0; mp['e']=1; mp['s']=2; mp['w']=3;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        string str;
        int x;
        cin>>str;
        if(str[0]=='?') A.push_back(0); 
        else
        {
            scanf("%d",&x);
            A.push_back(mp[str[0]]*7+x);
        }
    }
    for(int i=0;i<m;i++)
    {
        string str;
        int x;
        cin>>str;
        if(str[0]=='?') B.push_back(0); 
        else
        {
            scanf("%d",&x);
            B.push_back(mp[str[0]]*7+x);
        }
    }
    reverse(B.begin(),B.end());
    tmp1.resize(n); tmp2.resize(m);
    for(int i=0;i<n;i++) tmp1[i]=A[i]*A[i]*A[i];
    for(int i=0;i<m;i++) tmp2[i]=B[i];
    tmp1=fft::multiply(tmp1,tmp2);
    ans=tmp1;
    tmp1.resize(n); tmp2.resize(m);
    for(int i=0;i<n;i++) tmp1[i]=A[i];
    for(int i=0;i<m;i++) tmp2[i]=B[i]*B[i]*B[i];
    tmp1=fft::multiply(tmp1,tmp2);
	for(int i=0;i<(int)tmp1.size();i++) ans[i]+=tmp1[i];
    tmp1.resize(n); tmp2.resize(m);
    for(int i=0;i<n;i++) tmp1[i]=A[i]*A[i];
    for(int i=0;i<m;i++) tmp2[i]=B[i]*B[i];
    tmp1=fft::multiply(tmp1,tmp2);
	for(int i=0;i<(int)tmp1.size();i++) ans[i]-=2*tmp1[i];
    int cnt=0;
	for(int i=m-1;i<n;i++) if(ans[i]==0) cnt++;
    printf("%d\n",cnt);
    return 0;
}
