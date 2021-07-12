#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n,k,a[MAXN];
bool valid[12][12][12][(1<<11)];
vector<int> vpos[12][12][12];
P L[MAXN][12][12],R[MAXN][12][12];
ll sum[MAXN];
vector<int> Lop;
vector<int> Rop;
int LL,RR;
//valid[i][j][k][mask]:
//use i swaps
//j on the left side
//k on the right side
void construct_left(int pos,int swaps,P info)
{
    if(pos==0) {LL=pos+1; return;}
    int l=info.S,r=pos;
    LL=l;
    if(swaps==0) return;
    assert(l<=r);
    int len=r-l+1;
    ll delta=info.F-(sum[r]-sum[l-1]);
    if(delta==0) return;
    int nmask=-1,ni=-1,nj=-1;
    for(int i=1;i<=r-l+1;i++)
        for(int j=1;i+j<=min(r,11)&&j<=l-1;j++)
        {
            for(int mask=0;mask<(1<<(i+j));mask++)
            {
                if(!valid[swaps][i][j][mask]) continue;
                ll tmp=0;
                for(int pos=0;pos<i+j;pos++) 
                {
                    if(mask&(1<<pos))
                    {
                        if(pos<i)
                        {
                            tmp-=a[l+i-1-pos];
                        }
                        else tmp+=a[l+i-1-pos];
                    }
                }
                if(tmp==delta)
                {
                    nmask=mask; ni=i; nj=j;
                    break;
                }
            }   
        }
    assert(nmask!=-1);
    for(int i=0;i<swaps;i++)
    {
        int save=-1;
        for(int pos=0;pos+1<ni+nj;pos++)
        {
            int nnmask=nmask;
            int x=(nmask>>pos)&1,y=(nmask>>(pos+1))&1;
            if(x^y)
            {
                nnmask^=(1<<pos);
                nnmask^=(1<<(pos+1));
            }
            if(pos+1==ni)
            {
                nnmask^=(1<<pos);
                nnmask^=(1<<(pos+1));
            }
            if(valid[swaps-i-1][ni][nj][nnmask]) 
            {
                save=pos;
                nmask=nnmask;
                break;
            }
        }
        assert(save!=-1);
        Lop.push_back(l+ni-1-save-1);
    }
   // reverse(Lop.begin(),Lop.end());
}
void construct_right(int pos,int swaps,P info)
{
    if(pos==0) {RR=pos-1; return;}
    int l=pos,r=info.S;
    RR=r;
    if(swaps==0) return;
    int len=r-l+1;
    ll delta=info.F-(sum[r]-sum[l-1]);
    if(delta==0) return;
    int nmask=-1,ni=-1,nj=-1;
    for(int i=1;i<=r-l+1;i++)
        for(int j=1;i+j<=11&&j<=n-r;j++)
        {
            for(int mask=0;mask<(1<<(i+j));mask++)
            {
                if(!valid[swaps][j][i][mask]) continue;
                ll tmp=0;
                for(int pos=0;pos<i+j;pos++) 
                {
                    if(mask&(1<<pos))
                    {
                        if(pos<j)
                        {
                            tmp+=a[r+j-pos];
                        }
                        else tmp-=a[r+j-pos];
                    }
                }
                if(tmp==delta)
                {
                    nmask=mask; ni=j; nj=i;
                    break;
                }
            }   
        }
    assert(nmask!=-1);
    for(int i=0;i<swaps;i++)
    {
        int save=-1;
        for(int pos=0;pos+1<ni+nj;pos++)
        {
            int nnmask=nmask;
            int x=(nmask>>pos)&1,y=(nmask>>(pos+1))&1;
            if(x^y)
            {
                nnmask^=(1<<pos);
                nnmask^=(1<<(pos+1));
            }
            if(pos+1==ni)
            {
                nnmask^=(1<<pos);
                nnmask^=(1<<(pos+1));
            }
            if(valid[swaps-i-1][ni][nj][nnmask]) 
            {
                save=pos;
                nmask=nnmask;
                break;
            }
        }
        assert(save!=-1);
        Rop.push_back(r+ni-save-1);
    }
    //reverse(Rop.begin(),Rop.end());
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    memset(valid,false,sizeof(valid));
    for(int i=1;i<=11;i++)
        for(int j=1;i+j<=11;j++)
        {
            valid[0][i][j][0]=true;
            vpos[0][i][j].push_back(0);
        }
    for(int k=1;k<=10;k++)
        for(int i=1;i<=11;i++)
            for(int j=1;i+j<=11;j++)
            {
                for(int mask=0;mask<(1<<(i+j));mask++)
                {
                    for(int pos=0;pos+1<i+j;pos++)
                    {
                        int nmask=mask;
                        int x=(mask>>pos)&1,y=(mask>>(pos+1))&1;
                        if(x^y)
                        {
                            nmask^=(1<<pos);
                            nmask^=(1<<(pos+1));
                        }
                        if(pos+1==i)
                        {
                            nmask^=(1<<pos);
                            nmask^=(1<<(pos+1));
                        }
                        if(valid[k-1][i][j][nmask]) valid[k][i][j][mask]=true;
                    }
                    if(valid[k][i][j][mask]) vpos[k][i][j].push_back(mask);
                }
            }
    for(int i=1;i<=n;i++)
    {
        for(int swaps=0;swaps<=k;swaps++)
        {
            L[i][swaps][0]=P(0,i+1);
            for(int j=1;j<=min(i,10);j++)
            {
                L[i][swaps][j]=P(0,i-j+1);
                for(int k=1;j+k<=min(i,11);k++) 
                    for(auto mask:vpos[swaps][j][k])
                    {
                        ll delta=0;
                        for(int pos=0;pos<j+k;pos++) 
                        {
                            if(mask&(1<<pos))
                            {
                                if(pos<j)
                                {
                                    delta-=a[i-pos];
                                }
                                else delta+=a[i-pos];
                            }
                        }
                        L[i][swaps][j]=max(L[i][swaps][j],P(delta,i-j+1));
                    }
                L[i][swaps][j].F+=sum[i]-sum[i-j];
            }
            P maxi=P(0,i+1);
            for(int j=0;j<=min(i,10);j++) maxi=max(maxi,L[i][swaps][j]);
            P q=L[i-1][swaps][11];
            q.F+=a[i]; 
            L[i][swaps][11]=max(q,maxi);
        }
    }
    for(int i=n;i>=1;i--)
    {
        for(int swaps=0;swaps<=k;swaps++)
        {
            R[i][swaps][0]=P(0,i-1);
            for(int j=1;j<=min(n+1-i,10);j++)
            {
                R[i][swaps][j]=P(0,i+j-1);
                for(int k=1;j+k<=min(n+1-i,11);k++) 
                    for(auto mask:vpos[swaps][k][j])
                    {
                        ll delta=0;
                        for(int pos=0;pos<j+k;pos++) 
                        {
                            if(mask&(1<<pos))
                            {
                                if(pos<k)
                                {
                                    delta+=a[i+j+k-1-pos];
                                }
                                else delta-=a[i+j+k-1-pos];
                            }
                        }
                        R[i][swaps][j]=max(R[i][swaps][j],P(delta,i+j-1));
                    }
                R[i][swaps][j].F+=sum[i+j-1]-sum[i-1];
            }
            P maxi=P(0,i-1);
            for(int j=0;j<=min(n+1-i,10);j++) maxi=max(maxi,R[i][swaps][j]);
            P q=R[i+1][swaps][11];
            q.F+=a[i]; 
            R[i][swaps][11]=max(q,maxi);
        }
    }
    ll ans=-INF;
    int pos=-1,num=-1;
    for(int i=1;i<=n;i++)
        for(int l=0;l<=k;l++) 
        {
            if(L[i-1][l][11].F+R[i][k-l][11].F>ans)
            {
                ans=L[i-1][l][11].F+R[i][k-l][11].F;
                pos=i;
                num=l;
            }
        }
    printf("%lld ",ans);
    construct_left(pos-1,num,L[pos-1][num][11]);
    construct_right(pos,k-num,R[pos][k-num][11]);
    assert((int)Lop.size()+(int)Rop.size()<=k);
    printf("%d\n",(int)Lop.size()+(int)Rop.size());
    for(auto x:Lop) {assert(x>=1&&x<=n-1); printf("%d %d\n",x,x+1);}
    for(auto x:Rop) {assert(x>=1&&x<=n-1); printf("%d %d\n",x,x+1);}
    printf("%d %d\n",LL,RR);
    return 0;
}
/*
6 10
90 20 -5 11 -8 100
*/