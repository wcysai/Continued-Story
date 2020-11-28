#include<bits/stdc++.h>
#define MAXN 20005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int cur,n,m;
int curans,num;
bool updated[MAXN];
bool answered[MAXN];
void answer(int v)
{
    printf("$ %d\n",v);
    fflush(stdout);
}
string str;
bool queryss(int x,int y)
{
    num++;
    printf("s %d s %d\n",x+1,y+1);
    fflush(stdout);
    bool f;
    cin>>str;
    if(str[0]=='Y') f=true; else f=false;
    if(num==5&&!answered[cur]) {answer(curans); answered[cur]=true; num=0; cur++; if(cur==m) exit(0); }
    return f;
}
bool queryst(int x,int y)
{
    num++;
    printf("s %d t %d\n",x+1,y+1);
    fflush(stdout);
    bool f;
    cin>>str;
    if(str[0]=='Y') f=true; else f=false;
    if(num==5&&!answered[cur]) {answer(curans); answered[cur]=true; num=0; cur++; if(cur==m) exit(0); }
    return f;
}
vector<int> nxt(20002,0);
void build_nxt(int id)
{
    int j=id-1;
    while(j>0)
    {
        j=nxt[j];
        if(queryss(j,id-1))
        {
            nxt[id]=j+1;
            break;
        }
    }
    updated[id]=true;
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(updated,false,sizeof(updated));
    memset(answered,false,sizeof(answered));
    updated[1]=true;
    cur=0;
    int j=0;
    for(int i=0;i<m;i++)
    {
        if(i+1<=n&&!updated[i+1]) build_nxt(i+1);
        if(j<n&&queryst(j,i)) j++;
        else
        {
            while(j>0)
            {
                j=nxt[j];
                if(queryst(j,i)) {j++; break;}
            }
        }
        if(j==n) curans++;
        if(cur==i&&!answered[cur])
        {
            num=0;
            answered[cur]=true;
            cur++;
            answer(curans);
        }
    }
}