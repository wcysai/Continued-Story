#include<bits/stdc++.h>
using namespace std;
int n,k;
priority_queue< int,vector<int>,greater<int> > q;
int main()
{
    scanf("%d%d",&n,&k);
    int ans=0;
    for(int i=1;i<=k;++i)
    {
        int x;
        scanf("%d",&x);
        q.push(x);
        ans+=x;
    }
    printf("%d ",ans);
    for(int i=k+1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x>q.top())
        {
            ans-=q.top();
            q.pop();
            ans+=x;
            q.push(x);
        }
        printf("%d%c",ans,(i==n)?'\n':' ');
    }
}