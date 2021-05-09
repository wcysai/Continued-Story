#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int T,n,m,f[250005],g[505][505],_;
char c[505][505],d[505][505];
bool ok;
int F(int x){return x==f[x]?x:f[x]=F(f[x]);}
void U(int x,int y){
	if(!x||!y){
		ok=0;
		return;
	}
	if(F(x)!=F(y))f[f[x]]=f[y];
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		_=0;
		memset(g,0,sizeof(g));
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)scanf(" %c",c[i]+j),g[i][j]=++_;
		}
		for(int i=1;i<=n;++i)d[i][0]='*';
		for(int i=1;i<=m;++i)d[0][i]='*';
		bool OK=0;
		for(int x=0;x<4;++x){
			for(int y=0;y<4;++y){
				int cnt=0;
				ok=1;
				for(int i=1;i<=n;++i){
					for(int j=1;j<=m;++j){
						int u,l;
						if(d[i-1][j]=='l'||d[i-1][j]=='p'||d[i-1][j]=='q'||d[i-1][j]=='v')u=1;
						else u=0;
						if(d[i][j-1]=='-'||d[i][j-1]=='p'||d[i][j-1]=='b'||d[i][j-1]=='>')l=1;
						else l=0;
						if(c[i][j]=='*'){
							if(u||l){
								ok=0,i=501;
								break;
							}
							d[i][j]='*';
						}
						else if(c[i][j]=='q'){
							if(u&&l)d[i][j]='d';
							else if(u)d[i][j]='b';
							else if(l)d[i][j]='q';
							else d[i][j]='p';
						}
						else if(c[i][j]=='l'){
							if(u&&!l)d[i][j]='l';
							else if(l&&!u)d[i][j]='-';
							else{
								ok=0;
								i=501;
								break;
							}
						}
						else{
							++cnt;
							if(cnt==1){
								if(x==0)d[i][j]='^';
								else if(x==1)d[i][j]='>';
								else if(x==2)d[i][j]='v';
								else d[i][j]='<';
								if(u!=(x==0)||l!=(x==3)){
									ok=0;
									i=501;
									break;
								}
							}
							else{
								if(y==0)d[i][j]='^';
								else if(y==1)d[i][j]='>';
								else if(y==2)d[i][j]='v';
								else d[i][j]='<';
								if(u!=(y==0)||l!=(y==3)){
									ok=0;
									i=501;
									break;
								}
							}
						}
					}
				}
				if(!ok) continue;
				for(int i=1;i<=m;++i)if(d[n][i]=='p'||d[n][i]=='q'||d[n][i]=='l'||d[n][i]=='v')ok=0;
				for(int i=1;i<=n;++i)if(d[i][m]=='p'||d[i][m]=='b'||d[i][m]=='-'||d[i][m]=='>')ok=0;
				if(!ok) continue;
				for(int i=1;i<=_;++i)f[i]=i;
				for(int i=1;i<=n;++i){
					for(int j=1;j<=m;++j){
						if(d[i][j]=='l'){
							U(g[i][j],g[i-1][j]);
							U(g[i][j],g[i+1][j]);
						}
						if(d[i][j]=='-'){
							U(g[i][j],g[i][j-1]);
							U(g[i][j],g[i][j+1]);
						}
						if(d[i][j]=='b'){
							U(g[i][j],g[i-1][j]);
							U(g[i][j],g[i][j+1]);
						}
						if(d[i][j]=='d'){
							U(g[i][j],g[i-1][j]);
							U(g[i][j],g[i][j-1]);
						}
						if(d[i][j]=='p'){
							U(g[i][j],g[i][j+1]);
							U(g[i][j],g[i+1][j]);
						}
						if(d[i][j]=='q'){
							U(g[i][j],g[i][j-1]);
							U(g[i][j],g[i+1][j]);
						}
						if(d[i][j]=='v'){
							U(g[i][j],g[i+1][j]);
						}
						if(d[i][j]=='<'){
							U(g[i][j],g[i][j-1]);
						}
						if(d[i][j]=='>'){
							U(g[i][j],g[i][j+1]);
						}
						if(d[i][j]=='^'){
							U(g[i][j],g[i-1][j]);
						}
					}
				}
				int sx=0,sy=0;
				for(int i=1;i<=n;++i){
					for(int j=1;j<=m;++j){
						if(d[i][j]!='*'){
							if(!sx)sx=i,sy=j;
							else if(F(g[i][j])!=F(g[sx][sy]))ok=0;
						}
					}
				}
				if(ok){
					printf("YES\n");
					for(int i=1;i<=n;++i){
						for(int j=1;j<=m;++j)printf("%c",d[i][j]);
						printf("\n");
					}
					OK=1;
					x=4;
					break;
				}
			}
		}
		if(!OK){
			printf("NO\n");
		}
	}					
    return 0;
}
