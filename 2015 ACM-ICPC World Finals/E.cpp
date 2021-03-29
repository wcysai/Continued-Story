#include<bits/stdc++.h>
#define maxn 4005
using namespace std;
int n;
struct Str
{
	char s[maxn];
	int len;
	Str()
	{
		len=0;
		memset(s,0,sizeof(s));
	}
	void read()
	{
		memset(s,0,sizeof(s));
		scanf("%s",s+1);
		len=strlen(s+1);
	}
}s[maxn];
bool operator < (Str A,Str B)
{
	return A.len<B.len;
}
int id(char c)
{
	if(c=='A')return 0;
	else if(c=='C')return 1;
	else return 2;
}
int nxt[maxn][3];
bool issub(int a,int b)
{
	memset(nxt,0,sizeof(nxt));
	for(int j=0;j<3;++j)nxt[s[b].len][j]=0;
	for(int i=s[b].len-1;i>=0;--i)
	{
		for(int j=0;j<3;++j)nxt[i][j]=nxt[i+1][j];
		nxt[i][id(s[b].s[i+1])]=i+1;
	}
	int pos=0;
	for(int i=1;i<=s[a].len;++i)
	{
		if(!nxt[pos][id(s[a].s[i])])return 0;
		pos=nxt[pos][id(s[a].s[i])];
	}
	return 1;
}
vector<int> Ansa,Ansb;
vector< pair<int,int> > trace1,trace2;
int main()
{
	scanf("%d",&n);
	s[n+1].read();
	for(int i=1;i<=n;++i)s[i].read();
	sort(s+1,s+n+1);
	int x=0,y=0,a=0,b=0,c=0,d=0,tp=0;
	bool yes=1;
	for(int i=1;i<=n;++i)if(!issub(i,n+1))yes=0;
	for(int i=1;i<=n;++i)
	{
		if(!tp)
		{
			if(!issub(x,i)&&!issub(y,i))yes=0;
			else if(!issub(y,i))
			{
				Ansa.push_back(i);
				x=i;
			}
			else if(!issub(x,i))
			{
				Ansb.push_back(i);
				y=i;
			}
			else
			{
				tp=1;
				a=x;b=i;c=i;d=y;
				trace1.push_back(make_pair(0,i));
				trace2.push_back(make_pair(i,0));
			}
		}
		else
		{
			if(issub(b,i))
			{
				b=i;c=i;
				trace1.push_back(make_pair(0,i));
				trace2.push_back(make_pair(i,0));
			}
			else if(issub(a,i))
			{
				a=i;
				trace1.push_back(make_pair(i,0));
				for(auto p:trace1)
				{
					if(p.first)Ansa.push_back(p.first);
					if(p.second)Ansb.push_back(p.second);
				}
				trace1.clear();trace2.clear();
				tp=0;
				x=a;y=b;
			}
			else if(issub(d,i))
			{
				d=i;
				trace2.push_back(make_pair(0,i));
				for(auto p:trace2)
				{
					if(p.first)Ansa.push_back(p.first);
					if(p.second)Ansb.push_back(p.second);
				}
				trace1.clear();trace2.clear();
				tp=0;
				x=c;y=d;
			}
			else yes=0;
		}
	}
	if(tp==1)
	{
		for(auto p:trace1)
		{
			if(p.first)Ansa.push_back(p.first);
			if(p.second)Ansb.push_back(p.second);
		}
	}
	if(!yes)puts("impossible");
	else
	{
		printf("%d %d\n",Ansa.size(),Ansb.size());
		for(int x:Ansa)printf("%s\n",s[x].s+1);
		for(int x:Ansb)printf("%s\n",s[x].s+1);
	}
}