#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define REV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,type[20];//0: nothing 1: xor 2: and 3: or 
void add(ll &a,ll b) {a+=b; }
void FWT(ll a[],int n)    
{    
    int cnt=0;
    for(int d=1;d<n;d<<=1)    
    {
        for(int m=d<<1,i=0;i<n;i+=m)    
            for(int j=0;j<d;j++)    
            {    
                ll x=a[i+j],y=a[i+j+d];    
                if(type[cnt]==1) {a[i+j]=(x+y),a[i+j+d]=x-y;  }
                else if(type[cnt]==2) a[i+j]=(x+y);
                else a[i+j+d]=(x+y);
                //xor:   
                //and:a[i+j]=x+y;    
                //or:a[i+j+d]=x+y;    
            }    
        cnt++;
    }
}    
    
void UFWT(ll a[],int n)    
{    
    int cnt=0;
    for(int d=1;d<n;d<<=1)    
    {
        for(int m=d<<1,i=0;i<n;i+=m)    
            for(int j=0;j<d;j++)    
            {    
                ll x=a[i+j],y=a[i+j+d]; 
                if(type[cnt]==1) {a[i+j]=(x+y)/2LL,a[i+j+d]=(x-y)/2LL;   }
                else if(type[cnt]==2) a[i+j]=x-y;
                else a[i+j+d]=y-x;   
                //xor:
                     
                //and:a[i+j]=x-y;    
                //or:a[i+j+d]=y-x;    
            }    
        cnt++;
    }
}    
void solve(ll a[],ll b[],int n)    
{    
    FWT(a,n);    
    FWT(b,n);    
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i];    
    UFWT(a,n);    
}   
int calc(int x,int y)
{
    int res=0;
    for(int i=0;i<n;i++)
    {
        int a=((x>>i)&1),b=((y>>i)&1);
        if(type[i]==0) continue;
        else if(type[i]==1) res|=(1<<i)*(a^b);
        else if(type[i]==2) res|=(1<<i)*(a&b);
        else res|=(1<<i)*(a|b);
    }
    return res;
}
string str;
int op[3][18];//1: flip 2: to one 3: to zero
ll a[(1<<18)],b[(1<<18)],ans[(1<<18)],tmp[(1<<18)];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        cin>>str;
        int cnt=0;
        for(int j=0;j<4;j++) if(str[j]=='1') cnt++;
        if(cnt==0)
        {
            type[i]=2; op[0][i]=3; op[1][i]=3;
            continue;
        }
        else if(cnt==4)
        {
            type[i]=2; op[0][i]=2; op[1][i]=2;
            continue; 
        }
        else if(cnt==1)
        {
            type[i]=2;
            int id=-1;
            for(int j=0;j<4;j++) if(str[j]=='1') {id=j; break;}
            if(id&1); else op[1][i]=1;
            if(id&2); else op[0][i]=1;
        }
        else if(cnt==3)
        {
            type[i]=3;
            int id=-1;
            for(int j=0;j<4;j++) if(str[j]=='0') {id=j; break;}
            if(id&1) op[1][i]=1; 
            if(id&2) op[0][i]=1; 
        }
        else
        {
            vector<int> v; v.clear();
            for(int j=0;j<4;j++) if(str[j]=='1') v.push_back(j);
            if((v[0]^v[1])==3)
            {
                type[i]=1;
                if(v[0]==0||v[0]==3) op[1][i]=1;
            }
            else
            {
                type[i]=2;
                int x=(v[0]&v[1]);
                if(x==0)
                {
                    x=v[0]|v[1];
                    assert(x==1||x==2);
                    if(x==1)
                    {
                        op[0][i]=1;
                        op[1][i]=2;
                    }
                    else
                    {
                        op[0][i]=2;
                        op[1][i]=1;
                    }
                }
                else
                {
                    assert(x==1||x==2);
                    if(x==1) op[0][i]=2;
                    else op[1][i]=2;
                }
            }
        }
    }
    for(int i=0;i<(1<<n);i++) scanf("%lld",&a[i]);
    for(int i=0;i<(1<<n);i++) scanf("%lld",&b[i]);
    memset(tmp,0,sizeof(tmp));
    for(int i=0;i<(1<<n);i++)
    {
        int mask=i;
        for(int j=0;j<n;j++)
        {
            if(op[0][j]==1) mask^=(1<<j);
            else if(op[0][j]==2) mask|=(1<<j);
            else if(op[0][j]==3) mask&=(~(1<<j));
        }
        add(tmp[mask],a[i]);
    }
    for(int i=0;i<(1<<n);i++) a[i]=tmp[i];
    memset(tmp,0,sizeof(tmp));
    for(int i=0;i<(1<<n);i++)
    {
        int mask=i;
        for(int j=0;j<n;j++)
        {
            if(op[1][j]==1) mask^=(1<<j);
            else if(op[1][j]==2) mask|=(1<<j);
            else if(op[1][j]==3) mask&=(~(1<<j));
        }
        add(tmp[mask],b[i]);
    }
    for(int i=0;i<(1<<n);i++) b[i]=tmp[i];
    solve(a,b,(1<<n));
    for(int i=0;i<(1<<n);i++) printf("%lld ",a[i]);
    return 0;
}
