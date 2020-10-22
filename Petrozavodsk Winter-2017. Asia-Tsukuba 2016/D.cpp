#include<bits/stdc++.h>
#define maxn 4005
#define ull unsigned long long
using namespace std;
char a[maxn],b[maxn];
const ull bas=31;
int n,m;
int num[26];
ull encode()
{
    ull res=1;
    for(int i=0;i<26;++i)res=res*bas+num[i];
    return res;
}
map<ull,bool> mp;
int main()
{
    scanf("%s",a+1);
    scanf("%s",b+1);
    n=strlen(a+1);m=strlen(b+1);
    int ans=0;
    for(int len=1;len<=min(n,m);++len)
    {
        memset(num,0,sizeof(num));
        mp.clear();
        for(int i=1;i<=len;++i)num[a[i]-'a']++;
        mp[encode()]=1;
        for(int i=len+1;i<=n;++i)
        {
            num[a[i]-'a']++;
            num[a[i-len]-'a']--;
            mp[encode()]=1;
        }
        memset(num,0,sizeof(num));
        for(int i=1;i<=len;++i)num[b[i]-'a']++;
        if(mp[encode()])ans=max(ans,len);
        for(int i=len+1;i<=m;++i)
        {
            num[b[i]-'a']++;
            num[b[i-len]-'a']--;
            if(mp[encode()])ans=max(ans,len);
        }
    }
    printf("%d\n",ans);
}