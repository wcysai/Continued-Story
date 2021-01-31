#include<bits/stdc++.h>
#define MAXN 1000005
#define MOD 1000000007
#define INV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
ll ans;
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
    scanf("%d",&n);
    int fst=0;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        if(a[i]==1&&fst==0) fst=i;
    }
    if(!fst) {puts("0"); return 0;}
    int cnt2=0,cnt3=0,res=0,ans=0;
    for(int i=fst+1;i<=n;i++)
    {
        if(a[i]==2) cnt2++;
        else if(a[i]==3) 
        {
            add(res,pow_mod(2,cnt2));
            dec(res,1);
            cnt3++;
        }
    }
    add(ans,res);
    for(int i=fst+1;i<=n;i++)
    {
        if(a[i]==1) add(ans,res);
        else if(a[i]==2)
        {
            dec(res,cnt3);
            res=1LL*res*INV%MOD;
        }
        else if(a[i]==3) cnt3--;
    }
    printf("%d\n",ans);
}