#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 998244353
#define REV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
ll a[MAXN];
bool stopping[MAXN];
int lmost[MAXN],rmost[MAXN];
int fact[MAXN],invf[MAXN],inv[MAXN];
vector<pair<ll,int> > v;
set<ll> pos;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
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
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=500000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[500000]=pow_mod(fact[500000],MOD-2);
    for(int i=499999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=500000;i>=1;i--) inv[i]=1LL*invf[i]*fact[i-1]%MOD;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
        scanf("%lld",&a[i]);
    memset(stopping,false,sizeof(stopping));
    stopping[1]=stopping[n]=true;
    vector<int> st;
    st.push_back(1);
    for(int i=2;i<=n-1;i++)
    {
        while(st.size()>=2)
        {
            int r=i;
            int l=st[st.size()-2],mid=st.back();
            if((r-mid)*a[l]+(mid-l)*a[r]>(r-l)*a[mid]) st.pop_back(); else break;
        }
        int l=st.back(),r=n;
        if((r-i)*a[l]+(i-l)*a[r]<=(r-l)*a[i]) st.push_back(i);
    }
    for(auto x:st) stopping[x]=true;
    for(int i=1;i<=n;i++) 
    {
        if(stopping[i]) lmost[i]=i;
        else lmost[i]=lmost[i-1];
    }
    for(int i=n;i>=1;i--)
    {
        if(stopping[i]) rmost[i]=i;
        else rmost[i]=rmost[i+1];
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(stopping[i]) add(ans,1LL*inv[n]*(a[i]%MOD)%MOD);
        int len=rmost[i]-lmost[i];
        int dis=i-lmost[i];
        add(ans,1LL*inv[n]*inv[len]%MOD*(len-dis)%MOD*(a[lmost[i]]%MOD)%MOD);
        add(ans,1LL*inv[n]*inv[len]%MOD*(dis)%MOD*(a[rmost[i]]%MOD)%MOD);
    }
    printf("%d\n",ans);
    return 0;
}