#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,a[3],cnt[3];
int num[3];
//R:0 G:1 B:2
void empt(int x)
{
    printf("EMPTY %d\n",x);
    fflush(stdout);
}
void place(int x)
{
    printf("PLACE %d\n",x);
    fflush(stdout);
}
void discard()
{
    printf("DISCARD\n");
    fflush(stdout);
}
string str;
int get_color()
{
    cin>>str;
    if(str[0]=='R') return 0;
    else if(str[0]=='G') return 1;
    else if(str[0]=='B') return 2;
    else exit(0);
}
int main()
{
    scanf("%d",&T);
    for(int i=0;i<T;i++)
    {
        cnt[0]=cnt[1]=cnt[2]=0;
        for(int j=0;j<3;j++) scanf("%d",&a[j]);
        sort(a,a+3);
        if(a[0]+a[1]>=43)
        {
            for(int j=0;j<100;j++)
            {
                int c=get_color();
                if(c==0) place(1);
                else if(c==2) place(2);
                else discard();
            }
        }
        else if(a[0]<=19)
        {
            num[1]=0; num[2]=1;
            for(int j=0;j<100;j++)
            {
                int c=get_color();
                cnt[c]++;
                if(cnt[c]==a[0]+1)
                {
                    if(num[1]==c) place(1);
                    else if(num[2]==c) place(2);
                    else
                    {
                        if(cnt[num[1]]<=a[0])
                        {
                            empt(1);
                            num[1]=c;
                            place(1);
                        }
                        else 
                        {
                            empt(2);
                            num[2]=c;
                            place(2);
                        }
                    }
                }
                else
                {
                    if(num[1]==c) place(1);
                    else if(num[2]==c) place(2);
                    else discard();
                }
            }
        }
        else
        {
            num[1]=0; num[2]=1;
            for(int j=0;j<100;j++)
            {
                int c=get_color();
                cnt[c]++;
                if(cnt[c]==a[1]+1)
                {
                    if(num[1]==c) place(1);
                    else if(num[2]==c) place(2);
                    else
                    {
                        empt(1);
                        num[1]=c;
                        place(1);
                    }
                }
                else
                {
                    if(num[1]==c) place(1);
                    else if(num[2]==c) place(2);
                    else discard();
                }
            }
        }
    }
    return 0;
}