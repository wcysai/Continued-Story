#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
inline int max(int x,int y){int m=(x-y)>>31;return y&m|x&~m;}
inline int min(int x,int y){int m=(y-x)>>31;return y&m|x&~m;}
int n,m,A[1000005],pos[1000005];

const int N=1000105,D_max=21,L=27,inf=1<<30;
int f[N/L][D_max],M[N/L],a[N+L],stack[L+1],D;
int f2[N/L][D_max],M2[N/L],a2[N+L],stack2[L+1];
struct node{
    int state[L+1],*a;
    int Qmin(int x,int y){return a[x+__builtin_ctz(state[y]>>x)];}
    void init(int *_a){
        int top=0;a=_a;
        for (int i=1;i<=L;++i){
            state[i]=state[i-1];
            while (top&&a[i]<=a[stack[top]])state[i]-=1<<stack[top],--top;
            stack[++top]=i;state[i]+=1<<i;
        }
    }
}c[N/L],c2[N/L];
void build(){
    int nn=n/L;M[0]=-1;
    for (int i=1;i<=nn;++i){
        f[i][0]=inf;for (int j=1;j<=L;++j)f[i][0]=min(f[i][0],a[(i-1)*L+j]);
    }
    for (int i=1;i<=nn;++i)M[i]=!(i&(i-1))?M[i-1]+1:M[i-1];
    for (int j=1;j<=D;++j)
        for (int i=1;i<=nn-(1<<j)+1;++i)f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    for (int i=1;i<=nn+1;++i)c[i].init(a+(i-1)*L);
}
inline int Qmin_ST(int x,int y){
    int z=M[y-x+1];return min(f[x][z],f[y-(1<<z)+1][z]);
}
inline int Qmin(int x,int y){
    int xx=(x-1)/L+1,yy=(y-1)/L+1,res;
    if (xx+1<=yy-1)res=Qmin_ST(xx+1,yy-1);else res=inf;
    if (xx==yy)res=min(res,c[xx].Qmin(x-(xx-1)*L,y-(yy-1)*L));
    else res=min(res,c[xx].Qmin(x-(xx-1)*L,L)),res=min(res,c[yy].Qmin(1,y-(yy-1)*L));
    return res;
}
void build2(){
    int nn=n/L;M2[0]=-1;
    for (int i=1;i<=nn;++i){
        f2[i][0]=inf;for (int j=1;j<=L;++j)f2[i][0]=min(f2[i][0],a2[(i-1)*L+j]);
    }
    for (int i=1;i<=nn;++i)M2[i]=!(i&(i-1))?M2[i-1]+1:M2[i-1];
    for (int j=1;j<=D;++j)
        for (int i=1;i<=nn-(1<<j)+1;++i)f2[i][j]=min(f2[i][j-1],f2[i+(1<<(j-1))][j-1]);
    for (int i=1;i<=nn+1;++i)c2[i].init(a2+(i-1)*L);
}
inline int Qmin_ST2(int x,int y){
    int z=M2[y-x+1];return min(f2[x][z],f2[y-(1<<z)+1][z]);
}
inline int Qmin2(int x,int y){
    int xx=(x-1)/L+1,yy=(y-1)/L+1,res;
    if (xx+1<=yy-1)res=Qmin_ST2(xx+1,yy-1);else res=inf;
    if (xx==yy)res=min(res,c2[xx].Qmin(x-(xx-1)*L,y-(yy-1)*L));
    else res=min(res,c2[xx].Qmin(x-(xx-1)*L,L)),res=min(res,c2[yy].Qmin(1,y-(yy-1)*L));
    return res;
}

std::pair<int,int> p[1000005];
void pre(){
	//pre for rmq
	for(int i=1;i<=n;++i)a[i]=pos[i],a2[i]=n+1-pos[i];
	for(int i=n+1;i<=n+L;++i)a[i]=a2[i]=inf;
	build();
	build2();
}
int sol(int l,int r){
	if(l>r) return 0;
	int L=Qmin(l,r),R=n+1-Qmin2(l,r);//L=min(pos[l,r]),R=max(pos[l,r])
	if(r-l+1<p[L].first+p[R].first) return r-l+1;
	int ans=p[L].first+p[R].first-1;
	int m=A[L];
	return max(max(sol(l,m-1),sol(m+1,r)),ans);
}
int main(){
	scanf("%d%d",&n,&m);
	D=int(log2(n))+1;
	for(int i=1;i<=n;++i)scanf("%d",&p[i].first),p[i].second=i;
	sort(p+1,p+n+1);
	if(p[n].first<=0){
		for(int i=0;i<=m;++i)printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;++i)pos[A[i]=p[i].second]=i;
	pre();
	printf("%d\n",sol(1,n));
	for(int i=1;i<=m;++i){
		int k;
		scanf("%d",&k);
		for(int j=1;j<=k;++j){
			int x,y;
			scanf("%d%d",&x,&y);
			int t=pos[x];
			pos[x]=pos[y],pos[y]=t;
			t=A[pos[x]],A[pos[x]]=A[pos[y]],A[pos[y]]=t;
		}
		pre();
		printf("%d\n",sol(1,n));
	}
    return 0;
}
