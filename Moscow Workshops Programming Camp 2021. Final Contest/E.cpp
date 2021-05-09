//team continued story
#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;

struct E{int x,y,z,_;};
struct F{
	vector<E> v[60015];
	void add(int x,int y,int z,int _){
		E X,Y;
		X.x=y,X.y=z,X.z=v[y].size(),X._=_;
		Y.x=x,Y.y=0,Y.z=v[x].size(),Y._=_;
		v[x].pb(X),v[y].pb(Y);
	}
	int n,m,s,t,ans;
	int l[60015],i[60015],q[60015],L,R;
	int dfs(int x,int y){
		if(x==t) return y;
		int ret=0;
		for(;i[x]<v[x].size();++i[x]){
		    E &e=v[x][i[x]];
		    if(!e.y||l[e.x]!=l[x]+1) continue;
		    int d=dfs(e.x,min(y,e.y));
		    if(!d) continue;
		    e.y-=d,v[e.x][e.z].y+=d,ret+=d,y-=d;
		    if(!y) return ret;
		}
		l[x]=-1;
		return ret;
	}
	void sol(){
		ans=0;
		while(1){
		    memset(i,0,sizeof(i));
		    memset(l,-1,sizeof(l));
		    l[s]=0,L=0,R=1,q[1]=s;
		    while(L!=R){
		        int x=q[++L];
		        for(int i=0;i<v[x].size();++i){
		            if(v[x][i].y&&l[v[x][i].x]==-1)l[v[x][i].x]=l[x]+1,q[++R]=v[x][i].x;
		        }
		    }
		    if(l[t]==-1) break;
		    ans+=dfs(s,orz);
	   }
	}
}_[3];
int n,m,c[3][30005],a[30005],C,N[30005],A[30005],L[30005],R[30005],o[30005],res,cnt;
vector<int> v[30005];
void dfs(int x){
	c[C][x]=cnt;
	for(int i=0;i<v[x].size();++i)if(a[v[x][i]]!=C&&!c[C][v[x][i]])dfs(v[x][i]);
}
int main(){
//freopen("E.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%d",a+i),A[i]=(++N[--a[i]]);
    for(int i=1;i<=m;++i){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	v[x].pb(y);
    	v[y].pb(x);
    }
    for(C=0;C<3;++C){
    	cnt=0;
    	for(int i=1;i<=n;++i){
    		if(a[i]!=C&&!c[C][i]){
                ++cnt;
                dfs(i);
            }
    	}
    }
    for(C=0;C<3;++C){
    	_[C].t=_[C].n=n*2+2,_[C].s=_[C].t-1;
    	int s=_[C].s,t=_[C].t;
    	memset(L,0,sizeof(L));
    	memset(R,0,sizeof(R));
    	for(int i=1;i<=n;++i){
    		if(a[i]==C){
    			int l=c[(C+1)%3][i],r=c[(C+2)%3][i];
    			L[l]=i,R[r]=i;
    			_[C].add(l,r+n,1,i);
    		}
    	}
    	for(int i=1;i<=n;++i){
    		if(L[i])_[C].add(s,i,1,L[i]);
    		if(R[i])_[C].add(i+n,t,1,R[i]);
    	}
    	_[C].sol();
    	res=0;
    	for(int i=1;i<=n;++i){
    		for(int j=0;j<_[C].v[i].size();++j)if(_[C].v[i][j].y==0&&_[C].v[i][j].x<s)o[++res]=_[C].v[i][j]._;
    	}
    	for(int i=0;i<_[C].v[s].size();++i)if(_[C].v[s][i].y==1)o[++res]=_[C].v[s][i]._;
    	for(int i=0;i<_[C].v[t].size();++i)if(_[C].v[t][i].y==0)o[++res]=_[C].v[t][i]._;
    	printf("%d",res);
    	for(int i=1;i<=res;++i)printf(" %d",o[i]);
    	printf("\n");
    }

    return 0;
}