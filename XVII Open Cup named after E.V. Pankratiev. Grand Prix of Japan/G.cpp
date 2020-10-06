#include<bits/stdc++.h>
#define ll      long long
using namespace std;
int a[200][200],f[200][200];
int main(){
    for(int i=0;i<13;++i){
        for(int j=0;j<13;++j){
            int x=13*i,y=13*j;
            for(int k=0;k<13;++k)a[x+k][y+(k*j+i)%13]=1;
        }
    }
    cout<<150<<endl;
    for(int i=0;i<150;++i){
        for(int j=0;j<150;++j){
            if(a[i][j])cout<<"O";
            else cout<<".";
        }
        cout<<endl;
    }
    return 0;
}
