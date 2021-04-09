#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
//1w-9w 1-9
//1b-9b 10-18
//1s-9s 19-27
//1z-7z 28-34
int T;
int cnt[35];
string str;
bool flag;
vector<int> riichi;
vector<vector<int> > discard;
int parse(string str)
{
    if(str[1]=='w') return str[0]-'0';
    if(str[1]=='b') return str[0]-'0'+9;
    if(str[1]=='s') return str[0]-'0'+18;
    return str[0]-'0'+27;
}
string get_str(int id)
{
    string str="";
    if(id<=9)
    {
        str="w";
        str=(char)('0'+id)+str;
        return str;
    }
    else if(id<=18)
    {
        str="b";
        str=(char)('0'+id-9)+str;
        return str;
    }
    else if(id<=27)
    {
        str="s";
        str=(char)('0'+id-18)+str;
        return str;
    }
    str="z";
    str=(char)('0'+id-27)+str;
    return str;
}
void check(int cur,int rem)
{
    if(rem<0) return;
    if(rem==0)
    {
        flag=true;
        return;
    }
    if(flag) return;
    if(!cnt[cur]) check(cur+1,rem);
    if(cnt[cur]>=3)
    {
        cnt[cur]-=3;
        check(cur,rem-3);
        cnt[cur]+=3;
    }
    if(rem%3==2&&cnt[cur]>=2)
    {
        cnt[cur]-=2;
        check(cur,rem-2);
        cnt[cur]+=2;
    }
    if(cur<=27&&cur%9!=0&&cur%9!=8&&cnt[cur]&&cnt[cur+1]&&cnt[cur+2])
    {
        cnt[cur]--; cnt[cur+1]--; cnt[cur+2]--;
        check(cur,rem-3);
        cnt[cur]++; cnt[cur+1]++; cnt[cur+2]++;
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(cnt,0,sizeof(cnt));
        cin>>str;
        int n=(int)str.size();
        for(int i=0;i<n;i+=2)
        {
            cnt[parse(str.substr(i,2))]++;
        }
        flag=false;
        check(1,14);
        if(flag)
        {
            puts("Tsumo!");
            continue;
        }
        riichi.clear();
        discard.clear();
        for(int i=1;i<=34;i++)
        {
            if(cnt[i])
            {
                cnt[i]--;
                vector<int> tmp;
                tmp.clear();
                for(int j=1;j<=34;j++)
                {
                    if(j==i) continue;
                    cnt[j]++;
                    flag=false;
                    check(1,14);
                    if(flag) tmp.push_back(j);
                    cnt[j]--;
                }
                if(tmp.size())
                {
                    riichi.push_back(i);
                    discard.push_back(tmp);
                }
                cnt[i]++;
            }
        }
        printf("%d\n",(int)riichi.size());
        for(int i=0;i<(int)riichi.size();i++)
        {
            cout<<get_str(riichi[i])<<" ";
            for(int j=0;j<(int)discard[i].size();j++) cout<<get_str(discard[i][j]);
            cout<<endl;
        }
    }
    return 0;
}