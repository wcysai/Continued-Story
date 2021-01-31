#include <bits/stdc++.h>
#define MAXN 1000005
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int k,cnt;
int secret;
mt19937 wcy(time(NULL));
bool gen(double prob)
{
    int res=100000000*prob;
    if(wcy()%1000000000<=res) return 1;
    else return 0;
}
int test(int k)
{
    cnt++;
    printf("test %d\n",k);
    fflush(stdout);
    int x;
    scanf("%d",&x);
    return x;
}
int get_test(int now)
{
    double prob=secret/10000000.0;
    for(int i=0;i<now;i++) if(gen(prob)) return 1;
    return 0;
}
void answer(int x)
{
    printf("estimate %d\n",x);
    fflush(stdout);
    exit(0);
}
int main()
{
    int now=-1;
    for(int k=1;k<=10000000;k*=2)
    {
        if(test(k))
        {
            now=k;
            break;
        }
    }
    int rem=50-cnt;
    int c=0;
    for(int i=0;i<rem;i++) if(test(now)) c++;
    double prob=1.0-(c/(double)rem);
    prob=powl(prob,1.0/now);
    int estimate=(10000000-10000000*prob);
    answer(estimate);
    return 0;
}   