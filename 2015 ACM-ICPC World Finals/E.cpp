#include<bits/stdc++.h>
#define maxn 4005
using namespace std;
int n;
struct Str
{
    char s[maxn];
    int len;
    Str()
    {
        memset(s,0,sizeof(s));
        len=0;
    }
    void read()
    {
        scanf("%s",s+1);
        len=strlen(s+1);
    }
}s[maxn],T;
bool operator < (Str A,Str B)
{
    return A.len<B.len;
}
int id(char c)
{
    if(c=='A')return 0;
    else if(c=='C')return 1;
    else return 2;
}
int nxt[maxn][maxn][3];
bool issub(int a,int b)
{
    int pos=0;
    for(int i=1;i<=s[a].len;++i)
    {
        if(!nxt[b][pos][id(s[a].s[i])])return 0;
        pos=nxt[b][pos][id(s[a].s[i])];
    }
    return 1;
}
vector<int> ansa,ansb;
bool used[maxn];
int main()
{
    scanf("%d",&n);
    T.read();
    for(int i=1;i<=n;++i)s[i].read();
    sort(s+1,s+n+1);
    s[n+1]=T;
    for(int i=1;i<=n+1;++i)
    {
        for(int k=0;k<3;++k)nxt[i][s[i].len+1][k]=0;
        for(int j=s[i].len;j>=0;--j)
        {
            for(int k=0;k<3;++k)nxt[i][j][k]=nxt[i][j+1][k];
            if(j<s[i].len)nxt[i][j][id(s[i].s[j+1])]=j+1;
        }
    }
    bool yes=1;
    int now=0;
    int tp=0;
    int x=0,xx,y=0,yy;
    for(int i=1;i<=n;++i)
    {
        if(tp==0)
        {
            if(!issub(x,i)&&!issub(y,i))
            {
                yes=0;break;
            }
            else if(!issub(x,i))
            {
                y=i;
                ansb.push_back(i);
            }
            else if(!issub(y,i))
            {
                x=i;
                ansa.push_back(i);
            }
            else
            {
                tp=1;
                y=i;
                xx=i;yy=y;
            }
        }
        else
        {
            if(issub(y,i))
            {
                y=i;
                xx=i;
            }
            else if(issub(x,i))
            {
                yy=i;
            }
            else
            {
                
            }
        }
    }
    if(ansa.size())
    {
        if(!issubseq(ansa[ansa.size()-1],n+1))yes=0;
    }
    if(ansb.size())
    {
        if(!issubseq(ansb[ansb.size()-1],n+1))yes=0;
    }
    if(ansa.size()+ansb.size()<n)yes=0;
    if(!yes)
    {
        puts("impossible");
    }
    else
    {
        printf("%d %d\n",ansa.size(),ansb.size());
        for(int x:ansa)printf("%s\n",s[x].s+1);
        for(int x:ansb)printf("%s\n",s[x].s+1);
    }
}