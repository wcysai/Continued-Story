#include<bits/stdc++.h>
#define MAXN 35
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,M,K;
int l[MAXN];
int lw[(1<<16)],rw[(1<<16)];
unsigned mas[MAXN];
mt19937 wcy(time(NULL));
bool evaluate_and(int round,unsigned mask);
bool gen()
{
    return wcy()&1;
}
bool win(unsigned mask)
{
    return lw[(mask)&((1<<16)-1)]+rw[(mask>>16)]>=K;
}
bool evaluate_or(int round,unsigned mask)
{
    bool tmp=gen();
    return evaluate_and(round,mask^(tmp?0:mas[2*round-1]))||evaluate_and(round,mask^(tmp?mas[2*round-1]:0));
}
bool evaluate_and(int round,unsigned mask)
{
    if(round==(N-1)/2)
    {
        return win(mask)&&win(mask^mas[2*round])&&win(mask^mas[2*round+1])&&win(mask^mas[2*round]^mas[2*round+1]);
    }
    bool tmp=gen();
    return evaluate_or(round+1,mask^(tmp?0:mas[2*round]))&&evaluate_or(round+1,mask^(tmp?mas[2*round]:0));
}
string str;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&N,&M,&K);
        for(int i=1;i<=32;i++) l[i]=0;
        for(int i=1;i<=M;i++) scanf("%d",&l[i]);
        for(int i=0;i<(1<<16);i++) lw[i]=rw[i]=0;
        for(int i=0;i<(1<<16);i++)
            for(int j=0;j<16;j++)
                if(i&(1<<j)) lw[i]+=l[j+1];
        for(int i=0;i<(1<<16);i++)
            for(int j=0;j<16;j++)
                if(i&(1<<j)) rw[i]+=l[16+j+1];
        for(int i=1;i<=N;i++) mas[i]=0;
        for(int i=1;i<=N;i++)
        {
            cin>>str;
            for(int j=0;j<M;j++) if(str[j]=='1') mas[i]+=(1u<<j);
        }
        if(evaluate_or(1,0)) puts("Roland"); else puts("Patrick");
    }
    return 0;
}