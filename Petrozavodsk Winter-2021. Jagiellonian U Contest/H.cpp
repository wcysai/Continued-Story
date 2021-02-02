#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define fixed askoasd
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN];
int t,n,k;
vector<int> v1,v2;
int fa[MAXN],dep[MAXN];
vector<int> order;
bool has[MAXN],fixed[MAXN];
int cur;
int children_cnt[MAXN];
int maximum_children[MAXN];
bool flag;
vector<P> op;
bool cmp(int x,int y)
{
    if(dep[x]==dep[y]) return x<y;
    return dep[x]>dep[y];
}
void dfs(int v,int p,int d)
{
    dep[v]=d;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v,d+1);
    }
}
void dfs2(int v,int p)
{
    children_cnt[v]=0;
    fa[v]=p;
    for(auto to:G[v])
    {
        if(to==p||fixed[to]) continue;
        dfs2(to,v);
        if(has[to]) children_cnt[v]++;
    }
}
void try_push(int v,int p)
{
    for(auto to:G[v])
    {
        if(to==p||fixed[to]) continue;
        try_push(to,v);
    }
    if(has[v])
    {
        for(auto to:G[v])
        {
            if(to==p||fixed[to]) continue;
            if(!children_cnt[to])
            {
                has[to]=true;
                has[v]=false;
                children_cnt[fa[v]]--; children_cnt[v]++;
                op.push_back(P(v,to));
            }
            return;
        }
    }
}
void try_pull(int v,int p)
{
    if(flag) return;
    maximum_children[v]=max(maximum_children[v],children_cnt[v]);
    if(has[v])
    {
        if((fa[v]==cur||maximum_children[fa[fa[v]]]==0)&&(children_cnt[fa[v]]==1))
        {
            flag=true;
            has[v]=false;
            has[cur]=true;
            int tmp=v;
            while(tmp!=cur)
            {
                op.push_back(P(tmp,fa[tmp]));
                tmp=fa[tmp];
            }
        }
        return;
    }
    for(auto to:G[v])
    {
        if(to==p||fixed[to]) continue;
        maximum_children[to]=maximum_children[v];
        try_pull(to,v);
    }
}
vector<int> construct_canonical_form(vector<int> &a)
{
    memset(has,false,sizeof(has));
    memset(fixed,false,sizeof(fixed));
    for(auto x:a) has[x]=true;
    for(int i=0;i<n;i++)
    {
        int v=order[i];
        if(has[v]) 
        {
            fixed[v]=true;
            for(auto to:G[v]) fixed[to]=true;
            continue;
        }
        if(fixed[v]) continue;
        cur=v;
        dfs2(v,0);
        try_push(v,0);
        dfs2(v,0); maximum_children[v]=0; flag=false;
        try_pull(v,0);
        fixed[v]=true;
        if(has[v])
        {
            for(auto to:G[v]) fixed[to]=true;
            continue;
        }
    }
    vector<int> ret; ret.clear();
    for(int i=0;i<n;i++) if(has[order[i]]) ret.push_back(order[i]);
    return ret;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=0;i<n-1;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v); G[v].push_back(u);
        }
        dfs(1,0,0);
        order.clear();
        for(int i=1;i<=n;i++) order.push_back(i);
        sort(order.begin(),order.end(),cmp);
        scanf("%d",&k);
        v1.clear();
        for(int i=0;i<k;i++)
        {
            int x;
            scanf("%d",&x);
            v1.push_back(x);
        }
        v2.clear();
        for(int i=0;i<k;i++)
        {
            int x;
            scanf("%d",&x);
            v2.push_back(x);
        }
        op.clear();
        vector<int> p1=construct_canonical_form(v1);
        vector<P> tmp=op;
        op.clear();
        vector<int> p2=construct_canonical_form(v2);
        /*
        for(auto x:p1) printf("%d ",x);
        puts("");
        for(auto x:p2) printf("%d ",x);
        puts("");
        */
        if(p1==p2) 
        {
            puts("YES"); 
            assert((int)op.size()+(int)tmp.size()<=4*n*n);
            printf("%d\n",(int)op.size()+(int)tmp.size());
            for(auto p:tmp) printf("%d %d\n",p.F,p.S);
            for(int i=(int)op.size()-1;i>=0;i--) printf("%d %d\n",op[i].S,op[i].F);
        }
        else puts("NO");
    }
    return 0;
}
