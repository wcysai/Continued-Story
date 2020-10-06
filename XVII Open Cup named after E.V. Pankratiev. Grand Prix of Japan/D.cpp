#include<bits/stdc++.h>
#define maxn 1005
using namespace std;
int n;
struct Point
{
    int x,y;
}a[maxn];
bool cmpx(Point A,Point B)
{
    return A.x<B.x;
}
bool cmpy(Point A,Point B)
{
    return A.y<B.y;
}
int has[maxn][maxn],has2[maxn][maxn];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i].x=x;a[i].y=y;
        has[x][y]=1;has2[x][y]=1;
    }
    sort(a+1,a+n+1,cmpx);
    for(int i=1;i<=n;++i)
    {
        bool up=1,down=1;
        //cerr<<a[i].x<<" "<<a[i].y<<" ::::"<<endl;
        for(int j=i-1;j>=1;--j)if(a[i].x!=a[j].x)
        {
            if(a[j].y<a[i].y)
            {
                if(!down)continue;
                down=0;
                has2[a[j].x][a[i].y]=1;
                //cerr<<a[j].x<<" "<<a[i].y<<endl;
            }
            if(a[j].y>a[i].y)
            {
                if(!up)continue;
                up=0;
                has2[a[j].x][a[i].y]=1;
                //cerr<<a[j].x<<" "<<a[i].y<<endl;
            }
        }
    }
    for(int i=n;i>=1;--i)
    {
        bool up=1,down=1;
        for(int j=i+1;j<=n;++j)if(a[i].x!=a[j].x)
        {
            if(a[j].y<a[i].y)
            {
                if(!down)continue;
                down=0;
                has2[a[j].x][a[i].y]=1;
            }
            if(a[j].y>a[i].y)
            {
                if(!up)continue;
                up=0;
                has2[a[j].x][a[i].y]=1;
            }
        }
    }
    sort(a+1,a+n+1,cmpy);
    for(int i=1;i<=n;++i)
    {
        bool up=1,down=1;
        for(int j=i-1;j>=1;--j)if(a[i].y!=a[j].y)
        {
            if(a[j].x<a[i].x)
            {
                if(!down)continue;
                down=0;
                has2[a[i].x][a[j].y]=1;
            }
            if(a[j].x>a[i].x)
            {
                if(!up)continue;
                up=0;
                has2[a[i].x][a[j].y]=1;
            }
        }
    }
    for(int i=n;i>=1;--i)
    {
        bool up=1,down=1;
        for(int j=i+1;j<=n;++j)if(a[i].y!=a[j].y)
        {
            if(a[j].x<a[i].x)
            {
                if(!down)continue;
                down=0;
                has2[a[i].x][a[j].y]=1;
            }
            if(a[j].x>a[i].x)
            {
                if(!up)continue;
                up=0;
                has2[a[i].x][a[j].y]=1;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=1000;++i)
        for(int j=1;j<=1000;++j)if(has2[i][j]&&(!has[i][j]))ans++;
    printf("%d\n",ans);
    for(int i=1;i<=1000;++i)
        for(int j=1;j<=1000;++j)if(has2[i][j]&&(!has[i][j]))printf("%d %d\n",i,j);
}
