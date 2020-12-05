#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n;
string str;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        cin>>str;
        n=(int)str.size();
        if(n%2==0)
        {
            int k=n/2+1;
            printf("%d %d %d %d\n",k,n,1,1);
            printf("%d\n",2);
            int tot=0;
            for(int i=1;i<=k-1;i++) printf("%d %d %d\n",i,i+1,str[tot++]-'0');
            printf("%d %d %d\n",k,k,str[tot++]-'0');
            for(int i=k;i>=3;i--) printf("%d %d %d\n",i,i-1,str[tot++]-'0');
        }
        else
        {
            int k=n/2+1;
            printf("%d %d %d %d\n",k,n,1,1);
            printf("%d\n",1);
            int tot=0;
            for(int i=1;i<=k-1;i++) printf("%d %d %d\n",i,i+1,str[tot++]-'0');
            printf("%d %d %d\n",k,k,str[tot++]-'0');
            for(int i=k;i>=2;i--) printf("%d %d %d\n",i,i-1,str[tot++]-'0');
        }
    }
    return 0;
}