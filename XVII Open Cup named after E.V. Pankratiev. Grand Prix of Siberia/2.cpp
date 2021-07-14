#include<bits/stdc++.h>
#define maxn 1005
using namespace std;
int n,m,k;
struct Point
{
    int x,y;
}a[maxn];
bool operator < (Point A,Point B)
{
    if(A.x==B.x)return A.y<B.y;
    return A.x<B.x;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    sort(a+1,a+k+1);
    bool yes=1;
    a[0].x=1;a[0].y=1;
    a[k+1].x=n;a[k+1].y=m;
    for(int i=1;i<=k+1;++i)
    {
        if(a[i].y<a[i-1].y)yes=0;
    }
    if(!yes)puts("Impossible");
    else
    {
        for(int i=1;i<=k+1;++i)
        {
            for(int j=1;j<=a[i].x-a[i-1].x;++j)printf("D");
            for(int j=1;j<=a[i].y-a[i-1].y;++j)printf("R");
        }
    }
}