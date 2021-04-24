#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int main()
{
    int ans=1000000;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ans=min(ans,y/x);
    }
    printf("%d\n",ans);
}