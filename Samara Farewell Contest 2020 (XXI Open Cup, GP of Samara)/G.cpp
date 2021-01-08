#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;
char s[maxn];
int n,k;
int nxt[maxn][26],lst[26];
char Ans[maxn];
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    scanf("%d",&k);
    for(int j=0;j<26;++j)lst[j]=n+1;
    for(int i=n;i>=0;--i)
    {
        for(int j=0;j<26;++j)nxt[i][j]=lst[j];
        lst[s[i]-'a']=i;
    }
    int pos=0;
    for(int i=1;i<=k;++i)
    {
        for(int j=0;j<26;++j)if(i-1+n-nxt[pos][j]+1>=k)
        {
            pos=nxt[pos][j];
            Ans[i]=s[pos];
            break;
        }
    }
    printf("%s\n",Ans+1);
}
