#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,m,p[3],shift[3];
int a[MAXN][MAXN],b[MAXN][MAXN];
string str;
// a[p[0]+shift[p[0]]][p[1]+shift[p[1]]]=[p[2]+shift[p[2]]];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) 
            for(int j=1;j<=n;j++)
                scanf("%d",&a[i][j]);
        p[0]=0; p[1]=1; p[2]=2;
        shift[0]=shift[1]=shift[2]=0;
        cin>>str;
        for(int i=0;i<m;i++)
        {
            if(str[i]=='I') swap(p[1],p[2]);
            else if(str[i]=='C') swap(p[0],p[2]);
            else if(str[i]=='R') shift[p[1]]++;
            else if(str[i]=='L') {shift[p[1]]--; if(shift[p[1]]<0) shift[p[1]]+=n;}
            else if(str[i]=='D') shift[p[0]]++;
            else {shift[p[0]]--; if(shift[p[0]]<0) shift[p[0]]+=n;}
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)   
            {
                int val[3];
                val[0]=i; val[1]=j; val[2]=a[i][j];
                int x=(val[p[0]]+shift[p[0]])%n; if(x==0) x=n;
                int y=(val[p[1]]+shift[p[1]])%n; if(y==0) y=n;
                int z=(val[p[2]]+shift[p[2]])%n; if(z==0) z=n;
                b[x][y]=z;
            }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++) printf("%d ",b[i][j]);
            puts("");
        }
    }
    return 0;
}