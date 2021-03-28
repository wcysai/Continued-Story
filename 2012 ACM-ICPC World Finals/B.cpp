#include<bits/stdc++.h>
using namespace std;
int n,T;
double a[30],b[30],xl,xh,inc,pi=acos(-1.0);
double f(double x){
    double ans=0;
    for(int i=n;i>=0;--i)ans=ans*x+b[i];
    return ans;
}
double g(double x){
    double l=xl,r=xh;
    for(int _=0;_<100;++_){
        double m=(l+r)/2;
        if(f(m)<x)l=m;
        else r=m;
    }
    return l;
}
int main(){
    while(scanf("%d",&n)==1){
        ++T;
        for(int i=0;i<=n;++i)scanf("%lf",a+i);
        for(int i=0;i<=n*2;++i){
            b[i]=0;
            for(int j=0;j<=i;++j)b[i]+=a[j]*a[i-j];
        }
        n*=2;
        for(int i=n;i>=0;--i)b[i+1]=b[i]/(i+1)*pi;
        ++n;
        printf("%lf%lf%lf",&xl,&xh,&inc);
        b[0]=-f(xl);
        double H=f(xh);
        printf("Case %d: %.2f\n",T,H);
        if(H<inc){
            printf("insufficient volume\n");
            continue;
        }
        int t=(int)min(8.00001,H/inc);
        for(int i=1;i<t;++i)printf("%.2f ",g(i*inc));
        printf("%.2f\n",g(t*inc));
    }
    return 0;
}