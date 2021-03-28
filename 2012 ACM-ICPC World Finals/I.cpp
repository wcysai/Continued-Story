#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;
int r,c,m,n,cas;
set<int> R[maxn],C[maxn];
map<pair<int,int>,int> tp;
struct Line
{
    int x,y,xx,yy;
    Line(int x=0,int y=0,int xx=0,int yy=0):x(x),y(y),xx(xx),yy(yy){}
};
vector<Line> g;
//dir:0 right,1:down,2:left,3:up
bool go1()
{
    int x=1,y=0,dir=0;
    while(1)
    {
        if(dir==0)
        {
            set<int>::iterator it;
            it=R[x].lower_bound(y+1);
            int nxt=*it;
            g.push_back(Line(x,y+1,x,nxt-1));
            y=nxt;
            if(tp[make_pair(x,y)]==0)dir=3;
            else dir=1;
        }
        else if(dir==1)
        {
            set<int>::iterator it;
            it=C[y].lower_bound(x+1);
            int nxt=*it;
            g.push_back(Line(x+1,y,nxt-1,y));
            x=nxt;
            if(tp[make_pair(x,y)]==0)dir=2;
            else dir=0;
        }
        else if(dir==2)
        {
            set<int>::iterator it;
            it=R[x].lower_bound(y);
            --it;
            int nxt=*it;
            g.push_back(Line(x,nxt+1,x,y-1));
            y=nxt;
            if(tp[make_pair(x,y)]==0)dir=1;
            else dir=3;
        }
        else
        {
            set<int>::iterator it;
            it=C[y].lower_bound(x);
            --it;
            int nxt=*it;
            g.push_back(Line(nxt+1,y,x-1,y));
            x=nxt;
            if(tp[make_pair(x,y)]==0)dir=0;
            else dir=2;
        }
        //cerr<<"pos::"<<x<<" "<<y<<" "<<dir<<endl;
        if(x==r&&y==c+1)return 1;
        if(x==r+1||y==c+1||x==0||y==0)return 0;
    }
}
bool go2()
{
    int x=r,y=c+1,dir=2;
    while(1)
    {
        if(dir==0)
        {
            set<int>::iterator it;
            it=R[x].lower_bound(y+1);
            int nxt=*it;
            g.push_back(Line(x,y+1,x,nxt-1));
            y=nxt;
            if(tp[make_pair(x,y)]==0)dir=3;
            else dir=1;
        }
        else if(dir==1)
        {
            set<int>::iterator it;
            it=C[y].lower_bound(x+1);
            int nxt=*it;
            g.push_back(Line(x+1,y,nxt-1,y));
            x=nxt;
            if(tp[make_pair(x,y)]==0)dir=2;
            else dir=0;
        }
        else if(dir==2)
        {
            set<int>::iterator it;
            it=R[x].lower_bound(y);
            --it;
            int nxt=*it;
            g.push_back(Line(x,nxt+1,x,y-1));
            y=nxt;
            if(tp[make_pair(x,y)]==0)dir=1;
            else dir=3;
        }
        else
        {
            set<int>::iterator it;
            it=C[y].lower_bound(x);
            --it;
            int nxt=*it;
            g.push_back(Line(nxt+1,y,x-1,y));
            x=nxt;
            if(tp[make_pair(x,y)]==0)dir=0;
            else dir=2;
        }
        //cerr<<"pos::"<<x<<" "<<y<<" "<<dir<<endl;
        if(x==1&&y==0)return 1;
        if(x==r+1||y==c+1||x==0||y==0)return 0;
    }
}
typedef long long ll;
vector< pair<int,int> > rline[maxn],cline[maxn];
int sumv[maxn<<2];
void build(int rt,int l,int r)
{
    sumv[rt]=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);build(rt<<1|1,mid+1,r);
}
void update(int rt,int l,int r,int pos,int v)
{
    if(l==r)
    {
        sumv[rt]+=v;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)update(rt<<1,l,mid,pos,v);
    else update(rt<<1|1,mid+1,r,pos,v);
    sumv[rt]=sumv[rt<<1]+sumv[rt<<1|1];
}
int query(int rt,int l,int r,int ql,int qr)
{
    int ans=0;
    if(ql<=l&&r<=qr)return sumv[rt];
    int mid=(l+r)>>1;
    if(ql<=mid)ans+=query(rt<<1,l,mid,ql,qr);
    if(qr>mid)ans+=query(rt<<1|1,mid+1,r,ql,qr);
    return ans;
}
ll ans;
int ansx,ansy;
int main()
{
    while(~scanf("%d%d%d%d",&r,&c,&m,&n))
    {
        for(int i=1;i<=r+1;++i)R[i].clear(),rline[i].clear();
        for(int i=1;i<=c+1;++i)C[i].clear(),cline[i].clear();
        for(int i=1;i<=r;++i)R[i].insert(c+1),R[i].insert(0);
        for(int i=1;i<=c;++i)C[i].insert(r+1),C[i].insert(0);
        g.clear();tp.clear();
        ans=0;ansx=0;ansy=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            R[x].insert(y);
            C[y].insert(x);
            tp[make_pair(x,y)]=0;
        }
        for(int i=1;i<=n;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            R[x].insert(y);
            C[y].insert(x);
            tp[make_pair(x,y)]=1;
        }
        printf("Case %d: ",++cas);
        if(go1())
        {
            printf("0\n");
            continue;
        }
        go2();
        build(1,1,c);
        for(Line L:g)
        {
            //cerr<<L.x<<" "<<L.y<<" "<<L.xx<<" "<<L.yy<<endl;
            if(L.x==L.xx)
            {
                rline[L.x].push_back(make_pair(L.y,L.yy));
            }
            else
            {
                cline[L.x].push_back(make_pair(L.y,1));
                cline[L.xx].push_back(make_pair(L.y,-1));
            }
        }
        for(int i=1;i<=r;++i)
        {
            for(auto p:cline[i])
            {
                int pos=p.first,tp=p.second;
                if(tp==1)
                {
                    update(1,1,c,pos,1);
                }
            }
            for(auto p:rline[i])
            {
                int l=p.first,r=p.second;
                ans+=query(1,1,c,l,r);
            }
            if(ansx==0&&ans>0)
            {
                for(int j=1;j<=c;++j)if(query(1,1,c,j,j))
                {
                    ansx=i;ansy=j;
                    break;
                }
            }
            for(auto p:cline[i])
            {
                int pos=p.first,tp=p.second;
                if(tp==-1)
                {
                    update(1,1,c,pos,-1);
                }
            }
        }
        if(!ans)puts("impossible");
        else
        {
            printf("%lld %d %d\n",ans,ansx,ansy);
        }
    }
}