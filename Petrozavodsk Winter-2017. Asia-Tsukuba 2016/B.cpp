#include<bits/stdc++.h>
using namespace std;
int f[10][10],g[10][10][10][10][10],ans;
int main(){
	for(int i=0;i<=9;++i){
		for(int j=0;j<=9;++j)scanf("%d",f[i]+j);
	}
	for(int a=0;a<=9;++a){
		for(int b=0;b<=9;++b){
			for(int c=0;c<=9;++c){
				for(int d=0;d<=9;++d){
					for(int e=0;e<=9;++e)g[a][b][c][d][e]=f[f[f[f[f[0][a]][b]][c]][d]][e];
				}
			}
		}
	}		
	for(int a=0;a<=9;++a){
		for(int b=0;b<=9;++b){
			for(int c=0;c<=9;++c){
				for(int d=0;d<=9;++d){
					int e=f[f[f[f[0][a]][b]][c]][d];
					bool ok=0;
					for(int i=0;i<=9;++i)if(i!=a&&!g[i][b][c][d][e])ok=1;
					for(int i=0;i<=9;++i)if(i!=b&&!g[a][i][c][d][e])ok=1;
					for(int i=0;i<=9;++i)if(i!=c&&!g[a][b][i][d][e])ok=1;
					for(int i=0;i<=9;++i)if(i!=d&&!g[a][b][c][i][e])ok=1;
					for(int i=0;i<=9;++i)if(i!=e&&!g[a][b][c][d][i])ok=1;
					if(a!=b&&!g[b][a][c][d][e])ok=1;
					if(b!=c&&!g[a][c][b][d][e])ok=1;
					if(c!=d&&!g[a][b][d][c][e])ok=1;
					if(d!=e&&!g[a][b][c][e][d])ok=1;
					if(ok)++ans;
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
	