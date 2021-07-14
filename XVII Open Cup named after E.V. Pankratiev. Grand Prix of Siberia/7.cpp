#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int state[MAXN];
int tot,fa[MAXN],root;
set<int> upd;
set<int> children[MAXN];
map<int,int> mp;
set<int> marked;
set<int> added,removed,modified;
vector<int> updated;
bool vis[MAXN];
int id[MAXN];
string str;
int get_id(int x)
{
    if(mp.find(x)==mp.end()) {mp[x]=++tot; id[tot]=x;}
    return mp[x];
}
int find_root(int x)
{
    if(fa[x]==0) return x;
    else return find_root(fa[x]);
}
void go(int v,int st)
{
    if(vis[v]) return;
    if(st==state[v]) return;
    if(st==1) removed.insert(v); else added.insert(v);
    updated.push_back(v);
    vis[v]=true;
    for(auto to:children[v])
        go(to,st);
}
void modify(int v)
{
    if(!state[v]) modified.insert(v);
    for(auto to:children[v])
    {
        if(marked.count(to)) continue;
        modify(to);
    }
}
void output(set<int> &s)
{
    set<int> ns;
    for(auto x:s) ns.insert(id[x]);
    for(auto x:ns) printf(" %d",x);
    puts("");
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        x=get_id(x);
        int t;
        scanf("%d",&t);
        for(int j=0;j<t;j++)
        {
            int y;
            scanf("%d",&y);
            y=get_id(y);
            fa[y]=x;
            children[x].insert(y);
        }
    }
    for(int i=1;i<=tot;i++) if(!fa[i]) root=i;
    scanf("%d",&m);
    for(int i=0;i<m;i++)
    {
        cin>>str;
        if(str=="remove")
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x=get_id(x); y=get_id(y);
            children[x].erase(y);
            marked.insert(y);
            fa[y]=0; upd.insert(y);
        }
        else if(str=="add")
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x=get_id(x); y=get_id(y);
            children[x].insert(y);
            fa[y]=x; upd.insert(y);
        }
        else if(str=="modify")
        {
            int x;
            scanf("%d",&x);
            x=get_id(x);
            marked.insert(x);
        }
        else
        {
            for(auto x:upd)
            {
                int rt=find_root(x);
                go(x,(rt==root?0:1));
            }
            for(auto x:marked)
            {
                int rt=find_root(x);
                if(rt==root) modify(x);
            }
            printf("added %d",(int)added.size());
            output(added);
            printf("removed %d",(int)removed.size());
            output(removed);
            printf("modified %d",(int)modified.size());
            output(modified);
            for(auto x:updated) {vis[x]=false; state[x]^=1;}
            upd.clear();
            added.clear();
            marked.clear();
            removed.clear();
            modified.clear();
            updated.clear();
        }
    }
    return 0;
}
/*
8
3 0
5 3 7 6 12
17 1 20
7 0
6 0
12 0
20 0
666 3 3 5 17
14
remove 17 20
render
remove 666 5
add 5 20
modify 20
render
add 3 5
render 
modify 5
render 
remove 3 5
add 666 5
render
modify 666
*/