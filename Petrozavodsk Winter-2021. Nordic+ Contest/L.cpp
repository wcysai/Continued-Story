#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int n,m,a[205][205],f[205][205],_,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},d[5]={0,0,1,2,3},x[5],y[5];
char A[205][205],B[205][205],C[205][205];
void out(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)printf("%c",A[i][j]);
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)printf("%c",B[i][j]);
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)printf("%c",C[i][j]);
		printf("\n");
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)scanf("%1d",a[i]+j),_=max(_,a[i][j]);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)A[i][j]=B[i][j]=C[i][j]='.';
	}
	if(_==1){
		if(n*m<3){
			printf("impossible\n");
			return 0;
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)C[i][j]='C';
		}
		A[1][1]='A',C[1][1]='.';
		if(n>1)B[2][1]='B',C[2][1]='.';
		else B[1][2]='B',C[1][2]='.';
		out();
		return 0;
	}
	if(n==1){
		int cnt=0;
		for(int i=1;i<=m;++i){
			if(a[1][i]==2){
				if(i==1||a[1][i-1]==1)++cnt;
				if(cnt==1)A[1][i]='A';
				if(cnt==2)B[1][i]='B';
			}
			C[1][i]='C';
		}
		if(cnt>2){
			printf("impossible\n");
			return 0;
		}
		if(cnt==1){
			for(int i=1;i<=m;++i)if(a[1][i]==2)B[1][i]='B';
		}
		out();
		return 0;
	}
	if(m==1){
		int cnt=0;
		for(int i=1;i<=n;++i){
			if(a[i][1]==2){
				if(i==1||a[i-1][1]==1)++cnt;
				if(cnt==1)A[i][1]='A';
				if(cnt==2)B[i][1]='B';
			}
			C[i][1]='C';
		}
		if(cnt>2){
			printf("impossible\n");
			return 0;
		}
		if(cnt==1){
			for(int i=1;i<=n;++i)if(a[i][1]==2)B[i][1]='B';
		}
		out();
		return 0;
	}
	if(n==2){
		for(int i=1;i<=m;++i)A[1][i]='A',B[2][i]='B';
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)if(a[i][j]==2)C[i][j]='C',i=n,j=m;
		}
		for(int i=1;i<=m;++i){
			if(a[1][i]==2)B[1][i]='B';
			if(a[2][i]==2)A[2][i]='A';
		}
		out();
		return 0;
	}
	if(m==2){
		for(int i=1;i<=n;++i)A[i][1]='A',B[i][2]='B';
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)if(a[i][j]==2)C[i][j]='C',i=n,j=m;
		}
		for(int i=1;i<=n;++i){
			if(a[i][1]==2)B[i][1]='B';
			if(a[i][2]==2)A[i][2]='A';
		}
		out();
		return 0;
	}
	int cnt=n*m-4,st=1;
	x[1]=1,y[1]=1;
	x[2]=1,y[2]=m;
	x[3]=n,y[3]=m;
	x[4]=n,y[4]=1;
	f[1][1]=1;
	f[1][m]=2;
	f[n][m]=3;
	f[n][1]=4;
	_=0;
	while(cnt){
		++_;
		for(int i=1;i<=4;++i){
			while(f[x[i]+dx[d[i]]][y[i]+dy[d[i]]]==0&&(_==1||i==4||f[x[i]+dx[d[i]]*2][y[i]+dy[d[i]]*2]==0)){
				x[i]+=dx[d[i]];
				y[i]+=dy[d[i]];
				f[x[i]][y[i]]=i;
				--cnt;
			}
			if(cnt==1&&f[x[i]+dx[d[i]]][y[i]+dy[d[i]]]==0){
				x[i]+=dx[d[i]];
				y[i]+=dy[d[i]];
				f[x[i]][y[i]]=i;
				--cnt;
			}
			if(!cnt){
				st=i;
				break;
			}
			d[i]=(d[i]+1)&3;
		}
	}
	if(st==1||st==3){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(f[i][j]==2)A[i][j]='A';
				else if(f[i][j]==4)B[i][j]='B';
				else C[i][j]='C';
			}
		}
	}
	else{
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(f[i][j]==1)A[i][j]='A';
				else if(f[i][j]==3)B[i][j]='B';
				else C[i][j]='C';
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(A[i][j]=='A'){
				for(int k=0;k<4;++k)if(a[i+dx[k]][j+dy[k]]==2)A[i+dx[k]][j+dy[k]]='A';
			}
			if(B[i][j]=='B'){
				for(int k=0;k<4;++k)if(a[i+dx[k]][j+dy[k]]==2)B[i+dx[k]][j+dy[k]]='B';
			}
			if(C[i][j]=='C'){
				for(int k=0;k<4;++k)if(a[i+dx[k]][j+dy[k]]==2)C[i+dx[k]][j+dy[k]]='C';
			}
		}
	}
	out();
    return 0;
}
