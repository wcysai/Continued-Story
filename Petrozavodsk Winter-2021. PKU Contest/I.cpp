#include<bits/stdc++.h>
#define MAXN 205
#define MAXM 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int color[MAXN][MAXN];
vector<P> colors[MAXN];
bool has[MAXN];
int x,y,fore,rear,cnt,ans,father[MAXN],f[MAXN],path[MAXN],tra[MAXN],que[MAXN],match[MAXN];
bool a[MAXN][MAXN],check[MAXN],treec[MAXN],pathc[MAXN];
bool val[MAXN];
vector<int> valid;
inline void push(int x)
{
    que[++rear]=x;
    check[x]=true;
    if(!treec[x])
    {
        tra[++cnt]=x;
        treec[x]=true;
    }
}
int root(int x){return f[x]?f[x]=root(f[x]):x;}

void clear()
{
    for(int i=1,j;i<=cnt;++i)
    {
        j=tra[i];
        check[j]=treec[j]=false;
        father[j]=0,f[j]=0;
    }
}

int lca(int u,int v)
{
    int len=0;
    for(;u;u=father[match[u]])
    {
        u=root(u);
        path[++len]=u;
        pathc[u]=true;
    }
    for(;;v=father[match[v]])
    {
        v=root(v);
        if(pathc[v]) break;
    }
    for(int i=1;i<=len;++i)
    {
        pathc[path[i]]=false;
    }
    return v;
}

void reset(int u,int p)
{
    for(int v;root(u)!=p;)
    {
        if(!check[v=match[u]]) push(v);
        if(f[u]==0) f[u]=p;
        if(f[v]==0) f[v]=p;
        u=father[v];
        if(root(u)!=p) father[u]=v;
    }
}

void flower(int u,int v)
{
    int p=lca(u,v);
    if(root(u)!=p) father[u]=v;
    if(root(v)!=p) father[v]=u;
    reset(u,p),reset(v,p);
}

bool find(int x)
{
    fore=rear=cnt=0,push(x);
    while(fore++<rear)
    {
        int i=que[fore];
        for(auto j:valid)
        {
            if(a[i][j]&&root(i)!=root(j)&&match[j]!=i)
              if(match[j]&&father[match[j]])
                 flower(i,j);
              else if(father[j]==0)
              {
                  father[j]=i;
                  tra[++cnt]=j;
                  treec[j]=true;
                  if(match[j])
                    push(match[j]);
                  else
                  {
                      for(int k=i,l=j,p;k;l=p,k=father[l])
                      {
                          p=match[k];
                          match[k]=l;
                          match[l]=k;
                      }
                      return true;
                  }
              }
        }
    }
    return false;
}

void matching()
{
    ans=0;
    for(int i=1;i<=m+1;i++) father[i]=f[i]=path[i]=tra[i]=que[i]=match[i]=check[i]=treec[i]=pathc[i]=0;
    for(auto x:valid)
        if(match[x]==0)
        {
            if(find(x)) ans++;
            clear();
        }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++)
    {
        for(int j=1;j<=n-i;j++)
        {
            int x;scanf("%d",&x);
            color[i][i+j]=color[i+j][i]=x;
            colors[x].push_back(P(i,i+j));
        }
    }
    for(int i=1;i<=n;i++)
    {
        memset(has,false,sizeof(has));
        for(int j=1;j<=i;j++) 
        {
            if(has[color[i][j]])
            {
                puts("No");
                return 0;
            }
            has[color[i][j]]=true;
        }
    }
    if(m%2==0) {puts("No"); return 0;}
    for(int i=1;i<=m+1;i++)
        for(int j=1;j<=m+1;j++)
            if(i==j||(i<=n&&j<=n)) a[i][j]=false; else a[i][j]=true;
    for(int i=1;i<=m;i++)
    {
        valid.clear();
        for(int j=1;j<=m+1;j++) val[j]=true;
        for(auto p:colors[i]) val[p.F]=val[p.S]=false;
        for(int j=1;j<=m+1;j++) if(val[j]) valid.push_back(j);
        printf("i=%d\n",i);
        matching();
        if(ans!=(m+1)/2-(int)colors[i].size()) 
        {
            puts("No");
            return 0;
        }
        for(int j=1;j<=m+1;j++)
        {
            if(val[j])
            {
                color[j][match[j]]=i;
                a[j][match[j]]=false;
            }
        }
    }
    puts("Yes");
    for(int i=1;i<=m+1;i++)
    {
        for(int j=1;j<=m+1-i;j++)
        {
            assert(color[i][i+j]>=1&&color[i][i+j]<=m);
            printf("%d ",color[i][i+j]);
        }
        puts("");
    }
    return 0;
}