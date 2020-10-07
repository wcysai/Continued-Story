#include<bits/stdc++.h>
#define MAXN 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 dsakdso
#define y1 reokoa
#define x2 dakoda
#define y2 dfasok
#define x3 dfsakodas
#define y3 fasdosla
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,tot;
int ans[(1<<19)];
int dx[8]={-1,-1,-1,0,0,1,1,1};
int dy[8]={-1,0,1,-1,1,-1,0,1};
int cnt[(1<<19)];
char mp[10][10];
//encoded as white king/white rook/black king
//op 0: white 1: black
int encode_state(int op,int x1,int y1,int x2,int y2,int x3,int y3)
{
    int state=y3+(x3<<3)+(y2<<6)+(x2<<9)+(y1<<12)+(x1<<15)+(op<<18);
    return y3+(x3<<3)+(y2<<6)+(x2<<9)+(y1<<12)+(x1<<15)+(op<<18);
}
bool is_valid(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return (!(x1==x2&&y1==y2))&&(!(x1==x3&&y1==y3))&&(!(x2==x3&&y2==y3));
}
bool in_a_line(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return (x1==x2&&x1==x3&&((y2<y1&&y1<y3)||(y2>y1&&y1>y3)))||(y1==y2&&y1==y3&&((x2<x1&&x1<x3)||(x2>x1&&x1>x3)));
}
bool king_adj(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return max(x1-x3,x3-x1)<=1&&max(y1-y3,y3-y1)<=1;
}
bool black_king_under_attack(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return king_adj(x1,y1,x2,y2,x3,y3)||((x2==x3||y2==y3)&&(!in_a_line(x1,y1,x2,y2,x3,y3)));
}
bool white_king_under_attack(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return king_adj(x1,y1,x2,y2,x3,y3);
}
bool rook_under_protection(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return max(x1-x2,x2-x1)<=1&&max(y1-y2,y2-y1)<=1;
}
bool rook_under_attack(int x1,int y1,int x2,int y2,int x3,int y3)
{
    if(rook_under_protection(x1,y1,x2,y2,x3,y3)) return false;
    return max(x2-x3,x3-x2)<=1&&max(y2-y3,y3-y2)<=1;
}
bool is_checkmate(int x1,int y1,int x2,int y2,int x3,int y3)
{
    if(white_king_under_attack(x1,y1,x2,y2,x3,y3)) return false;
    if(!black_king_under_attack(x1,y1,x2,y2,x3,y3)) return false;
    for(int i=0;i<8;i++)
    {
        int nx=x3+dx[i],ny=y3+dy[i];
        if(nx<0||nx>=8||ny<0||ny>=8) continue;
        if(!black_king_under_attack(x1,y1,x2,y2,nx,ny)) return false;
    }
    return true;
}
bool is_stalemate(int x1,int y1,int x2,int y2,int x3,int y3)
{
    if(white_king_under_attack(x1,y1,x2,y2,x3,y3)) return false;
    if(black_king_under_attack(x1,y1,x2,y2,x3,y3)) return false;
    for(int i=0;i<8;i++)
    {
        int nx=x3+dx[i],ny=y3+dy[i];
        if(nx<0||nx>=8||ny<0||ny>=8) continue;
        if(!black_king_under_attack(x1,y1,x2,y2,nx,ny)) return false;
    }
    return true;
}
int get_id()
{
    int x1=-1,y1=-1,x2=-1,y2=-1,x3=-1,y3=-1;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(mp[i][j]=='W') {x1=i; y1=j;}
            if(mp[i][j]=='R') {x2=i; y2=j;}
            if(mp[i][j]=='B') {x3=i; y3=j;}
        }
    return encode_state(0,x1,y1,x2,y2,x3,y3);
}
vector<int> G[(1<<19)],rG[(1<<19)];
void add_edge(int u,int v)
{
    ++tot;
    G[u].push_back(v);
    rG[v].push_back(u);
}
void print_state(int state)
{
    int y3=state&7;
    int x3=(state>>3)&7;
    int y2=(state>>6)&7;
    int x2=(state>>9)&7;
    int y1=(state>>12)&7;
    int x1=(state>>15)&7;
    int op=(state>>18)&1;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(i==x1&&j==y1) printf("W");
            else if(i==x2&&j==y2) printf("R");
            else if(i==x3&&j==y3) printf("B");
            else printf(".");
        }
        puts("");
    }
    puts("");
}
int main()
{
    for(int i=0;i<(1<<19);i++) ans[i]=-1;
    queue<int> que;
    for(int op=0;op<2;op++)
        for(int x1=0;x1<8;x1++)
            for(int y1=0;y1<8;y1++)
                for(int x2=0;x2<8;x2++)
                    for(int y2=0;y2<8;y2++)
                        for(int x3=0;x3<8;x3++)
                            for(int y3=0;y3<8;y3++)
                            {
                                if(!is_valid(x1,y1,x2,y2,x3,y3)) continue;
                                int id=encode_state(op,x1,y1,x2,y2,x3,y3);
                                if(op==1)
                                {
                                    if(white_king_under_attack(x1,y1,x2,y2,x3,y3)) continue;
                                    if(rook_under_attack(x1,y1,x2,y2,x3,y3)) continue;
                                    for(int i=0;i<8;i++)
                                    {
                                        int nx=x3+dx[i],ny=y3+dy[i];
                                        if(nx<0||nx>=8||ny<0||ny>=8) continue;
                                        if(!is_valid(x1,y1,x2,y2,nx,ny)) continue;
                                        if(black_king_under_attack(x1,y1,x2,y2,nx,ny)) continue;
                                        add_edge(id,encode_state(0,x1,y1,x2,y2,nx,ny));
                                        cnt[id]++;
                                    }
                                    if(is_checkmate(x1,y1,x2,y2,x3,y3))
                                    {
                                        ans[id]=0;
                                        que.push(id);
                                    }
                                }
                                else
                                {
                                    if(black_king_under_attack(x1,y1,x2,y2,x3,y3)) continue;
                					for(int i=0;i<8;i++)
                                    {
                                        int nx=x1+dx[i],ny=y1+dy[i];
                                        if(nx<0||nx>=8||ny<0||ny>=8) continue;
                                        if(!is_valid(nx,ny,x2,y2,x3,y3)) continue;
                                        if(rook_under_attack(nx,ny,x2,y2,x3,y3)) continue;
                                        if(white_king_under_attack(nx,ny,x2,y2,x3,y3)) continue;
                                        if(is_stalemate(nx,ny,x2,y2,x3,y3)) continue;
                                        add_edge(id,encode_state(1,nx,ny,x2,y2,x3,y3));
                                    }
                                    for(int i=1;i<=x2;i++)
                                    {
                                        if(!is_valid(x1,y1,x2-i,y2,x3,y3)) break;
                                        if(rook_under_attack(x1,y1,x2-i,y2,x3,y3)) continue;
                                        if(is_stalemate(x1,y1,x2-i,y2,x3,y3)) continue;
                                        add_edge(id,encode_state(1,x1,y1,x2-i,y2,x3,y3));
                                    }
                                    for(int i=1;i<8-x2;i++)
                                    {
                                        if(!is_valid(x1,y1,x2+i,y2,x3,y3)) break;
                                        if(rook_under_attack(x1,y1,x2+i,y2,x3,y3)) continue;
                                        if(is_stalemate(x1,y1,x2+i,y2,x3,y3)) continue;
                                        add_edge(id,encode_state(1,x1,y1,x2+i,y2,x3,y3));
                                    }
                                    for(int i=1;i<=y2;i++)
                                    {
                                        if(!is_valid(x1,y1,x2,y2-i,x3,y3)) break;
                                        if(rook_under_attack(x1,y1,x2,y2-i,x3,y3)) continue;
                                        if(is_stalemate(x1,y1,x2,y2-i,x3,y3)) continue;
                                        add_edge(id,encode_state(1,x1,y1,x2,y2-i,x3,y3));
                                    }
                                    for(int i=1;i<8-y2;i++)
                                    {
                                        if(!is_valid(x1,y1,x2,y2+i,x3,y3)) break;
                                        if(rook_under_attack(x1,y1,x2,y2+i,x3,y3)) continue;
                                        if(is_stalemate(x1,y1,x2,y2+i,x3,y3)) continue;
                                        add_edge(id,encode_state(1,x1,y1,x2,y2+i,x3,y3));
                                    }
                                }
                            }
    while(que.size())
    {
        int state=que.front(); que.pop();
        if((state>>18)&1)
        {
            for(auto to:rG[state])
            {
                if(ans[to]==-1)
                {
                    ans[to]=ans[state]+1;
                    que.push(to);
                }
            }
        }
        else
        {
            for(auto to:rG[state])
            {
                cnt[to]--;
                if(cnt[to]==0&&ans[to]==-1)
                {
                    ans[to]=ans[state];
                    que.push(to);
                }
            }
        }
    }
    scanf("%d",&T);
    while(T--)
    {
        for(int i=0;i<8;i++) scanf("%s",mp[i]);
        int id=get_id();
        assert(ans[id]!=-1);
        printf("%d\n",ans[id]);
    }
    return 0;
}
