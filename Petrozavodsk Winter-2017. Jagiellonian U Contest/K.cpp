#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define maxn 200005
using namespace std;
int T,n,m;
char s[maxn],str[maxn];
int Len[maxn];
vector< pair<string,int> > g[maxn];
int Ans[maxn];

const int bas1=31,bas2=37;
const int mod1=1000000007,mod2=998244353;
int xp1[maxn],xp2[maxn];

const int M=1000007;
struct HashTable
{
    int head[M];
    int v1[maxn],v2[maxn],val[maxn],nxt[maxn],p;
    void add(int u,int h1,int h2)
    {
        for(int i=head[u];i;i=nxt[i])
        {
            if(v1[i]==h1&&v2[i]==h2)
            {
                val[i]++;
                return;
            }
        }
        ++p;
        v1[p]=h1;v2[p]=h2;val[p]=1;nxt[p]=head[u];head[u]=p;
    }
    int get(int u,int h1,int h2)
    {
        for(int i=head[u];i;i=nxt[i])
        {
            if(h1==v1[i]&&h2==v2[i])return val[i];
        }
        return 0;
    }
}ht;

int add1(int h,int t,int L)
{
    h=(1ll*h*bas1+t)%mod1;
    return h;
}
int del1(int h,int t,int L)
{
    h=(h-1ll*t*xp1[L-1]%mod1+mod1)%mod1;
    return h;
}
int add2(int h,int t,int L)
{
    h=(1ll*h*bas2+t)%mod2;
    return h;
}
int del2(int h,int t,int L)
{
    h=(h-1ll*t*xp2[L-1]%mod2+mod2)%mod2;
    return h;
}
int used[maxn];
void solve(int L)
{
    int cnt=0;
    int h1=0,h2=0;
    for(int j=1;j<=L;++j)
    {
        h1=(1ll*h1*bas1+(s[j]-'a'+1))%mod1;
        h2=(1ll*h2*bas2+(s[j]-'a'+1))%mod2;
    }
    int B=19260817%M;
    used[++cnt]=(1ll*h1*B+h2)%M;
    ht.add((1ll*h1*B+h2)%M,h1,h2);
    //if(L==3)cerr<<h1<<" "<<h2<<endl;
    for(int i=L+1;i<=m;++i)
    {
        h1=del1(h1,s[i-L]-'a'+1,L);
        //if(L==3)cerr<<h1<<endl;
        h1=add1(h1,s[i]-'a'+1,L);
        h2=del2(h2,s[i-L]-'a'+1,L);
        h2=add2(h2,s[i]-'a'+1,L);
        used[++cnt]=(1ll*h1*B+h2)%M;
        ht.add((1ll*h1*B+h2)%M,h1,h2);
        //if(L==3)cerr<<h1<<" "<<h2<<endl;
    }
    //cerr<<L<<"!!!!!!!!!!!!!!!"<<endl;
    for(int i=0;i<g[L].size();++i)
    {
        string a=g[L][i].first;
        int id=g[L][i].second;
        int h1=0,h2=0;
        for(int j=1;j<=L;++j)
        {
            h1=(1ll*h1*bas1+(a[j]-'a'+1))%mod1;
            h2=(1ll*h2*bas2+(a[j]-'a'+1))%mod2;
        }
        Ans[id]+=ht.get((1ll*h1*B+h2)%M,h1,h2);
        for(int j=1;j<=L;++j)
        {
            for(int k='a';k<='z';++k)if(k!=a[j])
            {
                int t1,t2;
                t1=(h1-1ll*(a[j]-'a'+1)*xp1[L-j]%mod1+mod1)%mod1;
                t1=(t1+1ll*(k-'a'+1)*xp1[L-j]%mod1)%mod1;
                t2=(h2-1ll*(a[j]-'a'+1)*xp2[L-j]%mod2+mod2)%mod2;
                t2=(t2+1ll*(k-'a'+1)*xp2[L-j]%mod2)%mod2;
                Ans[id]+=ht.get((1ll*t1*B+t2)%M,t1,t2);
            }
        }
    }
    for(int i=1;i<=cnt;++i)ht.head[used[i]%M]=0;
    ht.p=0;
    //cerr<<L<<"!!!!!!!!!!!!!!!!!!!!!"<<endl;
}
int main()
{
    //freopen("K.in","r",stdin);
    scanf("%d",&T);
    xp1[0]=xp2[0]=1;
    for(int i=1;i<=200000;++i)xp1[i]=1ll*xp1[i-1]*bas1%mod1,xp2[i]=1ll*xp2[i-1]*bas2%mod2;
    while(T--)
    {
        scanf("%s",s+1);
        m=strlen(s+1);
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            Ans[i]=0;
            scanf("%s",str+1);
            Len[i]=strlen(str+1);
            string tmp;tmp.clear();
            tmp.push_back(' ');
            for(int j=1;j<=Len[i];++j)tmp.push_back(str[j]);
            g[Len[i]].push_back(make_pair(tmp,i));
        }
        sort(Len+1,Len+n+1);
        int d=unique(Len+1,Len+n+1)-Len-1;
        for(int i=1;i<=d;++i)
        {
            int L=Len[i];
            solve(L);
        }
        for(int i=1;i<=n;++i)printf("%d\n",Ans[i]);
        for(int i=1;i<=d;++i)g[Len[i]].clear();
    }
}
