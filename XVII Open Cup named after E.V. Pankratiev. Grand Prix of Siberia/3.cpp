#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
int ax,ay,bx,by,cx,cy;
int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
double query(int x,int y,int xx,int yy)
{
    int A=y-yy;
    int B=xx-x;
    int C=x*yy-xx*y;
    printf("? %d %d %d\n",A,B,C);
    fflush(stdout);
    double p;
    scanf("%lf",&p);
    return p;
}
int U,D,L,R;
void getbound()
{
    int l,r,ans;
    l=-1000,r=1000,ans=-1000;
    while(l<=r)
    {
        int mid=(l+r)/2;
        double p=query(-1000,mid,1000,mid);
        if(dcmp(p)==0)ans=mid,l=mid+1;
        else r=mid-1;
    }
    D=ans;
    l=-1000,r=1000,ans=1000;
    while(l<=r)
    {
        int mid=(l+r)/2;
        double p=query(-1000,mid,1000,mid);
        if(dcmp(p-1)==0)ans=mid,r=mid-1;
        else l=mid+1;
    }
    U=ans;
    l=-1000,r=1000,ans=-1000;
    while(l<=r)
    {
        int mid=(l+r)/2;
        double p=query(mid,-1000,mid,1000);
        if(dcmp(p)==0)ans=mid,l=mid+1;
        else r=mid-1;
    }
    L=ans;
    l=-1000,r=1000,ans=1000;
    while(l<=r)
    {
        int mid=(l+r)/2;
        double p=query(mid,-1000,mid,1000);
        if(dcmp(p-1)==0)ans=mid,r=mid-1;
        else l=mid+1;
    }
    R=ans;
}
int main()
{
    getbound();
    if(dcmp(query(L,D+1,L+1,D)-0)>0)
    {
        ax=L;ay=D;
        int l,r,ans;
        l=D;r=U;
        
    }
    else if(dcmp(query(L+1,U,L,U-1))>0)
    {

    }
    else if(dcmp(query(R-1,U,R,U-1))>0)
    {

    }
    else if(dcmp(query(R-1,D,R,D+1))>0)
    {

    }
}