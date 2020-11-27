#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int R;
const double ratio=0.618;
string str;
bool valid[MAXN];
map<int,int> mp;
int submit_solution(int x)
{
    if(mp.find(x)!=mp.end()) return mp[x];
    printf("%d\n",x);
    fflush(stdout);
    cin>>str;
    if(str=="AC") exit(0);
    int y;
    scanf("%d",&y);
    mp[x]=y;
    return y;
}
vector<int> vec;
void build_vec()
{
    vec.clear();
    for(int i=1;i<=R;i++) if(valid[i]) vec.push_back(i);
}
int main()
{
    scanf("%d",&R);
    int l=1,r=R;
    mp[0]=1; mp[R+1]=2;
    for(int i=1;i<=R;i++) valid[i]=true;
    build_vec();
    while(vec.size()>1)
    {
        int sz=(int)vec.size();
        int lb=sz/3,rb=sz*2/3;
        int x=submit_solution(vec[lb]),y=submit_solution(vec[rb]);
        valid[vec[lb]]=valid[vec[rb]]=false;
        if(x==y) {for(int i=vec[lb];i<=vec[rb];i++) valid[i]=false;}
        else if(x<y) {for(int i=1;i<=vec[lb];i++) valid[i]=false;}
        else for(int i=vec[rb];i<=R;i++) valid[i]=false;
        build_vec();
    }
    assert(vec.size()==1);
    printf("%d\n",(int)vec[0]);
    return 0;
}