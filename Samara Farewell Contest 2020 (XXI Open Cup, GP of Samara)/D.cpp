#include<bits/stdc++.h>
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int a[MAXN];
double prob[MAXN],tmp[MAXN];
int main()
{
    scanf("%d",&n);
    double sum=0.0;
    for(int i=1;i<=n;i++) {scanf("%d",&a[i]); sum+=a[i];}
    sort(a+1,a+n+1);
    int now=n&1;
    if(now==0) 
    {
        now=2;
        prob[2]=1.0; prob[1]=0.0;
    }
    else prob[1]=1.0;
    for(int i=now+2;i<=n;i+=2)
    {
        for(int j=1;j<=i;j++) tmp[j]=0.0;
        tmp[i]=1.0;
        for(int j=i-1;j>=1;j--)
        {
            int less=j-1;
            tmp[j]=prob[j-1]*less/(i-1)+prob[j]*(i-2-less)/(i-1);
        }
        swap(prob,tmp);
    }
    double ans=0.0;
    for(int i=1;i<=n;i++) ans+=prob[i]*a[i];
    printf("%.10f %.10f\n",ans,sum-ans);
    return 0;
}