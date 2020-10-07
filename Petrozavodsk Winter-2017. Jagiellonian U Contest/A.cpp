#include<bits/stdc++.h>
using namespace std;
int z,h,a,b,c,va,vb,vc;
int main(){
    scanf("%d",&z);
    while(z--){
        scanf("%d%d%d%d%d%d%d",&h,&a,&b,&c,&va,&vb,&vc);
        double l=0.0,r=1.0/(max(va,max(vb,vc))*1.0);
        for(int i=1;i<=60;++i){
            double m=(l+r)*0.5,sa=va*m,sb=vb*m,sc=vc*m,ca=sqrt(1.0-sa*sa),cb=sqrt(1.0-sb*sb),cc=sqrt(1.0-sc*sc);
            if(a*sa/ca+b*sb/cb+c*sc/cc<h)l=m;
            else r=m;
        }
        double sa=va*l,sb=vb*l,sc=vc*l,ca=sqrt(1.0-sa*sa),cb=sqrt(1.0-sb*sb),cc=sqrt(1.0-sc*sc);
        double ans=a/ca/va+b/cb/vb+c/cc/vc;
        printf("%.10lf\n",ans);
    }
    return 0;
}
