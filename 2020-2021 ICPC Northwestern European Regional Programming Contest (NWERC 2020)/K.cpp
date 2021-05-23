#include<bits/stdc++.h>
#define maxn 1005
using namespace std;
string s,t;
int n,m;
int hass[300],hast[300];
int main()
{
    getline(cin,s);
    getline(cin,t);
    n=s.length();
    m=t.length();
    for(int i=0;i<n;++i)hass[s[i]]++;
    for(int i=0;i<m;++i)hast[t[i]]++;
    for(int i=0;i<300;++i)if(hass[i]>0&&hast[i]==2*hass[i])printf("%c",i);
}