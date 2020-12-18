#include<bits/stdc++.h>
#define maxn 6000005
using namespace std;
typedef long double db;
const db eps = 1e-5;
const int mod = 1000000007;
int T;
int fac[maxn],inv[maxn];
int fastpow(int a,int p)
{
    int ans=1;
    while(p)
    {
        if(p&1)ans=1ll*ans*a%mod;
        p>>=1;a=1ll*a*a%mod;
    }
    return ans;
}
int C(int x,int y)
{
    return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
struct Point
{
    db x,y;
    Point(db x=0,db y=0):x(x),y(y){}
};
int dcmp(db x)
{
    if(fabs(x)<eps)return 0;
    return x>0?1:-1;
}
typedef Point Vector;
Vector operator + (Vector A,Vector B)
{
    return Vector(A.x+B.x,A.y+B.y);
}
Vector operator - (Vector A,Vector B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator * (Vector A,db k)
{
    return Vector(A.x*k,A.y*k);
}
Vector operator / (Vector A,db k)
{
    return Vector(A.x/k,A.y/k);
}
db Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
db Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
Point GetLineIntersection(Point p,Vector v,Point q,Vector w)
{
    return p+v*Cross(w,p-q)/Cross(v,w);
}
bool OnSegment(Point p,Point a1,Point a2)
{
    return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<=0;
}
bool operator < (Point A,Point B)
{
    if(dcmp(A.x-B.x)==0)return A.y<B.y;
    return A.x<B.x;
}
bool operator == (Point A,Point B)
{
    return dcmp(A.x-B.x)==0&&dcmp(A.y-B.y)==0;
}
Point A[5],P,Q;
Point pos[10];
int cnt;
int query(int k,int p)
{
    if(p==-1)return 0;
    return C(k+p+1,k+1);
}
int main()
{
    fac[0]=1;inv[0]=1;
    for(int i=1;i<=6000000;++i)fac[i]=1ll*fac[i-1]*i%mod;
    for(int i=1;i<=6000000;++i)inv[i]=fastpow(fac[i],mod-2);
    scanf("%d",&T);
    while(T--)
    {
        double ax,ay,bx,by,cx,cy;
        scanf("%lf%lf%lf%lf%lf%lf",&ax,&ay,&bx,&by,&cx,&cy);
        A[1].x=ax;A[1].y=ay;A[2].x=bx;A[2].y=by;A[3].x=cx;A[3].y=cy;
        int ans=0;
        for(int k=0;k<=2000000;++k)
        {
            P.x=-10000000;P.y=-10000000+2.0*k;
            Q.x=10000000;Q.y=10000000+2.0*k;
            //cerr<<k<<"::"<<endl;
            cnt=0;
            for(int i=1;i<=2;++i)
                for(int j=i+1;j<=3;++j)if(dcmp(Cross(A[j]-A[i],Q-P))!=0)
                {
                    Point u=GetLineIntersection(A[i],A[j]-A[i],P,Q-P);
                    //cerr<<u.x<<" "<<u.y<<endl;
                    if(OnSegment(u,A[i],A[j]))
                    {
                        pos[++cnt]=u;
                        //cerr<<u.x<<" "<<u.y<<endl;
                    }
                }
            //sort(pos+1,pos+cnt+1);
            //cnt=unique(pos+1,pos+cnt+1)-pos-1;
            //if(cnt==1)pos[2]=pos[1],++cnt;
            //cerr<<"cnt="<<cnt<<endl;
            if(cnt==1)assert(0);
            if(cnt!=0)
            {
                int l=(int)(1e9),r=(int)(-1e9);
                for(int i=1;i<=cnt;++i)
                {
                    l=min(l,(int)floor(pos[i].x+k-(1e-7)));
                    r=max(r,(int)floor(pos[i].x+k+(1e-7)));
                }
                l=max(l,-1);r=max(r,-1);
                //cerr<<"("<<pos[1].x<<","<<pos[1].y<<")"<<" "<<"("<<pos[2].x<<","<<pos[2].y<<")"<<endl;
                //int l=max(-1,(int)floor(pos[1].x+k-(1e-3)));
                //cerr<<pos[2].x+k+eps<<" "<<floor(pos[2].x+k+eps)<<endl;
                //int r=max(-1,(int)floor(pos[2].x+k+(1e-3)));
                //cerr<<l<<" "<<r<<endl;
                ans=(ans+query(k,r))%mod;
                ans=(ans-query(k,l)+mod)%mod;
            }
        }
        printf("%d\n",ans);
    }
}
