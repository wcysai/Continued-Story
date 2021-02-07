#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 dsakodas
#define y1 daskodas
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
ll ans;
char str[MAXN][MAXN];
int l[MAXN][MAXN],r[MAXN][MAXN],u[MAXN][MAXN],d[MAXN][MAXN];
int pre[MAXN][MAXN];
int save1[MAXN][MAXN],save2[MAXN][MAXN];
//problem: given an n*m matrix
//find the number of submatrices with the same character on the border
//solution: d&c in O(nmlog(nm))
void solve(int x1,int y1,int x2,int y2)//upper left at(x1,y1) lower right at(x2,y2)
{
    int n=x2-x1+1,m=y2-y1+1;
    if(n<=1||m<=1) return;
    if(n>m)
    {
        //puts("splitting row");
        //printf("ans=%lld\n",ans);
        for(int i=y1;i<=y2;i++)
            for(int j=y1;j<=y2;j++)
                pre[i][j]=save1[i][j]=0;
        int mid=(x1+x2)/2; //split into (x1,y1)(mid,y2) and (mid+1,y1) (x2,y2)
        for(int i=y1;i<=y2;i++)
        {
            //printf("i=%d u=%d\n",i,u[mid][i]);
            for(int j=1;j<=min(mid-x1+1,u[mid][i]);j++)
            {
                //printf("j=%d r=%d\n",j,r[mid+1-j][i]);
                int len=r[mid+1-j][i];
                int rightmost=min(i+len-1,y2);
                pre[i][i+1]++; pre[i][rightmost+1]--;
            }
        }
        for(int i=y1;i<=y2;i++)
            for(int j=y1+1;j<=y2;j++)
                pre[i][j]+=pre[i][j-1];
        for(int i=y1;i<=y2;i++)
            for(int j=i+1;j<=y2;j++)
                if(u[mid][j]>=u[mid][i]) save1[i][j]=pre[i][j];
        for(int i=y1;i<=y2;i++)
            for(int j=y1;j<=y2;j++)
                pre[i][j]=0;
        for(int i=y2;i>=y1;i--)
        {
            //printf("i=%d u=%d\n",i,u[mid][i]);
            for(int j=1;j<=min(mid-x1+1,u[mid][i]);j++)
            {
                //printf("j=%d r=%d\n",j,r[mid+1-j][i]);
                int len=l[mid+1-j][i];
                int leftmost=max(i-len+1,y1);
                pre[i][i-1]++; pre[i][leftmost-1]--;
            }
        }
        for(int i=y1;i<=y2;i++)
            for(int j=y2-1;j>=y1;j--)
                pre[i][j]+=pre[i][j+1];
        for(int i=y1;i<=y2;i++)
            for(int j=i-1;j>=y1;j--)
                if(u[mid][j]>=u[mid][i]) save1[j][i]=pre[i][j];
        for(int i=y1;i<=y2;i++)
            for(int j=y1;j<=y2;j++)
                pre[i][j]=save2[i][j]=0;
        for(int i=y1;i<=y2;i++)
        {
            for(int j=1;j<=min(x2-mid,d[mid+1][i]);j++)
            {
                int len=r[mid+j][i];
                int rightmost=min(i+len-1,y2);
                pre[i][i+1]++; pre[i][rightmost+1]--;
            }
        }
        for(int i=y1;i<=y2;i++)
            for(int j=y1+1;j<=y2;j++)
                pre[i][j]+=pre[i][j-1];
        for(int i=y1;i<=y2;i++)
            for(int j=i+1;j<=y2;j++)
                if(d[mid+1][j]>=d[mid+1][i]) save2[i][j]=pre[i][j];
        for(int i=y1;i<=y2;i++)
            for(int j=y1;j<=y2;j++)
                pre[i][j]=0;
        for(int i=y2;i>=y1;i--)
        {
            for(int j=1;j<=min(x2-mid,d[mid+1][i]);j++)
            {
                int len=l[mid+j][i];
                int leftmost=max(i-len+1,y1);
                pre[i][i-1]++; pre[i][leftmost-1]--;
            }
        }
        for(int i=y1;i<=y2;i++)
            for(int j=y2-1;j>=y1;j--)
                pre[i][j]+=pre[i][j+1];
        for(int i=y1;i<=y2;i++)
            for(int j=i-1;j>=y1;j--)
                if(d[mid+1][j]>=d[mid+1][i]) save2[j][i]=pre[i][j];
        for(int i=y1;i<=y2;i++)
            for(int j=i+1;j<=y2;j++)
                if(str[mid][i]==str[mid][j]&&str[mid+1][i]==str[mid+1][j]&&str[mid][i]==str[mid+1][i]) ans+=1LL*save1[i][j]*save2[i][j];
                
        //printf("ans=%lld\n",ans);
        solve(x1,y1,mid,y2); solve(mid+1,y1,x2,y2);
    }
    else
    {
        for(int i=x1;i<=x2;i++)
            for(int j=x1;j<=x2;j++)
                pre[i][j]=save1[i][j]=0;
        int mid=(y1+y2)/2; //split into (x1,y1)(x2,mid) and (x1,mid+1) (x2,y2)
        for(int i=x1;i<=x2;i++)
        {
            for(int j=1;j<=min(mid-y1+1,l[i][mid]);j++)
            {
                int len=d[i][mid+1-j];
                int downmost=min(i+len-1,x2);
                pre[i][i+1]++; pre[i][downmost+1]--;
            }
        }
        for(int i=x1;i<=x2;i++)
            for(int j=x1+1;j<=x2;j++)
                pre[i][j]+=pre[i][j-1];
        for(int i=x1;i<=x2;i++)
            for(int j=i+1;j<=x2;j++)
                if(l[j][mid]>=l[i][mid]) save1[i][j]=pre[i][j];
        for(int i=x1;i<=x2;i++)
            for(int j=x1;j<=x2;j++)
                pre[i][j]=0;
        for(int i=x2;i>=x1;i--)
        {
            for(int j=1;j<=min(mid-y1+1,l[i][mid]);j++)
            {
                int len=u[i][mid+1-j];
                int upmost=max(i-len+1,x1);
                pre[i][i-1]++; pre[i][upmost-1]--;
            }
        }
        for(int i=x1;i<=x2;i++)
            for(int j=x2-1;j>=x1;j--)
                pre[i][j]+=pre[i][j+1];
        for(int i=x1;i<=x2;i++)
            for(int j=i-1;j>=x1;j--)
                if(l[j][mid]>=l[i][mid]) save1[j][i]=pre[i][j];
        for(int i=x1;i<=x2;i++)
            for(int j=x1;j<=x2;j++)
                pre[i][j]=save2[i][j]=0;
        for(int i=x1;i<=x2;i++)
        {
            for(int j=1;j<=min(y2-mid,r[i][mid+1]);j++)
            {
                int len=d[i][mid+j];
                int downmost=min(i+len-1,x2);
                pre[i][i+1]++; pre[i][downmost+1]--;
            }
        }
        for(int i=x1;i<=x2;i++)
            for(int j=x1+1;j<=x2;j++)
                pre[i][j]+=pre[i][j-1];
        for(int i=x1;i<=x2;i++)
            for(int j=i+1;j<=x2;j++)
                if(r[j][mid+1]>=r[i][mid+1]) save2[i][j]=pre[i][j];
        for(int i=x1;i<=x2;i++)
            for(int j=x1;j<=x2;j++)
                pre[i][j]=0;
        for(int i=x2;i>=x1;i--)
        {
            for(int j=1;j<=min(y2-mid,r[i][mid+1]);j++)
            {
                int len=u[i][mid+j];
                int upmost=max(i-len+1,x1);
                pre[i][i-1]++; pre[i][upmost-1]--;
            }
        }
        for(int i=x1;i<=x2;i++)
            for(int j=x2-1;j>=x1;j--)
                pre[i][j]+=pre[i][j+1];
        for(int i=x1;i<=x2;i++)
            for(int j=i-1;j>=x1;j--)
                if(r[j][mid+1]>=r[i][mid+1]) save2[j][i]=pre[i][j];
        for(int i=x1;i<=x2;i++)
            for(int j=i+1;j<=x2;j++)
                if(str[i][mid]==str[j][mid]&&str[i][mid+1]==str[j][mid+1]&&str[i][mid]==str[i][mid+1])
                    ans+=1LL*save1[i][j]*save2[i][j];
        solve(x1,y1,x2,mid); solve(x1,mid+1,x2,y2);
    }
}
int main()
{
    //freopen("E.in","r",stdin);
    ans=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(j==1||str[i][j-1]!=str[i][j]) l[i][j]=1; else l[i][j]=l[i][j-1]+1;
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
            if(j==m||str[i][j+1]!=str[i][j]) r[i][j]=1; else r[i][j]=r[i][j+1]+1; 
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(j==1||str[j-1][i]!=str[j][i]) u[j][i]=1; else u[j][i]=u[j-1][i]+1;
    for(int i=1;i<=m;i++)
        for(int j=n;j>=1;j--)
            if(j==n||str[j+1][i]!=str[j][i]) d[j][i]=1; else d[j][i]=d[j+1][i]+1;
    ans=0;
    solve(1,1,n,m);
    printf("%lld\n",ans);
}