#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
vector<int> G[MAXN];
string str[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
int tot[2];
int trie[2][MAXN][26],fa[2][MAXN],c[2][MAXN];
vector<int> gr[MAXN];
int deg[MAXN],a[MAXN],save[MAXN],r[MAXN];
bool cmp(int x,int y)
{
    return deg[x]<deg[y];
}
void insert(int id,string s,int rt)
{
    for(int i=0;i<(int)s.size();i++)
    {
        int x=s[i]-'a';
        if(trie[id][rt][x]==-1) 
        {
            trie[id][rt][x]=++tot[id];
            fa[id][tot[id]]=rt;
            c[id][tot[id]]=x;
        }
        rt=trie[id][rt][x];
    }
}
string construct_string(int id,int x)
{
    string s="";
    while(x!=0)
    {
        s+='a'+c[id][x];
        x=fa[id][x];
    }
    if(!id) reverse(s.begin(),s.end());
    return s;
}
vector<int> pre,suf;
int main()
{
    memset(trie,-1,sizeof(trie));
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        tot[0]=tot[1]=0;
        for(int i=1;i<=n;i++)
        {
            cin>>str[i];
            insert(0,str[i],0);
            reverse(str[i].begin(),str[i].end());
            insert(1,str[i],0);
            reverse(str[i].begin(),str[i].end());
        }
        int N=tot[0]+tot[1];
        for(int i=1;i<=N;i++) a[i]=i,gr[i].clear(),G[i].clear();
        for(int i=1;i<=n;i++)
        {
            pre.clear(); suf.clear();
            int m=(int)str[i].size();
            int rt=0;
            for(int j=0;j<m-1;j++)
            {
                rt=trie[0][rt][str[i][j]-'a'];
                pre.push_back(rt);
            }
            reverse(str[i].begin(),str[i].end());
            rt=0;
            for(int j=0;j<m-1;j++)
            {
                rt=trie[1][rt][str[i][j]-'a'];
                suf.push_back(rt);
            }
            for(int j=0;j<m-1;j++) add_edge(pre[j],tot[0]+suf[m-2-j]);
        }
        for(int i=1;i<=N;i++) deg[i]=(int)G[i].size();
        sort(a+1,a+N+1,cmp);
        for(int i=1;i<=N;i++) r[a[i]]=i;
        for(int i=1;i<=N;i++)
            for(auto to:G[i]) 
                if(r[to]>r[i]) gr[i].push_back(to); 
        int x=-1,y=-1,z=-1,w=-1;
        for(int i=1;i<=N;i++)
        {
            if(x!=-1) break;
            for(auto u:G[i])
            {
                for(auto to:gr[u])
                {
                    if(r[to]>r[i]) 
                    {
                        if(save[to])
                        {
                            x=i; y=to; z=u; w=save[to]; break;
                        }
                        save[to]=u;
                    }
                }
            }
            for(auto u:G[i])
                for(auto to:gr[u])
                    if(r[to]>r[i]) save[to]=0;
        }
        if(x==-1) puts("NO"); 
        else 
        {
            puts("YES");
            if(x>tot[0]) {swap(x,z); swap(y,w);}
            string xx=construct_string(0,x);
            string yy=construct_string(0,y);
            string zz=construct_string(1,z-tot[0]);
            string ww=construct_string(1,w-tot[0]);
            cout<<xx<<zz<<' '<<yy<<ww<<endl;
            cout<<yy<<zz<<' '<<xx<<ww<<endl;
        }
        for(int i=0;i<2;i++)
            for(int j=0;j<=tot[i];j++)
                for(int k=0;k<26;k++)
                    trie[i][j][k]=-1;
    }
}