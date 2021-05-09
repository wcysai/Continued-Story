#include<bits/stdc++.h>
#define MAXN 15
#define MAXK 15
#define MAXG 105
#define MAXM 10000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<double> vec;
typedef vector<vec> mat;
int n,k,g,m;
int c[MAXK];
double p[MAXK];
int pw[MAXN];
int lab[2005];
vector<int> valid;
typedef long long ll;
mat A;
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<A.size();i++)
        for(int k=0;k<B.size();k++)
            for(int j=0;j<B[0].size();j++)
                C[i][j]=(C[i][j]+A[i][k]*B[k][j]);
    return C;
}
mat get_pow(mat A,ll n)
{
    mat B(A.size(),vec(A.size()));
    for(int i=0;i<A.size();i++)
        B[i][i]=1;
    while(n>0)
    {
        if(n&1) B=mul(B,A);
        A=mul(A,A);
        n>>=1;
    }
    return B;
}
int get_id(int mask,int i)
{
    return (mask/pw[i])%k;
}
int normalize(int mask)
{
    vector<int> v;
    for(int i=0;i<n;i++) v.push_back(get_id(mask,i));
    sort(v.begin(),v.end());
    int s=0;
    for(int i=0;i<n;i++) s+=v[i]*pw[i];
    return s;
}
pair<double,vector<int>> get_masks(int mask)
{
    vector<int> v; v.clear();
    int val=INF;
    for(int i=1;i<(1<<n);i++)
    {
        int res=0;
        for(int j=0;j<n;j++)
            if(i&(1<<j))
                res+=c[get_id(mask,j)];
        val=min(val,max(res-g,g-res));
    }
    double sum=0.0;
    for(int i=1;i<(1<<n);i++)
    {
        int res=0;
        for(int j=0;j<n;j++)
            if(i&(1<<j))
                res+=c[get_id(mask,j)];
        if(max(res-g,g-res)==val) {sum+=res; v.push_back(i);}
    }
    sum=sum/(int)v.size();
    return make_pair(sum,v);
}
void compute_coef(int mask)
{
    auto pi=get_masks(mask);
    vector<int> masks=pi.S;
    double val=pi.F;
    for(int i=0;i<pw[n];i++)
    {
        for(int j=0;j<(int)masks.size();j++)
        {
            int m=masks[j];
            double prob=1.0/(int)masks.size();
            for(int k=0;k<n;k++)
            {
                if(m&(1<<k))
                    prob=prob*p[get_id(i,k)];
                else if(get_id(mask,k)!=get_id(i,k))
                {
                    prob=0.0;
                    break;
                }
            }
            A[lab[normalize(i)]][lab[mask]]+=prob;
        }
    }
    A[(int)valid.size()][lab[mask]]+=val;
}
int main()
{
    scanf("%d%d%d%d",&n,&k,&g,&m);
    for(int i=0;i<k;i++) scanf("%d%lf",&c[i],&p[i]);
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*k;
    valid.clear();
    for(int i=0;i<=pw[n];i++)
    {
        bool f=true;
        for(int j=1;j<n;j++) if(get_id(i,j)<get_id(i,j-1)) f=false;
        if(f) valid.push_back(i);
    }
    memset(lab,-1,sizeof(lab));
    for(int i=0;i<(int)valid.size();i++) lab[valid[i]]=i;
    A.resize((int)valid.size()+1);
    for(int i=0;i<=(int)valid.size();i++) A[i].resize((int)valid.size()+1);
    for(auto x:valid) compute_coef(x);
    A[(int)valid.size()][(int)valid.size()]=1.0;
    A=get_pow(A,m);
    mat B((int)valid.size()+1,vec(1));
    for(int i=0;i<pw[n];i++) 
    {
        double prob=1.0;
        for(int j=0;j<n;j++) prob=prob*p[get_id(i,j)];
        B[lab[normalize(i)]][0]+=prob;
    }
    B=mul(A,B);
    printf("%.10f\n",B[(int)valid.size()][0]/m);
}
