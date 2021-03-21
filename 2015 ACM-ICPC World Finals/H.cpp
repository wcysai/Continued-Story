#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int _w,_h,n;
double h;
double pos[MAXN],ans[MAXN];
double res[MAXN];
double _ans;
int main()
{
    scanf("%d%d%d",&_w,&_h,&n);
    h=1.0*_h/_w;
    pos[0]=(1.0-h)/2; ans[0]=0.5*0.5*(1+h)*(1+h);
    for(int i=1;i<=n;i++)
    {
        double a,b,c;
        a=ans[0]+ans[i-1]-h-h*h*0.5;
        b=-2*ans[i-1]+h;
        c=ans[i-1]+h*h*0.5;
        pos[i]=-b/(2*a);
        ans[i]=a*pos[i]*pos[i]+b*pos[i]+c;
    }
    printf("%.15f\n",ans[n]*_w*_w);
    double now=_w;
    for(int i=n;i>=1;i--)
    {
        res[i]=now*(1.0-pos[i]);
        now=res[i];
    }
    for(int i=1;i<=min(10,n);i++) printf("%.15f\n",res[i]);
    return 0;
}