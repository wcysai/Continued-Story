#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,cnt[10];
string str;
int main()
{
    int ans=INF,id=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        memset(cnt,0,sizeof(cnt));
        int x;
        scanf("%d",&x);
        cin>>str;
        for(int j=0;j<(int)str.size();j++) cnt[str[j]-'0']++;
        if(cnt[0]>=1&&cnt[1]>=1&&cnt[2]>=2)
        {
            if(x<ans)
            {
                ans=x;
                id=i+1;
            }
        }
    }
    printf("%d\n",id);
    return 0;
}