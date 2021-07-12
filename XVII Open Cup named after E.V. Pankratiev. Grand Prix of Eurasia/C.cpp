#include<bits/stdc++.h>
using namespace std;
char s[100005],t[100005];
double a,b,c;
int main()
{
    scanf("%s%lf%s%lf%lf",s,&a,t,&c,&b);
    double p=a*c-b;
    if(fabs(p)<1e-6)
    {
        puts("Whatever");
    }
    else if(p>0)
    {
        puts("Power up, Evolve");
    }
    else if(p<0)
    {
        puts("Evolve, Power up");
    }
}