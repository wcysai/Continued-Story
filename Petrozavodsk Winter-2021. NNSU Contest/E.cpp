#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t;
int n,m,x,y,fore,rear,cnt,ans,father[MAXN],f[MAXN],path[MAXN],tra[MAXN],que[MAXN],match[MAXN];
bool a[MAXN][MAXN],check[MAXN],treec[MAXN],pathc[MAXN];
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
        for(int j=1;j<=n;++j)
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
    for(int i=1;i<=n;i++) father[i]=f[i]=path[i]=tra[i]=que[i]=match[i]=check[i]=treec[i]=pathc[i]=0;
    ans=0;
    for(int i=1;i<=n;i++)
        if(match[i]==0)
        {
            if(find(i)) ans++;
            clear();
        }
}

vector<int> G[MAXN];
vector<int> rG[MAXN];
vector<int> vs;
bool used[MAXN];
int cmp[MAXN];
int u[MAXM],v[MAXM];
void add_edge(int from,int to)
{
    G[from].push_back(to);
    rG[to].push_back(from);
}
void erase_edge(int from,int to)
{
    for(int i=0;i<(int)G[from].size();i++) if(G[from][i]==to) {G[from].erase(G[from].begin()+i); break;}
    for(int i=0;i<(int)rG[to].size();i++) if(rG[to][i]==from) {rG[to].erase(rG[to].begin()+i); break;}
}
void dfs(int v)
{
    used[v]=true;
    for(int i=0;i<(int)G[v].size();i++)
        if(!used[G[v][i]]) dfs(G[v][i]);
    vs.push_back(v);
}
void rdfs(int v,int k)
{
    used[v]=true;
    cmp[v]=k;
    for(int i=0;i<(int)rG[v].size();i++)
        if(!used[rG[v][i]]) rdfs(rG[v][i],k);
}
int scc()
{
    memset(used,0,sizeof(used));
    vs.clear();
    for(int v=1;v<=2*n;v++) if(!used[v]) dfs(v);
    int k=0;
    memset(used,0,sizeof(used));
    for(int i=vs.size()-1;i>=0;i--) if(!used[vs[i]]) rdfs(vs[i],k++);
    return k;
}

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=2*n;i++) G[i].clear(),rG[i].clear();
        for(int i=1;i<=n;i++) 
            for(int j=1;j<=n;j++)
                a[i][j]=(i==j?true:false);
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u[i],&v[i]);
            a[u[i]][v[i]]=a[v[i]][u[i]]=true;
        }
        matching();
        for(int i=0;i<m;i++)
        {
            add_edge(n+u[i],v[i]);
            add_edge(n+v[i],u[i]);
            if(match[u[i]]==v[i])
            {
                add_edge(u[i],n+v[i]);
                add_edge(v[i],n+u[i]);
            }
        }
        for(int i=1;i<=n;i++) if(match[i]==0) add_edge(i,n+i);
        scc();
        bool f=true;
        for(int i=1;i<=n;i++) if(cmp[i]==cmp[n+i]) f=false;
        if(f)
        {
            printf("%d\n",ans);
            for(int i=1;i<=n;i++) if(cmp[i]>cmp[n+i]) printf("%d ",i);
            puts("");
            continue;
        }
       
        //take both vertices from a matching
        bool flag=false;
        for(int i=0;i<m;i++)
        {
            if(match[u[i]]!=v[i]) continue;
            erase_edge(u[i],n+v[i]);
            erase_edge(v[i],n+u[i]);
            add_edge(n+u[i],u[i]);
            add_edge(n+v[i],v[i]);
            scc();
            bool f=true;
            for(int j=1;j<=n;j++) if(cmp[j]==cmp[n+j]) f=false;
            if(f)
            {
                printf("%d\n",ans+1);
                for(int j=1;j<=n;j++) if(cmp[j]>cmp[n+j]) printf("%d ",j);
                puts("");
                flag=true; break;
            }
            erase_edge(n+u[i],u[i]);
            erase_edge(n+v[i],v[i]);
            add_edge(u[i],n+v[i]);
            add_edge(v[i],n+u[i]);
        }
        if(flag) continue;
        //take an isolated vertex
        for(int i=1;i<=n;i++)
        {
            if(match[i]) continue;
            erase_edge(i,n+i);
            add_edge(n+i,i);
            scc();
            bool f=true;
            for(int j=1;j<=n;j++) if(cmp[j]==cmp[n+j]) f=false;
            if(f)
            {
                printf("%d\n",ans+1);
                for(int j=1;j<=n;j++) if(cmp[j]>cmp[n+j]) printf("%d ",j);
                puts("");
                flag=true; break;
            }
            erase_edge(n+i,i);
            add_edge(i,n+i);
        }
        if(flag) continue;
        puts("not smol");
    }
    return 0;
}
