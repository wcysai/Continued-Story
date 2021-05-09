//team continued story
#include<bits/stdc++.h>
#define maxn 105
using namespace std;
const double PI = acos(-1.0);
const double eps = 1e-8;
double dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
struct Point3
{
    double x,y,z;
    Point3(double x=0,double y=0,double z=0):x(x),y(y),z(z){}
};
typedef Point3 Vector3;
Vector3 operator + (Vector3 A,Vector3 B)
{
    return Vector3(A.x+B.x,A.y+B.y,A.z+B.z);
}
Vector3 operator - (Vector3 A,Vector3 B)
{
    return Vector3(A.x-B.x,A.y-B.y,A.z-B.z);
}
Vector3 operator * (Vector3 A,double p)
{
    return Vector3(A.x*p,A.y*p,A.z*p);
}
Vector3 operator / (Vector3 A,double p)
{
    return Vector3(A.x/p,A.y/p,A.z/p);
}
double Dot(Vector3 A,Vector3 B){return A.x*B.x+A.y*B.y+A.z*B.z;}
double Length(Vector3 A){return sqrt(Dot(A,A));}
double Angle(Vector3 A,Vector3 B)
{
    if(fabs(Length(A))<eps)assert(0);
    if(fabs(Length(B))<eps)assert(0);
    double t=Dot(A,B)/Length(A)/Length(B);
    t=max(t,-1.0);t=min(t,1.0);
    return acos(t);
}
Vector3 Cross(Vector3 A,Vector3 B){return Vector3(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x);}
double Area(Point3 A,Point3 B,Point3 C){return Length(Cross(B-A,C-A))/2;}


int V,E,F;
double d;
Point3 a[maxn];
struct E{int u,v;}b[maxn];
int has[maxn][maxn],facesz[maxn],used[maxn][maxn];
double ans;
vector<int> face[maxn];
int main()
{
    //freopen("C.in","r",stdin);
    scanf("%d",&V);
    for(int i=0;i<V;++i)scanf("%lf%lf%lf",&a[i].x,&a[i].y,&a[i].z);
    scanf("%d",&E);
    for(int i=0;i<E;++i)scanf("%d%d",&b[i].u,&b[i].v);
    scanf("%d",&F);
    for(int i=0;i<F;++i)
    {
        scanf("%d",&facesz[i]);
        if(facesz[i]<3)assert(0);
        for(int j=0;j<facesz[i];++j)
        {
            int x;
            scanf("%d",&x);
            has[i][x]=1;
        }
    }
    scanf("%lf",&d);
    for(int i=0;i<F;++i)
    {
        int lst=-1;
        for(int j=0;j<E;++j)if(has[i][j])
        {
            face[i].push_back(b[j].v);
            lst=b[j].v;
            used[i][j]=1;
            break;
        }
        for(int j=1;j<facesz[i];++j)
        {
            for(int k=0;k<E;++k)if(has[i][k]&&!used[i][k])
            {
                if(b[k].u==lst)
                {
                    face[i].push_back(b[k].v);
                    used[i][k]=1;
                    lst=b[k].v;
                }
                else if(b[k].v==lst)
                {
                    face[i].push_back(b[k].u);
                    used[i][k]=1;
                    lst=b[k].u;
                }
            }
        }
        //for(int j=0;j<facesz[i];++j)cerr<<"("<<a[face[i][j]].x<<","<<a[face[i][j]].y<<","<<a[face[i][j]].z<<") ";
        //cerr<<endl;
        int N=facesz[i];
        double ar=0;
        for(int j=0;j<N;++j)
        {
            ar+=Area(a[face[i][0]],a[face[i][j]],a[face[i][(j+1)%N]]);
        }
        ans+=abs(ar)*d;
    }
    for(int i=0;i<E;++i)
    {
        for(int x=0;x<F;++x)if(has[x][i])
        {
            int X=-1;
            for(int u:face[x])if(fabs(Length(Cross(a[b[i].u]-a[b[i].v],a[u]-a[b[i].v])))>eps)X=u;
            for(int y=x+1;y<F;++y)if(has[y][i])
            {
                int Y=-1;
                for(int v:face[y])if(fabs(Length(Cross(a[b[i].u]-a[b[i].v],a[v]-a[b[i].v])))>eps)Y=v;

                if(X==-1||Y==-1)assert(0);

                Vector3 Norx=Cross(a[b[i].u]-a[b[i].v],a[X]-a[b[i].v]),Nory=Cross(a[Y]-a[b[i].v],a[b[i].u]-a[b[i].v]);
                double ang=Angle(Norx,Nory);//::
                if(fabs(ang-PI)<eps)ang=0;
                //cerr<<ang<<endl;
                ans+=0.5*ang*d*d*Length(a[b[i].u]-a[b[i].v]);
                //cerr<<ans<<endl;
            }
        }
    }
    ans+=4.0*PI*d*d*d/3.0;
    printf("%.10f\n",ans);
}