#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<500> bs;
int n,m,K;
string str[MAXN];
bs save[MAXN];
bs f[MAXN];
int l[MAXN],r[MAXN];
int main()
{
    scanf("%d%d%d",&n,&m,&K);
    for(int i=0;i<n;i++) 
    {
        cin>>str[i];
        for(int j=0;j<m;j++) if(str[i][j]=='1') save[i].set(j);
    }
    for(int i=0;i<m;i++)
        for(int j=i;j<m;j++)
        {
            bs tmp; tmp.reset();
            for(int k=i;k<=j;k++) tmp.set(k);
            for(int k=0;k<n;k++) f[k]=save[k]&tmp;
        }
}