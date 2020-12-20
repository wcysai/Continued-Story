#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<1050> bs;
typedef bitset<2042> bsm;
int n,m,a[MAXN];
//public key
bsm key[MAXN];
bs bas[MAXN];
string str;
string s;
string t;
bs b;
bs ans;
vector<int> save;
vector<int> pos;
void gauss_jordan()
{
    ans.reset();
    int pt=0;
    for(int i=0;i<m-n;i++)
    {
        int pivot=-1;
        for(int j=pt;j<n;j++) if(bas[j].test(i)) {pivot=j; break;}
        if(pivot==-1) continue;
        swap(bas[pt],bas[pivot]); 
        int tmp=b[pt];
        b[pt]=b[pivot];
        b[pivot]=tmp;
        pos.push_back(i);
        for(int j=pt+1;j<n;j++)
        {
            if(bas[j].test(i))
            {
                bas[j]^=bas[pt];
                if(b.test(pt)) b.flip(j);
            }
        }
        pt++;
    }
    for(int i=0;i<n;i++)
    {
        bool empty=true;
        for(int j=0;j<m-n;j++) if(bas[i].test(j)) empty=false;
        if(empty&&b[i])
        {
            puts("no solution");
            assert(0);
        }
    }
    for(int i=pt-1;i>=0;i--)
    {
        int x=pos[i],v=b[i];
        for(int j=x+1;j<m-n;j++) if(bas[i].test(j)&&ans.test(j)) v^=1;
        if(v) ans.set(x);
    }
}
mt19937 wcy(19260818);
int main()
{
    cin>>str;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(wcy()&1) key[i].set(j);
        }
    }
    if(str=="Bob")
    {
        cin>>t;
        bsm res; res.reset();
        for(int i=0;i<m;i++) if(t[i]=='1') res.set(i);
        for(int i=0;i<n;i++)
            if((res&key[i]).count()&1) printf("1"); else printf("0");
    }
    else
    {
        cin>>s;
        cin>>t;
        b.reset();
        int cnt=0;
        for(int j=0;j<n;j++) bas[j].reset();
        for(int i=0;i<n;i++) if(s[i]=='1') b.set(i);
        for(int i=0;i<m;i++) 
        {
            if(t[i]=='?') 
            {
                save.push_back(i);
                for(int j=0;j<n;j++) if(key[j].test(i)) bas[j].set(cnt);
                cnt++; 
            }
            else if(t[i]=='1')
            {
                for(int j=0;j<n;j++) if(key[j].test(i)) b.flip(j);
            }
        }
        /*
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m-n;j++) if(bas[i].test(j)) printf("1"); else printf("0");
            puts("");
        }
        for(int i=0;i<n;i++) if(b.test(i)) printf("1"); else printf("0");
        puts("");
        */
        gauss_jordan();
        for(int i=0;i<m-n;i++) t[save[i]]='0'+(ans.test(i)?1:0);
        cout<<t<<endl;
    }
    return 0;
}