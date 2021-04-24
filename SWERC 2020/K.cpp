#include<bits/stdc++.h>
#define maxn 1000005
typedef long long ll;
using namespace std;
int n;
char str[maxn];
int fa[maxn],cnt,last,rt,ch[maxn][26],pos[maxn];
ll sz[maxn],dis[maxn];
void init()
{
    cnt=0;
    rt=last=++cnt;
    memset(fa,0,sizeof(fa));
    memset(dis,0,sizeof(dis));
    memset(sz,0,sizeof(sz));
    memset(ch,0,sizeof(ch));
}
inline int newnode(int x){dis[++cnt]=x;return cnt;}
void add(int x,int id)
{
    int np=newnode(dis[last]+1),p=last;
    for(;p&&(!ch[p][x]);p=fa[p])ch[p][x]=np;
    if(!p)fa[np]=rt;
    else
    {
        int q=ch[p][x];
        if(dis[q]==dis[p]+1)fa[np]=q;
        else
        {
            int nq=newnode(dis[p]+1);
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            fa[nq]=fa[q];
            fa[q]=fa[np]=nq;
            for(;ch[p][x]==q;p=fa[p])ch[p][x]=nq;
        }
    }
    last=np;
    sz[last]=1;
    pos[last]=id;
}
int c[maxn],t[maxn];
void count()
{
    memset(c,0,sizeof(c));
    memset(t,0,sizeof(t));
    for(int i=1;i<=cnt;++i)c[dis[i]]++;
    for(int i=1;i<=cnt;++i)c[i]+=c[i-1];
    for(int i=cnt;i;--i)t[c[dis[i]]--]=i;
    for(int i=cnt;i;--i)
    {
        int x=t[i];
        sz[fa[x]]+=sz[x];
    }
    int len=n+1,anspos=0;
    for(int i=2;i<=cnt;++i)if(sz[i]==1)
    {
        if(dis[fa[i]]+1<len||(dis[fa[i]]+1==len&&anspos>pos[i]))
        {
            len=dis[fa[i]]+1;
            anspos=pos[i];
        }
    }
    for(int i=anspos-len+1;i<=anspos;++i)printf("%c",str[i]);
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    init();
    for(int i=1;i<=n;++i)add(str[i]-'A',i);
    count();
}