#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
	cin>>k>>n;
	--k;
	int o=n%k,p=n/k;
	cout<<(p+1)*(p+1)*o+p*p*(k-o)<<endl;
	return 0;
}