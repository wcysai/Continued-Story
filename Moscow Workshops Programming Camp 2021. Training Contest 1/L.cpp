#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
typedef long long ll;
struct Point
{
	ll x,y;
	Point(ll x=0,ll y=0):x(x),y(y){}
	void read()
	{
		scanf("%lld%lld",&x,&y);
	}
};
typedef Point Vector;
Vector operator + (Vector A,Vector B)
{
	return Vector(A.x+B.x,A.y+B.y);
}
Vector operator - (Vector A,Vector B)
{
	return Vector(A.x-B.x,A.y-B.y);
}
ll Cross(Vector A,Vector B)
{
	return A.x*B.y-A.y*B.x;
}
int n,s,t;
Point p[maxn];
pair<Point,int> stk[maxn];
int top;
int main()
{
	scanf("%d",&n);
	p[n].read();
	for(int i=1;i<n;++i)p[i].read();
	scanf("%d%d",&s,&t);
	if(!s)s=n;if(!t)t=n;
	bool fl=0;
	if(s>t)swap(s,t),fl=1;
	stk[++top]=make_pair(p[s],s);
	stk[++top]=make_pair(p[s+1],s+1);
	for(int i=s+2;i<=t;++i)
	{
		while(top>1&&Cross(p[i]-stk[top-1].first,stk[top].first-stk[top-1].first)<=0)--top;
		stk[++top]=make_pair(p[i],i);
	}
	printf("%d\n",top);
	if(fl)reverse(stk+1,stk+top+1);
	for(int i=1;i<=top;++i)
	{
		int x=stk[i].second;
		if(x==n)x=0;
		printf("%d ",x);
	}
}