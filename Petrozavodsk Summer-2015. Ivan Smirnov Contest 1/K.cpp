#include<bits/stdc++.h>
#define MAXN 405
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<400> bs;
int n,m;
mt19937 wcy(time(NULL));
bs G[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        u--; v--;
        G[u].set(v); G[v].set(u);
    }
    //find K33
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            for(int k=j+1;k<n;k++)
            {
                bs tmp=G[i]&G[j]&G[k];
                if(tmp.count()>=3)
                {
                    vector<int> vv;
                    for(int l=0;l<n;l++) if(tmp.test(l)) vv.push_back(l);
                    puts("K33");
                    printf("%d %d %d\n",i+1,j+1,k+1);
                    printf("%d %d %d\n",vv[0]+1,vv[1]+1,vv[2]+1);
                    return 0;
                }
            }
    //random algorithm to find K5
    for(int round=0;round<200000;round++)
    {
        vector<int> perm; perm.clear();
        for(int i=0;i<n;i++) perm.push_back(i);
        random_shuffle(perm.begin(),perm.end());
        vector<int> cur;
        for(int i=0;i<n;i++)
        {
            bool f=true;
            for(int j=0;j<(int)cur.size();j++) if(!G[cur[j]].test(perm[i])) {f=false; break;}
            if(f) 
            {
                cur.push_back(perm[i]);
                if(cur.size()==5) break;
            }
        }
        if(cur.size()==5) 
        {
            puts("K5");
            for(auto x:cur) printf("%d ",x+1);
            return 0;
        }
    }
    puts("NO");
    return 0;
}