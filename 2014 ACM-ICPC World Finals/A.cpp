#include<bits/stdc++.h>
using namespace std;
void sol(int l,int n){
    if(n==3){
        printf("%d to %d\n",l+2,l-1);
        printf("%d to %d\n",l+5,l+2);
        printf("%d to %d\n",l+3,l-3);
        return;
    }
    if(n==4){
        printf("%d to %d\n",l+6,l-1);
        printf("%d to %d\n",l+3,l+6);
        printf("%d to %d\n",l+0,l+3);
        printf("%d to %d\n",l+7,l+0);
        return;
    }
    
    if(n==5){
        printf("%d to %d\n",l+8,l-1);
        printf("%d to %d\n",l+3,l+8);
        printf("%d to %d\n",l+6,l+3);
        printf("%d to %d\n",l+0,l+6);
        printf("%d to %d\n",l+9,l+0);
        return;
    }
    if(n==6){
        printf("%d to %d\n",l+10,l-1);
        printf("%d to %d\n",l+7,l+10);
        printf("%d to %d\n",l+2,l+7);
        printf("%d to %d\n",l+6,l+2);
        printf("%d to %d\n",l+0,l+6);
        printf("%d to %d\n",l+11,l+0);
        return;
    }
    if(n==7){
        printf("%d to %d\n",l+12,l-1);
        printf("%d to %d\n",l+5,l+12);
        printf("%d to %d\n",l+8,l+5);
        printf("%d to %d\n",l+3,l+8);
        printf("%d to %d\n",l+9,l+3);
        printf("%d to %d\n",l+0,l+9);
        printf("%d to %d\n",l+13,l+0);
        return;
    }
    printf("%d to %d\n",l+2*n-2,l-1);
    printf("%d to %d\n",l+3,l+2*n-2);
    sol(l+4,n-4);
    printf("%d to %d\n",l,l+2*n-5);
    printf("%d to %d\n",l+2*n-1,l);
}
int main(){
    int n;
    cin>>n;
    sol(0,n);
    return 0;
}