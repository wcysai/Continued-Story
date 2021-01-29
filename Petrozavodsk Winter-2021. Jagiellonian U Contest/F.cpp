#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int T,n;
char opt[5],K;
char s[maxn],t[maxn];
void add()
{
	s[n]++;
	for(int i=n;i>=1;--i)if(s[i]>'z')s[i]='a',s[i-1]++;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s",&n,opt);
		K=opt[0];
		scanf("%s",s+1);
		scanf("%s",t+1);
		bool yes=0;
		for(int i=1;i<=26;++i)
		{
			add();
			if(strcmp(s+1,t+1)==0)break;
			bool has=0;
			for(int j=1;j<=n;++j)if(s[j]==K)has=1;
			if(has)
			{
				yes=1;
				printf("%s\n",s+1);
				break;
			}
		}
		if(!yes)puts("NO");
	}
}