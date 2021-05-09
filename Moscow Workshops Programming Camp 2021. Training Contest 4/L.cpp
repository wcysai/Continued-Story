#include<bits/stdc++.h>
using namespace std;
string s;
int n,k,a[5005],ans,cnt[5005][26],mx[5005];
int main(){
    ios::sync_with_stdio(0);
    cin>>k;
    cin>>s;
    n=s.size();
    for(int i=1;i<=n;++i)a[i]=s[i-1]-'a';
    for(int d=1;d<=n;++d){
        for(int i=0;i<d;++i){
            memset(cnt[i],0,sizeof(cnt[i]));
            mx[i]=1;
        }
        int l=1,_l=1%d,r=d,_r=0,m=d;
        for(int i=1;i<d;++i)cnt[i][a[i]]=1;
        cnt[0][a[r]]=1;
        int _lx=n-d+1,res=-n-1;
        for(;l<=_lx;){
            while(r-l-m<k&&r<=n){
                ++r,++_r;
                if(_r==d)_r=0;
                int &o=cnt[_r][a[r]];
                ++o;
                if(o>mx[_r])mx[_r]=o,++m;
            }
            res=max(res,r-l);
            if(cnt[_l][a[l]]==mx[_l]){
                --cnt[_l][a[l]];
                bool b=0;
                int _m=mx[_l];
                for(int i=0;i<26;++i)if(cnt[_l][i]==_m)b=1,i=26;
                if(!b)--mx[_l],--m;
            }
            else{
                --cnt[_l][a[l]];
            }
            ++l,++_l;
            if(_l==d)_l=0;
        }
        ans=max(ans,res-d);
    }
    cout<<ans<<endl;
    return 0;
}

