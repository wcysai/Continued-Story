#include<bits/stdc++.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
using namespace std;
int a[100005],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	if(n>90){
		puts("Yes");
		return 0;
	}
	for(int i=1;i<n;++i){
		for(int j=i+1;j<n;++j){
			for(int k=j+1;k<n;++k){
				for(int l=k+1;l<=n;++l){
					if((a[i]^a[j]^a[k]^a[l])==0){
						puts("Yes");
						return 0;
					}
				}
			}
		}
	}
	puts("No");
			
    return 0;
}
