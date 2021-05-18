#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define MAXN 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 sbcjb
#define x2 cjbsb
#define y1 cjbnt
#define y2 ntcjb
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int d,n,ans;
int dx[8]={-1,0,-1,-1,1,0,1,1};
int dy[8]={0,-1,-1,1,0,1,1,-1};
int vdx[4]={-1,0,1,0};
int vdy[4]={0,-1,0,1};
bool valid[8];
//W,S,SW,NW,E,N,NE,SE
string str;
int x[MAXN],y[MAXN];
int tmp[MAXN][3][3];
int id[4];
int get_moves(int id,int nx,int ny)
{
    int k;
    if(dx[id]!=0) k=nx/dx[id];
    else k=ny/dy[id];
    if(k<0||k*dx[id]!=nx||k*dy[id]!=ny) return INF; else return k;
}
int calc_minsteps(int id,int sx,int sy)
{
    sx=sx-x[id]; sy=sy-y[id];
    int res=INF;
    for(int j=0;j<8;j++)
    {
        if(!valid[j]) continue;
        for(int k=j;k<8;k++)
        {
            if(!valid[k]) continue;
            int nx=sx,ny=sy;
            if(j==k||k==j+4)//colinear
            {
                res=min(res,get_moves(j,nx,ny));
                if(k==j+4) res=min(res,get_moves(k,nx,ny));
            }
            else//not colinear
            {
                int x1=dx[j],x2=dx[k],y1=dy[j],y2=dy[k],a,b;//ax1+bx2=nx, ay1+by2=ny, solve for (a,b)
                a=(nx*y2-ny*x2)/(x1*y2-x2*y1);
                if(x2!=0) b=(nx-a*x1)/x2; else b=(ny-a*y1)/y2;
                //printf("i=%d j=%d k=%d nx=%d ny=%d x1=%d x2=%d y1=%d y2=%d a=%d b=%d\n",i,j,k,nx,ny,x1,x2,y1,y2,a,b);
                if(a*x1+b*x2!=nx||a*y1+b*y2!=ny) continue;
                if(a>=0&&b>=0) res=min(res,a+b);
            }
        }
    }
    return res;
}
void calc(int sx,int sy)
{
    for(int i=0;i<n;i++)
    {
        for(int j=-1;j<=1;j++)
            for(int k=-1;k<=1;k++)
                tmp[i][j+1][k+1]=calc_minsteps(i,sx+j,sy+k);
    }
    for(int j=-1;j<=1;j++)
        for(int k=-1;k<=1;k++)
        {
            int res=0;
            for(int i=0;i<n;i++)
            {
                int val=tmp[i][j+1][k+1];
                for(int dir=0;dir<4;dir++) 
                {
                    if(!valid[id[dir]]) continue;
                    if(j-vdx[dir]<-1||j-vdx[dir]>1||k-vdy[dir]<-1||k-vdy[dir]>1) continue;
                    val=min(val,1+tmp[i][j+1-vdx[dir]][k+1-vdy[dir]]);
                }
                if(val==INF) {res=INF; break;} else res+=val;
            }
            if(res!=INF) ans=min(ans,res);
        }
}
int main()
{
    memset(valid,false,sizeof(valid));
    id[0]=0; id[1]=1; id[2]=4; id[3]=5;
    scanf("%d",&d);
    for(int i=0;i<d;i++)
    {
        cin>>str;
        if(str=="W") valid[0]=true;
        else if(str=="S") valid[1]=true;
        else if(str=="SW") valid[2]=true;
        else if(str=="NW") valid[3]=true;
        else if(str=="E") valid[4]=true;
        else if(str=="N") valid[5]=true;
        else if(str=="NE") valid[6]=true;
        else valid[7]=true;
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d%d",&x[i],&y[i]);
    ans=INF;
    for(int i=0;i<n;i++) calc(x[i],y[i]);
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
        {
            for(int dir1=0;dir1<8;dir1++)
            {
                for(int dir2=0;dir2<8;dir2++)
                {
                    if(dir1==dir2||dir1==dir2+4||dir2==dir1+4) continue;
                    int nx=x[j]-x[i],ny=y[j]-y[i];
                    int x1=dx[dir1],x2=dx[dir2],y1=dy[dir1],y2=dy[dir2],a,b;//ax1+bx2=nx, ay1+by2=ny, solve for (a,b)
                    a=(nx*y2-ny*x2)/(x1*y2-x2*y1);
                    if(x2!=0) b=(nx-a*x1)/x2; else b=(ny-a*y1)/y2;
                    if(a*x1+b*x2!=nx||a*y1+b*y2!=ny) continue;
                    if(a>0&&b>0)
                    {
                        int tx=x[i]+a*x1,ty=y[i]+a*y1;
                        calc(tx,ty);
                    }
                }
            }
        }
    printf("%d\n",ans);
    return 0;
}