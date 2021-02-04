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
int n,cnt[(1<<18)],p2[(1<<18)],p3[(1<<18)],p4[(1<<18)];
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
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void FWT(int a[],int n)    
{    
    for(int d=1;d<n;d<<=1)    
        for(int m=d<<1,i=0;i<n;i+=m)    
            for(int j=0;j<d;j++)    
            {    
                int x=a[i+j],y=a[i+j+d];    
                //xor:
                a[i+j]=(x+y)%MOD,a[i+j+d]=(x-y+MOD)%MOD;     
                //and:a[i+j]=x+y;    
                //or:a[i+j+d]=x+y;    
            }    
}    
    
void UFWT(int a[],int n)    
{    
    for(int d=1;d<n;d<<=1)    
        for(int m=d<<1,i=0;i<n;i+=m)    
            for(int j=0;j<d;j++)    
            {    
                int x=a[i+j],y=a[i+j+d];    
                //xor:
                a[i+j]=1LL*(x+y)*REV%MOD,a[i+j+d]=(1LL*(x-y)*REV%MOD+MOD)%MOD;      
                //and:a[i+j]=x-y;    
                //or:a[i+j+d]=y-x;    
            }    
}    
void solve(int a[],int b[],int n)    
{    
    FWT(a,n);    
    FWT(b,n);    
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%MOD;    
    UFWT(a,n);    
}   
int main()
{
    scanf("%d",&n);
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        cnt[x]++;
    }    
    FWT(cnt,(1<<18));
    for(int i=0;i<(1<<18);i++) p2[i]=1LL*cnt[i]*cnt[i]%MOD;
    for(int i=0;i<(1<<18);i++) p3[i]=1LL*p2[i]*cnt[i]%MOD;
    for(int i=0;i<(1<<18);i++) p4[i]=1LL*p3[i]*cnt[i]%MOD;
    UFWT(cnt,(1<<18)); UFWT(p2,(1<<18)); UFWT(p3,(1<<18)); UFWT(p4,(1<<18));
    //1 1
    dec(p2[0],n);
    for(int i=0;i<(1<<18);i++) p2[i]=1LL*p2[i]*REV%MOD;
    //1 1 1
    for(int i=0;i<(1<<18);i++) dec(p3[i],cnt[i]);
    //1 1 2
    for(int i=0;i<(1<<18);i++) dec(p3[i],3LL*cnt[i]*(n-1)%MOD);
    int inv6=pow_mod(6,MOD-2);
    for(int i=0;i<(1<<18);i++) p3[i]=1LL*p3[i]*inv6%MOD; 
    //1 1 1 1
    dec(p4[0],n); 
    //1 1 1 2
    for(int i=0;i<(1<<18);i++) dec(p4[i],8LL*p2[i]%MOD);
    //1 1 2 2
    dec(p4[0],3LL*n*(n-1)%MOD);
    //1 2 3 3 
    for(int i=0;i<(1<<18);i++) dec(p4[i],12LL*(n-2)%MOD*p2[i]%MOD);
    int inv24=pow_mod(24,MOD-2);
    for(int i=0;i<(1<<18);i++) p4[i]=1LL*p4[i]*inv24%MOD;
    if(p4[0]) puts("Yes"); else puts("No");
    return 0;
}
