#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef unsigned long long ll;
typedef pair<int,int> P;
int tot;
string s,t;
string cur;
ll ans;
ll dp[2][20][2][2][(1<<16)];
ll cnt[2][2][17][(1<<16)];
ll fact[MAXN];
ll pw[2][20];
string str;
int type;
int get_val(char ch)
{
    if(ch>='0'&&ch<='9') return ch-'0';
    return ch-'a'+10;
}
bool check(string &str)
{
    set<int> s;
    for(int i=0;i<(int)str.size();i++) s.insert(str[i]);
    return s.size()==str.size();
}
ll solve(int base,int rem,int less,int zero,int mask)
{
    //printf("base=%d rem=%d less=%d zero=%d mask=%d\n",base,rem,less,zero,mask);
    if(rem==0) {return zero?0:1;}
    if(less&&dp[base][rem][less][zero][mask]!=-1) return dp[base][rem][less][zero][mask]; 
    int limit=(less?(base==0?9:15):get_val(cur[(int)cur.size()-rem]));
    ll ret=0;
    for(int i=0;i<=limit;i++)
    {
        if(mask&(1<<i)) continue;
        int nmask;
        if(zero&&i==0) nmask=mask; else nmask=mask^(1<<i); 
        ret+=solve(base,rem-1,less|(i<limit),zero&(i==0),nmask);
    }
    return dp[base][rem][less][zero][mask]=ret;
}
ll solve_cnt(int base,int zero,int rem,int mask)
{
    if(cnt[base][zero][rem][mask]!=-1) return cnt[base][zero][rem][mask];
    if(rem==0) return 1;
    ll res=0;
    int limit=(base==0?9:15);
    for(int i=0;i<=limit;i++)
    {
        if(!(mask&(1<<i))) continue;
        int nmask;
        if(zero&&i==0) nmask=mask; else nmask=mask^(1<<i); 
        res+=solve_cnt(base,zero&(i==0),rem-1,nmask);
    }
    return cnt[base][zero][rem][mask]=res;
}
ll find_num(int base,int zero,int rem,int mask,ll res)
{
    assert(res>=1&&res<=solve_cnt(base,zero,rem,mask));
    if(rem==0) return 0;
    int limit=(base==0?9:15);
    for(int i=0;i<=limit;i++)
    {
        if(!(mask&(1<<i))) continue;
        int nmask;
        if(zero&&i==0) nmask=mask; else nmask=mask^(1<<i); 
        if(res<=solve_cnt(base,zero&(i==0),rem-1,nmask)) return 1LL*i*pw[base][rem-1]+find_num(base,zero&(i==0),rem-1,nmask,res);
        else res-=solve_cnt(base,zero&(i==0),rem-1,nmask);
    }
    assert(0); //should not reach here
    return 0;
}
ll convert_to_num(string str,int base)
{
    ll res=0;
    for(int i=0;i<(int)str.size();i++)
    {
        if(base==0) res=10LL*res+get_val(str[i]);
        else res=16LL*res+get_val(str[i]);
    }
    return res;
}
int main()
{
    fact[0]=1;
    for(int i=1;i<=16;i++) fact[i]=1LL*fact[i-1]*i;
    pw[0][0]=pw[1][0]=1;
    for(int i=1;i<=19;i++) pw[0][i]=10LL*pw[0][i-1];
    for(int i=1;i<=19;i++) pw[1][i]=16LL*pw[1][i-1];
    memset(dp,-1,sizeof(dp));
    memset(cnt,-1,sizeof(cnt));
    scanf("%d",&tot);
    while(tot--)
    {
        cin>>str;
        int base=(str[0]=='d'?0:1);
        scanf("%d",&type);
        if(type==0)
        {
            cin>>s; cin>>t;
            ll ans=0;
            cur=t; ans+=solve(base,(int)cur.size(),0,1,0);
            cur=s; ans-=solve(base,(int)cur.size(),0,1,0);
            if(check(cur)) ans++;
            if(str[0]=='d') printf("%llu\n",ans); else printf("%llx\n",ans);
        }
        else
        {
            cin>>s;
            ll num=convert_to_num(s,base);
            if(base==0)
            {
                if(num>solve_cnt(0,1,10,(1<<10)-1))
                {
                    puts("-");
                    continue;
                }
                printf("%llu\n",find_num(0,1,10,(1<<10)-1,num));
            }
            else
            {
                if(num>solve_cnt(1,1,16,(1<<16)-1))
                {
                    puts("-");
                    continue;
                }
                printf("%llx\n",find_num(1,1,16,(1<<16)-1,num));
            }
        }
    }
    return 0;
}