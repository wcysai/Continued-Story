#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 1000005
#define MAXT 1000000001
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,tot;
bool has[MAXM];
int ans[MAXM],lson[MAXM],rson[MAXM];;
map<pair<P,int>,int> mp;
vector<int> v;
int cnt=0;
int compare(int a,int b,int w)
{
    if(mp.find(make_pair(P(a,b),w))!=mp.end()) return mp[make_pair(P(a,b),w)];
    if(mp.find(make_pair(P(b,a),w))!=mp.end()) return 2-mp[make_pair(P(b,a),w)];
    printf("? %d %d %d\n",a,b,w);
    fflush(stdout);
    string str;
    cin>>str;
    int res;
    if(str=="FIRST") res=0;
    else if(str=="EQUAL") res=1;
    else res=2;
    mp[make_pair(P(a,b),w)]=res;
    return res;
}
void prepare()
{
    printf("!\n");
    fflush(stdout);
}
void answer(int x)
{
    printf("! %d\n",x);
    fflush(stdout);
}
void insert(int &k,int l,int r,int x,int y,int id)
{
    if(!k) k=++tot;
    if(l>y||x>r) return;
    if(l>=x&&r<=y)
    {
        if(!has[k])
        {
            has[k]=true;
            ans[k]=id;
            return;
        }
        if(l==r)
        {
            int res=compare(ans[k],id,l);
            if(res>=1) ans[k]=id;
            return; 
        }
        int mid=(l+r)/2;
        int lans=compare(ans[k],id,l),mans=compare(ans[k],id,mid);
        if(lans<=1&&mans<=1) 
        {
            insert(rson[k],mid+1,r,x,y,id);
        }
        else if(lans>=1&&mans>=1)
        {
            swap(ans[k],id);
            insert(rson[k],mid+1,r,x,y,id);
        }
        else if(lans>=1&&mans<=1)
        {
            insert(lson[k],l,mid,x,y,id);
        }
        else if(lans<=1&&mans>=1)
        {
            swap(ans[k],id);
            insert(lson[k],l,mid,x,y,id);
        }
        return;
    }
    int mid=(l+r)/2;
    insert(lson[k],l,mid,x,y,id); insert(rson[k],mid+1,r,x,y,id);
}
void query(int k,int l,int r,int x)
{
    if(!k) return;
    if(has[k]) v.push_back(ans[k]);
    if(l==r) return;
    int mid=(l+r)/2;
    if(x<=mid) query(lson[k],l,mid,x);
    else query(rson[k],mid+1,r,x);
}
int read_query()
{
    string str;
    cin>>str;
    if(str=="FINISH") exit(0);
    int x;
    scanf("%d",&x);
    return x;
}
int perm[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<=n-1;i++) perm[i]=i;
    random_shuffle(perm,perm+n);
    int root;
    for(int i=0;i<=n-1;i++) insert(root,1,100000,1,100000,perm[i]);
    prepare();
    int x;
    cnt=0;
    do
    {
        x=read_query();
        v.clear();
        query(root,1,100000,x);
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        int cur=v[0];
        for(int i=1;i<(int)v.size();i++)
        {
            if(compare(v[i],cur,x)<=1)
                cur=v[i];
        }
        answer(cur);
    } while (true);
    return 0;
}
