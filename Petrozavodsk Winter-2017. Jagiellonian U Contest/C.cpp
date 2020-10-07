#include<bits/stdc++.h>
#define ll long long
using namespace std;
int z,n;
int main(){
	scanf("%d",&z);
	while(z--){
		scanf("%d",&n);
		if(n==1)puts("1 1 1 2");
		else if(n==2){
			puts("1 1 1 2");
			puts("1 3 1 4");
			puts("1 5 1 6");
		}
		else if(n==3){
			puts("1 1 1 2");
			puts("1 3 1 4");
			puts("2 1 3 1");
			puts("1 5 1 6");
			puts("2 4 3 4");
			puts("3 2 3 3");
		}
		else if(n==4){
			puts("2 1 2 2");
			puts("1 3 1 4");
			puts("2 3 2 4");
			puts("3 2 4 2");
			puts("1 6 2 6");
			puts("1 5 2 5");
			puts("3 6 4 6");
			puts("3 4 3 5");
			puts("3 3 4 3");
			puts("4 4 4 5");
		}
		else puts("impossible");
	}
	return 0;
}
