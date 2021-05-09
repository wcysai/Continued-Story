//team continued story
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int t,n,m;
string str[MAXN];
string ans[MAXN];
bool vis[MAXN][MAXN];
bool dfs(int x,int y,int dir,bool st=true)//0: from down 1: from left 2:from up 3:from right
{
    if(x<0||x>=n||y<0||y>=m) return false;
    if(vis[x][y]) return false;
    vis[x][y]=true;
    if(str[x][y]=='O'&&!st)
    {
        if(ans[x][y]=='v') return (dir==0);
        else if(ans[x][y]=='<') return (dir==1);
        else if(ans[x][y]=='>') return (dir==3);
        else return (dir==2);
    }
    if(str[x][y]=='*') return false;
    if(ans[x][y]=='v') return dfs(x+1,y,2,false);
    else if(ans[x][y]=='<') return dfs(x,y-1,3,false);
    else if(ans[x][y]=='^') return dfs(x-1,y,0,false);
    else if(ans[x][y]=='>') return dfs(x,y+1,1,false);
    else if(ans[x][y]=='q')
    {
        if(dir!=0&&dir!=1) return false;
        if(dir==0) return dfs(x,y-1,3,false);
        else return dfs(x+1,y,2,false);
    }
    else if(ans[x][y]=='d')
    {
        if(dir!=1&&dir!=2) return false;
        if(dir==1) return dfs(x-1,y,0,false);
        else return dfs(x,y-1,3,false);
    }
    else if(ans[x][y]=='b')
    {
        if(dir!=2&&dir!=3) return false;
        if(dir==2) return dfs(x,y+1,1,false);
        else return dfs(x-1,y,0,false);
    }
    else if(ans[x][y]=='p')
    {
        if(dir!=3&&dir!=0) return false;
        if(dir==3) return dfs(x+1,y,2,false);
        else return dfs(x,y+1,1,false);
    }
    else if(ans[x][y]=='l')
    {
        if(dir!=0&&dir!=2) return false;
        if(dir==0) return dfs(x-1,y,0,false);
        else return dfs(x+1,y,2,false);
    }
    else if(ans[x][y]=='-')
    {
        if(dir!=1&&dir!=3) return false;
        if(dir==1) return dfs(x,y+1,1,false);
        else return dfs(x,y-1,3,false);
    }
    else return false;
}
bool check()
{
    memset(vis,false,sizeof(vis));
    int x=-1,y=-1;
    for(int i=0;i<n;i++)
    {
        if(x!=-1) break;
        for(int j=0;j<m;j++)
            if(str[i][j]=='O') {x=i; y=j; break;}
    }
    if(!dfs(x,y,0)) return false;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(str[i][j]!='*'&&!vis[i][j]) return false;
    return true;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++) {cin>>str[i]; ans[i]=str[i];}
        bool f=false;
        for(int x=0;x<4;x++)
            for(int y=0;y<4;y++)
            {
                if(f) break;
                bool used=false;
                bool flag=true;
                for(int i=n-1;i>=0;i--)
                    for(int j=0;j<m;j++)
                    {
                        int dstate,lstate;
                        if(i==n-1) dstate=0;
                        else if(ans[i+1][j]=='l'||ans[i+1][j]=='d'||ans[i+1][j]=='b'||ans[i+1][j]=='^') dstate=1; else dstate=0;
                        if(j==0) lstate=0;
                        else if(ans[i][j-1]=='-'||ans[i][j-1]=='b'||ans[i][j-1]=='p'||ans[i][j-1]=='>') lstate=1; else lstate=0;
                        if(str[i][j]=='*')
                        {
                            if(dstate||lstate) flag=false;
                            ans[i][j]='*';
                        }
                        else if(str[i][j]=='l')
                        {
                            if(dstate&&lstate) flag=false;
                            else if(!dstate&&!lstate) flag=false;
                            else if(dstate) ans[i][j]='l'; else ans[i][j]='-';
                        }
                        else if(str[i][j]=='q')
                        {
                            if(dstate&&lstate) ans[i][j]='q';
                            else if(!dstate&&lstate) ans[i][j]='d';
                            else if(dstate&&!lstate) ans[i][j]='p';
                            else ans[i][j]='b';
                        }
                        else
                        {
                            if(!used)
                            {
                                if(x==0) ans[i][j]='v'; else if(x==1) ans[i][j]='<'; else if(x==2) ans[i][j]='^'; else ans[i][j]='>';
                                used=true;
                            }
                            else
                            {
                                if(y==0) ans[i][j]='v'; else if(y==1) ans[i][j]='<'; else if(y==2) ans[i][j]='^'; else ans[i][j]='>';
                            }
                        }
                    }
                    if(flag)
                    {
                        if(check())
                        {
                            puts("YES");
                            for(int i=0;i<n;i++) cout<<ans[i]<<endl;
                            f=true;
                            break;
                        }
                    }
            }
            if(!f) puts("NO");
    }
    return 0;
}

