#include<bits/stdc++.h>
#define mp      make_pair
#define pb      push_back
using namespace std;
int n,m,k,K,MK,N,A[100005],B[100005],a[100005],b[100005],num[600100],srt[600100],S,sl[600100],sr[600100],_,ask[600100],ansl,ansr;
bool ban[300005];
map<int,int> M;
vector<pair<int,int> > v[600100];
vector<int> rv[600100];
priority_queue<pair<int,int> > Q;
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i){
        scanf("%d%d",A+i,B+i);
        srt[++S]=A[i]-1;
        srt[++S]=A[i];
        srt[++S]=A[i]+1;
        srt[++S]=B[i]-1;
        srt[++S]=B[i];
        srt[++S]=B[i]+1;
    }
    srt[++S]=k-1;
    srt[++S]=k;
    srt[++S]=k+1;
    srt[++S]=m-k-1;
    srt[++S]=m-k;
    srt[++S]=m-k+1;
    srt[++S]=0;
    srt[++S]=m;
    sort(srt+1,srt+S+1);
    for(int i=1;i<=S;++i){
        if(srt[i]>=0&&srt[i]<=m&&(i==1||srt[i]!=srt[i-1])){
            num[++N]=srt[i];
            M[num[N]]=N;
        }
    }
    K=M[k];
    MK=M[m-k];
    for(int i=1;i<=n;++i)a[i]=M[A[i]],b[i]=M[B[i]],ban[i]=1000000007;
    for(int i=1;i<=n;++i){
        if(B[i]-A[i]<=k){
            ++_;
            v[a[i]].pb(mp(a[i]-1,_));
            rv[b[i]].pb(_);
        }
        if(A[i]<k)++sr[a[i]],--sr[min(K,b[i])+1];
        if(B[i]>m-k)++sl[max(MK,a[i])],--sl[b[i]+1];
        if(A[i]<=k&&B[i]>=m-k){
            if(a[i]>1){
                ++_;
                v[1].pb(mp(0,_));
                rv[a[i]-1].pb(_);
            }
            if(b[i]<N){
                ++_;
                v[b[i]+1].pb(mp(b[i],_));
            }
        }
    }
    ansl=0,ansr=k;
    int k=0;
    for(int i=1;i<=N;++i){
        sl[i]+=sl[i-1];
        sr[i]+=sr[i-1];
        if(!sl[i])k=ask[i];
        for(int j=0;j<v[i].size();++j){
            Q.push(mp(-v[i][j].first,v[i][j].second));
        }
        if(!sr[i]){
            while(!Q.empty()&&ban[Q.top().second])Q.pop();
            int x;
            if(Q.empty())x=ask[i];
            else x=ask[-Q.top().first];
            if(x&&num[i]-num[x]<ansr-ansl)ansl=num[x],ansr=num[i];
        }
        for(int j=0;j<rv[i].size();++j)ban[rv[i][j]]=1;
    }
    if(ansl==ansr)puts("-1 -1");
    else printf("%d %d\n",ansl,ansr);
    return 0;
}