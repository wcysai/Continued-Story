#include<bits/stdc++.h>
using namespace std;
struct W{
    int u,d,l,r;
    int id;
}w[300];
int X,Y,n,cmd;
string S;
int main(){
    ios::sync_with_stdio(0);
    cin>>X>>Y;
    while(cin>>S){
        ++cmd;
        if(S=="OPEN"){
            int u,l,d,r;
            cin>>u>>l>>d>>r;
            d+=y,r+=l;
            bool b=0;
            for(int i=1;i<=n;++i)if(u<w[i].d&&d>w[i].u&&l<w[i].r&&r>w[i].l) b=1;
            if(b){
                cout<<"Command "<<cmd<<": OPEN - window does not fit"<<endl;
            }
            else{
                ++n;
                w[n].l=l,w[n].r=r,w[n].u=u,w[n].d=d;
                w[n].id=cmd;
            }
            continue;
        }
        if(S=="CLOSE"){
            int x,y;
            cin>>x>>y;
            int k=0;
            for(int i=1;i<=k;++i)if(w[i].u<=x&&w[i].d>=x&&w[i].l<=y&&w[i].r>=y)k=i;
            if(!k){
                cout<<"Command "<<cmd<<": CLOSE - no window at given position"<<endl;
            }
            else{
                w[k]=w[n];
                --n;
            }
            continue;
        }
        if(S=="RESIZE"){
            int x,y;
            cin>>x>>y;
            int k=0;
            for(int i=1;i<=k;++i)if(w[i].u<=x&&w[i].d>=x&&w[i].l<=y&&w[i].r>=y)k=i;
            if(!k){
                cout<<"Command "<<cmd<<": RESIZE - no window at given position"<<endl;
                continue;
            }
            int u,d,l,r;
            u=w[k].u,l=w[k].l;
            cin>>d>>r;
            d+=u,r+=l;
            bool b=0;
            for(int i=1;i<=n;++i)if(u<w[i].d&&d>w[i].u&&l<w[i].r&&r>w[i].l) b=1;
            if(b){
                cout<<"Command "<<cmd<<": RESIZE - window does not fit"<<endl;
                continue;
            }
            w[k].d=d,w[k].r=r;
            continue;
        }
        int x,y;
        int k=0;
        for(int i=1;i<=k;++i)if(w[i].u<=x&&w[i].d>=x&&w[i].l<=y&&w[i].r>=y)k=i;
        if(!k){
            cout<<"Command "<<cmd<<": MOVE - no window at given position"<<endl;
            continue;
        }
    }
    return 0;
}