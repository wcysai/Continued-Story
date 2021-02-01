#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
#define fi   first
#define se   second
using namespace std;
int n,x[200005],y[200005],ans,_;
char c[200005];
bool b[200005];
pair<int,int> p[200005];
vector<int> v[200005];
priority_queue<pair<int,int> >q;
priority_queue<int> Q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int X,Y;
		scanf("%d%d %c",&X,&Y,c+i);
		x[i]=-X*2+Y;
		y[i]=-X*2-Y;
	}
	for(int i=1;i<=n;++i)p[i]=mp(x[i],i);
	sort(p+1,p+n+1);
	int k=0;
	for(int i=1;i<=n;++i){
		if(i==1||p[i].fi!=p[i-1].fi)++k;
		x[p[i].se]=k;
	}
	for(int i=1;i<=n;++i)p[i]=mp(y[i],i);
	sort(p+1,p+n+1);
	k=0;
	for(int i=1;i<=n;++i){
		if(i==1||p[i].fi!=p[i-1].fi)++k;
		y[p[i].se]=k;
	}
	for(int i=1;i<=n;++i)v[y[i]].pb(i);
	for(int i=1;i<=n;++i){
		for(int j=0;j<v[i].size();++j)q.push(mp(x[v[i][j]],v[i][j]));
		for(int j=0;j<v[i].size();++j){
			int k=v[i][j];
			if(c[k]=='N'){
				while(!q.empty()&&q.top().fi>=x[k]){
					b[q.top().se]=1;
					q.pop();
				}
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<v[i].size();++j)if(!b[v[i][j]])Q.push(x[v[i][j]]);
		for(int j=0;j<v[i].size();++j){
			int k=v[i][j];
			if(c[k]=='P'&&_<x[k]){
				if(Q.empty()||Q.top()<x[k]){
					printf("impossible\n");
					return 0;
				}
				++ans;
				_=Q.top();
			}
		}
	}
	printf("%d\n",ans);
    return 0;
}
