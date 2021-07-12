#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
deque<int> v;
vector<int> modulos;
ll sum;
mt19937 wcy(time(NULL));
int tot=1000;
void initialize()
{
    tot--;
    printf("? %d\n",INF);
    fflush(stdout);
    v.push_back(INF);
    sum+=INF;
    int x;
    scanf("%d",&x);
    for(int i=1;1LL*i*i<=sum-x;i++)
    {
        if((sum-x)%i) continue;
        if(i>=2&&i<=INF) modulos.push_back(i);
        if(((sum-x)/i)>=2&&((sum-x)/i)<=INF&&1LL*i*i!=sum-x) modulos.push_back((sum-x)/i);
    }
    sum-=v[0];
    v.pop_front();
    sum+=x;
    v.push_back(x);
    sum-=v[0];
    v.pop_front();
    //printf("sz=%d\n",(int)modulos.size());
}
void ask(int val=-1)
{
    tot--;
    if(val==-1) val=wcy()%(INF+1);
    printf("? %d\n",val);
    fflush(stdout);
    sum+=val;
    v.push_back(val);
    int x;
    scanf("%d",&x);
    vector<int> tmp;
    for(auto mod:modulos) if(sum%mod==x) tmp.push_back(mod);
    swap(modulos,tmp);
    sum-=v[0];
    v.pop_front();
    sum+=x;
    v.push_back(x);
    sum-=v[0];
    v.pop_front();
    //printf("sz=%d\n",(int)modulos.size());
}
void answer(int x)
{
    printf("! %d\n",x);
    fflush(stdout);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int x;
        scanf("%d",&x);
        v.push_back(x);
        sum+=x;
    }
    initialize();
    for(int i=0;i<99;i++) ask();
    assert(modulos.size()>=1&&modulos.size()<=900);
    while(modulos.size()>1)
    {
        int x=modulos[0],y=modulos[1];
        int val;
        if(sum%x!=sum%y) val=0;
        else val=x;
        ask(val);
        assert(tot>0);
    }
    answer(modulos[0]);
    return 0;
}