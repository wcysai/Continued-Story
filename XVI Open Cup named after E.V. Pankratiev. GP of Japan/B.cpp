#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,x[MAXN],y[MAXN];
char ch[MAXN][2];
int dir[MAXN];
int nxt[MAXN][4];
int tmp[MAXN][4];
vector<int> disx,disy;
vector<P> save[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d%s",&x[i],&y[i],ch[i]);
        if(ch[i][0]=='^') dir[i]=0;
        else if(ch[i][0]=='v') dir[i]=1;
        else if(ch[i][0]=='<') dir[i]=2;
        else dir[i]=3;
        disx.push_back(x[i]); disy.push_back(y[i]);
    }
    sort(disx.begin(),disx.end());
    disx.erase(unique(disx.begin(),disx.end()),disx.end());
    sort(disy.begin(),disy.end());
    disy.erase(unique(disy.begin(),disy.end()),disy.end());
    for(int i=1;i<=n;i++)
    {
        x[i]=lower_bound(disx.begin(),disx.end(),x[i])-disx.begin()+1;
        y[i]=lower_bound(disy.begin(),disy.end(),y[i])-disy.begin()+1;
    }
    for(int i=1;i<=n;i++) save[x[i]].push_back(P(y[i],i));
    for(int i=1;i<=(int)disx.size();i++)
    {
        if(save[i].size())
        {
            sort(save[i].begin(),save[i].end());
            for(int j=0;j<(int)save[i].size()-1;j++) nxt[save[i][j].S][1]=save[i][j+1].S;
            for(int j=1;j<(int)save[i].size();j++) nxt[save[i][j].S][0]=save[i][j-1].S;
        }
    }
    for(int i=1;i<=(int)disx.size();i++) save[i].clear();
    for(int i=1;i<=n;i++) save[y[i]].push_back(P(x[i],i));
    for(int i=1;i<=(int)disy.size();i++)
    {
        if(save[i].size())
        {
            sort(save[i].begin(),save[i].end());
            for(int j=0;j<(int)save[i].size()-1;j++) nxt[save[i][j].S][3]=save[i][j+1].S;
            for(int j=1;j<(int)save[i].size();j++) nxt[save[i][j].S][2]=save[i][j-1].S;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) 
            for(int k=0;k<4;k++)
                tmp[j][k]=nxt[j][k];
        int cnt=1,cur=i;
        while(tmp[cur][dir[cur]])
        {
            if(tmp[cur][0]) tmp[tmp[cur][0]][1]=tmp[cur][1];
            if(tmp[cur][1]) tmp[tmp[cur][1]][0]=tmp[cur][0];
            if(tmp[cur][2]) tmp[tmp[cur][2]][3]=tmp[cur][3];
            if(tmp[cur][3]) tmp[tmp[cur][3]][2]=tmp[cur][2];
            cur=tmp[cur][dir[cur]];
            cnt++;
        }
        ans=max(ans,cnt);
    }
    printf("%d\n",ans);
    return 0;
}