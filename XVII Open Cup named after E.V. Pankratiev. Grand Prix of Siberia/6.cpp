#include<bits/stdc++.h>
#define MAXN 100005
#define MAXB 17
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int b,m,tot;
int state[MAXN];
int trans[MAXN][MAXB];
map<P,int> mp;
int get_state(P p)
{
    if(mp.find(p)==mp.end()) mp[p]=tot++;
    return mp[p];
}
bool check(int l,int len)
{
    if(l==0||l+len-1>=m) return true;
    return false;
}
int main()
{
    scanf("%d%d",&b,&m);
    for(int i=0;i<m;i++)
    {
        int now=i,len=1,cnt=0;
        while(!check(now,len))
        {
            cnt++;
            now=now*b%m;
            len*=b;
        }
        state[i]=get_state(make_pair(cnt,now));
        //printf("i=%d state=%d\n",i,state[i]);
    }
    printf("%d %d\n",tot,0);
    for(int i=0;i<tot;i++) if(i==0) printf("G "); else printf("B ");
    puts("");
    for(int i=0;i<m;i++)
        for(int j=0;j<b;j++)
            trans[state[i]][j]=state[(i*b+j)%m];
    for(int i=0;i<tot;i++)
        for(int j=0;j<b;j++)
            printf("%d%c",trans[i][j],j==b-1?'\n':' ');
    return 0;
}