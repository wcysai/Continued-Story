#include<bits/stdc++.h>
using namespace std;
int p,a,b,c,d,n;
double m,ans;
int main(){
    scanf("%d%d%d%d%d%d",&p,&a,&b,&c,&d,&n);
    for(int i=1;i<=n;++i){
        double x=sin(a*i+b)+cos(c*i+d)+2;
        if(x<m)ans=max(ans,m-x);
        else m=x;
    }
    printf("%.10lf\n",ans*p);
    return 0;
}